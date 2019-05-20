#include "MqttService.h"
#include "esp_log.h"
#include "esp_event.h"
#include <mqtt_client.h>
#include <freertos/event_groups.h>

static esp_mqtt_client_handle_t client;
static EventGroupHandle_t mqtt_event_group;
const static int CONNECTED_BIT = BIT0;

static const char *TAG = "MQTT";
static const char *defaultMessage = "default";
bool SubscribeMessageReceived = false;

static esp_err_t mqtt_event_handler(esp_mqtt_event_handle_t event)
{
    switch (event->event_id) {
        case MQTT_EVENT_CONNECTED:
            xEventGroupSetBits(mqtt_event_group, CONNECTED_BIT);
            ESP_LOGI(TAG, "MQTT_EVENT_CONNECTED");
            break;
        case MQTT_EVENT_DISCONNECTED:
            ESP_LOGI(TAG, "MQTT_EVENT_DISCONNECTED");
            break;
        case MQTT_EVENT_SUBSCRIBED:
            ESP_LOGI(TAG, "MQTT_EVENT_SUBSCRIBED, msg_id=%d", event->msg_id);
            break;
        case MQTT_EVENT_UNSUBSCRIBED:
            ESP_LOGI(TAG, "MQTT_EVENT_UNSUBSCRIBED, msg_id=%d", event->msg_id);
            break;
        case MQTT_EVENT_PUBLISHED:
            ESP_LOGI(TAG, "MQTT_EVENT_PUBLISHED, msg_id=%d", event->msg_id);
            break;
        case MQTT_EVENT_DATA:
            SubscribeMessageReceived = true;
            ESP_LOGI(TAG, "MQTT_SUBSCRIBE_RECEIVED");
            break;
        case MQTT_EVENT_ERROR:
            ESP_LOGI(TAG, "MQTT_EVENT_ERROR");
            break;
        default:
            ESP_LOGI(TAG, "Other event id:%d", event->event_id);
            break;
    }
    return ESP_OK;
}

void openMqttConnection(const char *url){
    mqtt_event_group = xEventGroupCreate();
    esp_mqtt_client_config_t mqtt_cfg;
    memset(&mqtt_cfg, 0, sizeof(mqtt_cfg));
    mqtt_cfg.uri = url;
    mqtt_cfg.event_handle = mqtt_event_handler;

    client = esp_mqtt_client_init(&mqtt_cfg);
    xEventGroupClearBits(mqtt_event_group, CONNECTED_BIT);
    esp_mqtt_client_start(client);
    xEventGroupWaitBits(mqtt_event_group, CONNECTED_BIT, false, true, portMAX_DELAY);
}

void publish(const char *topic){
    esp_mqtt_client_publish(client, topic, defaultMessage, 0, 0, 0);
    ESP_LOGI(TAG, "MQTT_PUBLISH_SENT");
}

void subscribe(const char *topic){
    esp_mqtt_client_subscribe(client, topic, 0);
}

bool subscribeMessageIsReceived(){
    return SubscribeMessageReceived;
}

void updateMessageReceivedStatus(){
    SubscribeMessageReceived = false;
    ESP_LOGI(TAG, "MQTT_SUBSCRIBE_RECEIVED_RESET");
}
