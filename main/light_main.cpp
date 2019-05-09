
#include <stdio.h>
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "driver/gpio.h"
#include "sdkconfig.h"
#include <stdbool.h>
#include <tcpip_adapter.h>
#include <lib/LightController.h>
#include "nvs_flash.h"
#include "lwip/netdb.h"
#include "esp_event.h"
#include "service/wifi_service.h"
#include "PhysicalLight.h"
#include "WebLight.h"
#include "ButtonLightSwitch.h"
#include <memory>
#include <vector>
using namespace std;

#define LED GPIO_NUM_12
#define BUTTON GPIO_NUM_26


void setupWiFi() {
    // Set up Wi-Fi connection
    ESP_ERROR_CHECK( nvs_flash_init() );
    tcpip_adapter_init();
    ESP_ERROR_CHECK(esp_event_loop_create_default());

    ESP_ERROR_CHECK(config_connect());
}

extern "C" {

void app_main()
{
    setupWiFi();


    vector<shared_ptr<Light> > lights(2);

    lights[0].reset(new PhysicalLight());
    lights[1].reset(new WebLight());

    shared_ptr<LightSwitch> lightSwitch(new ButtonLightSwitch());

    LightController lightController(lightSwitch, lights);


    while(1) {
        lightController.update();
        vTaskDelay(50 / portTICK_PERIOD_MS);
    }
}

}
