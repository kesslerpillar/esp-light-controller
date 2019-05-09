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