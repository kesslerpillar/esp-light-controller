#include "nvs_flash.h"
#include "esp_wifi.h"
#include "esp_log.h"
#include "freertos/event_groups.h"
#include <string.h>

#define GOT_IPV4_BIT  BIT(0)
#define GOT_IPV6_BIT  BIT(1)

#ifdef CONFIG_EXAMPLE_CONNECT_IPV6
#define CONNECTED_BITS  (GOT_IPV4_BIT | GOT_IPV6_BIT)
#else
#define CONNECTED_BITS  (GOT_IPV4_BIT)
#endif

#ifdef CONFIG_EXAMPLE_CONNECT_IPV6
static ip6_addr_t s_ipv6_addr;
#endif

static EventGroupHandle_t s_connect_event_group;
static const char *TAG = "WIFI";
static const char* s_connection_name;
static ip4_addr_t s_ip_addr;

static void on_got_ip(void* arg, esp_event_base_t event_base,
                      int32_t event_id, void* event_data)
{
    ip_event_got_ip_t* event = (ip_event_got_ip_t*) event_data;
    memcpy(&s_ip_addr, &event->ip_info.ip, sizeof(s_ip_addr));
    xEventGroupSetBits(s_connect_event_group, GOT_IPV4_BIT);
}

#ifdef CONFIG_EXAMPLE_CONNECT_IPV6

static void on_got_ipv6(void* arg, esp_event_base_t event_base,
                        int32_t event_id, void* event_data)
{
    ip_event_got_ip6_t* event = (ip_event_got_ip6_t*) event_data;
    memcpy(&s_ipv6_addr, &event->ip6_info.ip, sizeof(s_ipv6_addr));
    xEventGroupSetBits(s_connect_event_group, GOT_IPV6_BIT);
}

#endif

static void on_wifi_disconnect(void* arg, esp_event_base_t event_base,
                               int32_t event_id, void* event_data)
{
    ESP_LOGI(TAG, "Wi-Fi disconnected, trying to reconnect...");
    ESP_ERROR_CHECK( esp_wifi_connect() );
}

#ifdef CONFIG_EXAMPLE_CONNECT_IPV6

static void on_wifi_connect(void* arg, esp_event_base_t event_base,
                            int32_t event_id, void* event_data)
{
    tcpip_adapter_create_ip6_linklocal(TCPIP_ADAPTER_IF_STA);
}

#endif

static void start()
{
    wifi_init_config_t cfg = WIFI_INIT_CONFIG_DEFAULT();
    ESP_ERROR_CHECK(esp_wifi_init(&cfg));

    ESP_ERROR_CHECK(esp_event_handler_register(WIFI_EVENT, WIFI_EVENT_STA_DISCONNECTED, &on_wifi_disconnect, NULL));
    ESP_ERROR_CHECK(esp_event_handler_register(IP_EVENT, IP_EVENT_STA_GOT_IP, &on_got_ip, NULL));
#ifdef CONFIG_EXAMPLE_CONNECT_IPV6
    ESP_ERROR_CHECK(esp_event_handler_register(WIFI_EVENT, WIFI_EVENT_STA_CONNECTED, &on_wifi_connect, NULL));
    ESP_ERROR_CHECK(esp_event_handler_register(IP_EVENT, IP_EVENT_GOT_IP6, &on_got_ipv6, NULL));
#endif

    ESP_ERROR_CHECK(esp_wifi_set_storage(WIFI_STORAGE_RAM));
    wifi_config_t wifi_config;
    memset(&wifi_config, 0, sizeof(wifi_config_t));
    strcpy(reinterpret_cast<char *>(wifi_config.sta.ssid), CONFIG_ESP_WIFI_SSID);
    strcpy(reinterpret_cast<char *>(wifi_config.sta.password), CONFIG_ESP_WIFI_PASSWORD);
    ESP_LOGI(TAG, "Connecting to %s...", wifi_config.sta.ssid);
    ESP_ERROR_CHECK(esp_wifi_set_mode(WIFI_MODE_STA));
    ESP_ERROR_CHECK(esp_wifi_set_config(ESP_IF_WIFI_STA, &wifi_config));
    ESP_ERROR_CHECK(esp_wifi_start());
    ESP_ERROR_CHECK(esp_wifi_connect());
    s_connection_name = CONFIG_ESP_WIFI_SSID;
}

esp_err_t config_connect()
{
    if (s_connect_event_group != NULL) {
        return ESP_ERR_INVALID_STATE;
    }
    s_connect_event_group = xEventGroupCreate();
    start();
    xEventGroupWaitBits(s_connect_event_group, CONNECTED_BITS, true, true, portMAX_DELAY);
    ESP_LOGI(TAG, "Connected to %s", s_connection_name);
    ESP_LOGI(TAG, "IPv4 address: " IPSTR, IP2STR(&s_ip_addr));
#ifdef CONFIG_EXAMPLE_CONNECT_IPV6
    ESP_LOGI(TAG, "IPv6 address: " IPV6STR, IPV62STR(s_ipv6_addr));
#endif
    return ESP_OK;
}

void setupWiFi() {
    ESP_ERROR_CHECK( nvs_flash_init() );
    tcpip_adapter_init();
    ESP_ERROR_CHECK(esp_event_loop_create_default());
    ESP_ERROR_CHECK(config_connect());
}