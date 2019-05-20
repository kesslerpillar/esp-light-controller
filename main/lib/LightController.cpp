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
    if(lightSwitch->isPressed()){
        if (!lightSwitch->isResponded){
            publish(CONFIG_MQTT_PUBLISH_TOPIC);
            lightSwitch->updateRespondedStatus(true);
        }
    } else {
        lightSwitch->updateRespondedStatus(false);
    }
}

void LightController::updateLights() {
    if (light->isOn)
        light->turnOff();
    else
        light->turnOn();
}

void LightController::blinkLight() {
    for(int i = 0; i < 2; i++) {
        light ->turnOn();
        sleep(1);
        light ->turnOff();
        sleep(1);
    }
}
