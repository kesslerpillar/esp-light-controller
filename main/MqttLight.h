#ifndef ESP_LIGHT_CONTROLLER_MQTTLIGHT_H
#define ESP_LIGHT_CONTROLLER_MQTTLIGHT_H

#include "lib/api/Light.h"

class MqttLight : public Light{
private:
    bool isOn;

public:
    void turnOn() override;

    void turnOff() override;
};

#endif
