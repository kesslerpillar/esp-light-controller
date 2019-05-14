#ifndef ESP_LIGHT_CONTROLLER_WIFI_SERVICE_H
#define ESP_LIGHT_CONTROLLER_WIFI_SERVICE_H
#include "esp_err.h"

void setupWiFi();
esp_err_t config_connect();
void getRequest(const char *url);

#endif
