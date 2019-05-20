#include <lib/LightController.h>
#include "esp_event.h"
#include "service/wifi_service.h"
#include "PhysicalLight.h"
#include "ButtonLightSwitch.h"
#include "service/MqttService.h"

using namespace std;

unique_ptr<LightController> getLightController();

unique_ptr<LightController> getLightController() {
    shared_ptr<Light> light{(shared_ptr<Light>) make_shared<PhysicalLight>()};
    shared_ptr<LightSwitch> lightSwitch(new ButtonLightSwitch());
    unique_ptr<LightController> lightController(new LightController(lightSwitch, light));
    return lightController;
}

unique_ptr<LightController> getBlinkLightController() {
    shared_ptr<Light> light{(shared_ptr<Light>) make_shared<PhysicalLight>()};
    unique_ptr<LightController> lightBlinkController(new LightController(light));
    return lightBlinkController;
}

extern "C" {
    void app_main()
    {
        setupWiFi();
        openMqttConnection(CONFIG_MQTT_BROKER_URL);
        subscribe(CONFIG_MQTT_PUBLISH_TOPIC);

        unique_ptr<LightController> lightBlinkController = getBlinkLightController();
        lightBlinkController -> blinkLight();

        unique_ptr<LightController> lightController = getLightController();

        while(1) {
            lightController->updateSwitch();
            if (subscribeMessageIsReceived())
            {
                lightController->updateLights();
                updateMessageReceivedStatus();
            }
            vTaskDelay(50 / portTICK_PERIOD_MS);
        }
    }
}
