//
// Created by nathan.l.gordon on 2019-05-09.
//

#ifndef ESP_LIGHT_CONTROLLER_BUTTONLIGHTSWITCH_H
#define ESP_LIGHT_CONTROLLER_BUTTONLIGHTSWITCH_H


#include <api/LightSwitch.h>

class ButtonLightSwitch : public LightSwitch{
public:
    ButtonLightSwitch();
    bool isOn() override;
};


#endif //ESP_LIGHT_CONTROLLER_BUTTONLIGHTSWITCH_H
