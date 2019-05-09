//
// Created by nathan.l.gordon on 2019-05-09.
//

#ifndef ESP_LIGHT_CONTROLLER_WEBLIGHT_H
#define ESP_LIGHT_CONTROLLER_WEBLIGHT_H


#include <lib/api/Light.h>

class WebLight : public Light{
private:
    bool isOn;

public:
    void turnOn() override;

    void turnOff() override;
};


#endif //ESP_LIGHT_CONTROLLER_WEBLIGHT_H
