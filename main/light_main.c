#include "esp_wifi.h"
#include "esp_http_client.h"
#include "esp_log.h"
#include "lwip/sockets.h"
#include "nvs_flash.h"
#include "lwip/netdb.h"
#include "freertos/event_groups.h"
#include <string.h>
#include "service/wifi_service.c"

static void http_get_request()
{

    while(1) {
        esp_http_client_config_t config = {
                .url = CONFIG_TURN_ON_LIGHT_URL,
                .event_handler = _http_event_handler,
        };
        esp_http_client_handle_t client = esp_http_client_init(&config);

        // GET
        esp_err_t err = esp_http_client_perform(client);
        if (err == ESP_OK) {
            ESP_LOGI(TAG, "HTTP GET Status = %d, content_length = %d",
                     esp_http_client_get_status_code(client),
                     esp_http_client_get_content_length(client));
        } else {
            ESP_LOGE(TAG, "HTTP GET request failed: %s", esp_err_to_name(err));
        }

        esp_http_client_cleanup(client);

        sleep(5);

        esp_http_client_config_t config2 = {
                .url = CONFIG_TURN_OFF_LIGHT_URL,
                .event_handler = _http_event_handler,
        };
        esp_http_client_handle_t client2 = esp_http_client_init(&config2);

        // GET
        esp_err_t err2 = esp_http_client_perform(client2);
        if (err2 == ESP_OK) {
            ESP_LOGI(TAG, "HTTP GET Status = %d, content_length = %d",
                     esp_http_client_get_status_code(client2),
                     esp_http_client_get_content_length(client2));
        } else {
            ESP_LOGE(TAG, "HTTP GET request failed: %s", esp_err_to_name(err2));
        }

        esp_http_client_cleanup(client2);

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
