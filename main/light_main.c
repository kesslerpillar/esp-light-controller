#include "nvs_flash.h"
#include "lwip/netdb.h"
#include "service/wifi_service.c"

static void http_get_request()
{
    while(1) {
        getRequest(CONFIG_TURN_ON_LIGHT_URL);
        sleep(5);

        getRequest(CONFIG_TURN_OFF_LIGHT_URL);
        sleep(5);
    }
}

void app_main()
{
    ESP_ERROR_CHECK( nvs_flash_init() );
    tcpip_adapter_init();
    ESP_ERROR_CHECK(esp_event_loop_create_default());

    ESP_ERROR_CHECK(config_connect());

    xTaskCreate(&http_get_request, "http_get_request", 4096, NULL, 5, NULL);
}
