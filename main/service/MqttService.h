#ifndef ESP_LIGHT_CONTROLLER_MQTTSERVICE_H
#define ESP_LIGHT_CONTROLLER_MQTTSERVICE_H

void openMqttConnection(const char *url);
void publish(const char *topic, const char *message);

#endif
