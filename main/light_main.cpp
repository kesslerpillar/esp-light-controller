#include <lib/LightController.h>
#include "nvs_flash.h"
#include "esp_event.h"
#include "service/wifi_service.h"
#include "PhysicalLight.h"
#include "MqttLight.h"
#include "ButtonLightSwitch.h"
#include "service/MqttService.h"
#include <vector>
#include <string.h>
#include <esp_log.h>

using namespace std;

unique_ptr<LightController> getLightController();

unique_ptr<LightController> getLightController() {
    vector<shared_ptr<Light> > lights{(shared_ptr<Light>) make_shared<PhysicalLight>()};
    shared_ptr<LightSwitch> lightSwitch(new ButtonLightSwitch());
    unique_ptr<LightController> lightController(new LightController(lightSwitch, lights));
    return lightController;
}

unique_ptr<LightController> getBlinkLightController() {
    shared_ptr<Light> blinkLight{(shared_ptr<Light>) make_shared<PhysicalLight>()};
    unique_ptr<LightController> lightBlinkController(new LightController(blinkLight));
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
            if (strcmp(getSubscribeMessage(), "") != 0){
                lightController->updateLights(getSubscribeMessage());
            }
            vTaskDelay(50 / portTICK_PERIOD_MS);
        }
    }
}
