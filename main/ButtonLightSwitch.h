#ifndef ESP_LIGHT_CONTROLLER_BUTTONLIGHTSWITCH_H
#define ESP_LIGHT_CONTROLLER_BUTTONLIGHTSWITCH_H

#include <api/LightSwitch.h>

class ButtonLightSwitch : public LightSwitch{
public:
    ButtonLightSwitch();
    bool isPressed() override;
    void updateRespondedStatus(bool status) override;
};

#endif