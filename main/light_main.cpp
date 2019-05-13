#include <lib/LightController.h>
#include "nvs_flash.h"
#include "esp_event.h"
#include "service/wifi_service.h"
#include "PhysicalLight.h"
#include "WebLight.h"
#include "ButtonLightSwitch.h"
#include <vector>
#include "mqtt_client.h"

using namespace std;

unique_ptr<LightController> getLightController();

unique_ptr<LightController> getLightController() {
    vector<shared_ptr<Light> > lights{(shared_ptr<Light>) make_shared<PhysicalLight>(), (shared_ptr<Light>) make_shared<WebLight>()};
    shared_ptr<LightSwitch> lightSwitch(new ButtonLightSwitch());
    unique_ptr<LightController> lightController(new LightController(lightSwitch, lights));
    return lightController;
}

extern "C" {
    static esp_err_t mqtt_event_handler(esp_mqtt_event_handle_t event)
    {
        esp_mqtt_client_handle_t client = event->client;
        switch (event->event_id) {
            case MQTT_EVENT_CONNECTED:
                esp_mqtt_client_publish(client, "iot.light.switch", "on", 0, 1, 0);
            default:
                break;
        }
        return ESP_OK;
    }

    void app_main()
    {
        setupWiFi();
        unique_ptr<LightController> lightController = getLightController();
        lightController -> blinkLight();

        while(1) {
            esp_mqtt_client_config_t mqtt_cfg;

            memset(&mqtt_cfg, 0, sizeof(mqtt_cfg));
            mqtt_cfg.uri = "tcp://10.3.10.229:1883";
            mqtt_cfg.event_handle = mqtt_event_handler;

            esp_mqtt_client_handle_t client = esp_mqtt_client_init(&mqtt_cfg);
            esp_mqtt_client_start(client);

            lightController->update();
            vTaskDelay(50 / portTICK_PERIOD_MS);
        }
    }
}
