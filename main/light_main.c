
#include <stdio.h>
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "driver/gpio.h"
#include "sdkconfig.h"
#include <stdbool.h>
#include "nvs_flash.h"
#include "lwip/netdb.h"
#include "service/wifi_service.c"

#define LED 12
#define BUTTON 26

int toggle_mode = 1;
int already_pressed = 0;

bool isButtonPressed() {
    return gpio_get_level(BUTTON);
}

void setPinsForInputOutput() {
    gpio_pad_select_gpio(LED);
    gpio_pad_select_gpio(BUTTON);
    gpio_set_direction(LED, GPIO_MODE_OUTPUT);
    gpio_set_direction(BUTTON, GPIO_MODE_INPUT);
}

void toggleLED() {
    printf("Toggling the LED\n");
    toggle_mode = (toggle_mode == 0) ? 1 : 0;
    gpio_set_level(LED, toggle_mode);
}

void toggleWebLight() {
    if(toggle_mode == 0) {
        getRequest(CONFIG_TURN_ON_LIGHT_URL);
    } else {
        getRequest(CONFIG_TURN_OFF_LIGHT_URL);
    }
}

void handleButtonPresses() {
    /* Detect button push */
    if(isButtonPressed()) {
        if(already_pressed == 0) {
            toggleLED();
            already_pressed = 1;
            toggleWebLight();
        } else {
            printf("Button already pressed, ignoring until it's released\n");
        }
    }
    else {
        already_pressed = 0;
    }
    vTaskDelay(50 / portTICK_PERIOD_MS);
}

void setupWiFi() {
    // Set up Wi-Fi connection
    ESP_ERROR_CHECK( nvs_flash_init() );
    tcpip_adapter_init();
    ESP_ERROR_CHECK(esp_event_loop_create_default());

    ESP_ERROR_CHECK(config_connect());
}

void app_main()
{
    setPinsForInputOutput();
    setupWiFi();

    // Turn light off to start
    gpio_set_level(LED, toggle_mode);

    while(1) {
        handleButtonPresses();
    }
}