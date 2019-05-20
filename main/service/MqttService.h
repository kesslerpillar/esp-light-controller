#ifndef ESP_LIGHT_CONTROLLER_MQTTSERVICE_H
#define ESP_LIGHT_CONTROLLER_MQTTSERVICE_H

void openMqttConnection(const char *url);
void publish(const char *topic);
void subscribe(const char *topic);
bool subscribeMessageIsReceived();
void updateMessageReceivedStatus();

#endif
