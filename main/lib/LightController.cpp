#include "LightController.h"

LightController::LightController(std::shared_ptr<LightSwitch>& lightSwitch, std::vector<std::shared_ptr<Light> >& lights) : lightSwitch (lightSwitch), lights (lights){
}

void LightController::update() {

    for(int i = 0; i < lights.size(); i++){
        if(lightSwitch->isOn()){
            lights[i]->turnOn();
        }else{
            lights[i]->turnOff();
        }
    }

}

void LightController::blinkLight() {
    for(int i = 0; i < 2; i++) {
        lights[0]->turnOn();
        sleep(1);
        lights[0]->turnOff();
        sleep(1);
    }
}