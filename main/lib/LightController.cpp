#include <string.h>
#include <cassert>
#include "LightController.h"
#include "service/MqttService.h"

LightController::LightController(std::shared_ptr<LightSwitch>& lightSwitch, std::vector<std::shared_ptr<Light> >& lights) : lightSwitch (lightSwitch), lights (lights){
}

LightController::LightController(std::shared_ptr<Light>& light) : light (light) {
}

void LightController::updateSwitch() {
    for(int i = 0; i < lights.size(); i++){
        if(lightSwitch->isOn()){
            publish(CONFIG_MQTT_PUBLISH_TOPIC, CONFIG_MQTT_PUBLISH_ON_MESSAGE);
        }else{
            publish(CONFIG_MQTT_PUBLISH_TOPIC, CONFIG_MQTT_PUBLISH_OFF_MESSAGE);
        }
    }
}

void LightController::updateLights(const char * lightStatus) {
    for(int i = 0; i < lights.size(); i++){
        if((strcmp(lightStatus, "1") == 0)){
            lights[i]->turnOn();
        }else if (strcmp(lightStatus, "0") == 0) {
            lights[i]->turnOff();
        }
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
