#ifndef ESP_LIGHT_CONTROLLER_PHYSICALLIGHT_H
#define ESP_LIGHT_CONTROLLER_PHYSICALLIGHT_H

#include <lib/api/Light.h>

class PhysicalLight : public Light{
public:
    PhysicalLight();
    void turnOn() override;

    void turnOff() override;
};

#endif
