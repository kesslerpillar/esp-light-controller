//
// Created by nathan.l.gordon on 2019-05-09.
//

#include "WebLight.h"
#include "sdkconfig.h"
#include "service/wifi_service.h"

void WebLight::turnOn() {
    if(!isOn) {
        getRequest(CONFIG_TURN_ON_LIGHT_URL);
        isOn = true;
    }
}

void WebLight::turnOff() {
    if(isOn) {
        getRequest(CONFIG_TURN_OFF_LIGHT_URL);
        isOn = false;
    }
}
