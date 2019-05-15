#include <lib/LightController.h>
#include "nvs_flash.h"
#include "esp_event.h"
#include "service/wifi_service.h"
#include "PhysicalLight.h"
#include "MqttLight.h"
#include "ButtonLightSwitch.h"
#include "service/MqttService.h"
#include <vector>

using namespace std;

unique_ptr<LightController> getLightController();

unique_ptr<LightController> getLightController() {
    vector<shared_ptr<Light> > lights{(shared_ptr<Light>) make_shared<PhysicalLight>(), (shared_ptr<Light>) make_shared<MqttLight>()};
    shared_ptr<LightSwitch> lightSwitch(new ButtonLightSwitch());
    unique_ptr<LightController> lightController(new LightController(lightSwitch, lights));
    return lightController;
}

extern "C" {
    void app_main()
    {
        setupWiFi();
        openMqttConnection(CONFIG_MQTT_BROKER_URL);
        unique_ptr<LightController> lightController = getLightController();
        lightController -> blinkLight();

        while(1) {
            lightController->update();
            vTaskDelay(50 / portTICK_PERIOD_MS);
        }
    }
}
