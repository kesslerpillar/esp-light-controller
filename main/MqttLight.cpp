#include "MqttLight.h"
#include "sdkconfig.h"
#include "service/MqttService.h"

void MqttLight::turnOn() {
    if(!isOn) {
        publish(CONFIG_MQTT_BROKER_URL, CONFIG_MQTT_PUBLISH_TOPIC, CONFIG_MQTT_PUBLISH_ON_MESSAGE);
        isOn = true;
    }
}

void MqttLight::turnOff() {
    if(isOn) {
        publish(CONFIG_MQTT_BROKER_URL, CONFIG_MQTT_PUBLISH_TOPIC, CONFIG_MQTT_PUBLISH_OFF_MESSAGE);
        isOn = false;
    }
}
