#include <string.h>
#include <cassert>
#include <esp_log.h>
#include <stdio.h>
#include "LightController.h"
#include "service/MqttService.h"

LightController::LightController(std::shared_ptr<LightSwitch>& lightSwitch, std::shared_ptr<Light>& light) : lightSwitch (lightSwitch), light (light){
}

LightController::LightController(std::shared_ptr<Light>& light) : light (light) {
}

void LightController::updateSwitch() {
    if(lightSwitch->isOn()){
        publish(CONFIG_MQTT_PUBLISH_TOPIC);
    }
}

void LightController::updateLights(const char * lightStatus) {
    if(strcmp(lightStatus, CONFIG_LIGHT_ON_CODE) == 0){
        light->turnOn();
    }else if (strcmp(lightStatus, CONFIG_LIGHT_OFF_CODE) == 0) {
        light->turnOff();
    }
}

void LightController::blinkLight() {
    for(int i = 0; i < 2; i++) {
        light ->turnOn();
        sleep(1);
        light ->turnOff();
        sleep(1);
    }
}
