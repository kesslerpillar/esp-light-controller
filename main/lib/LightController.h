#ifndef __REVERSE_H__
#define __REVERSE_H__

#include <string>
#include "api/LightSwitch.h"
#include "api/Light.h"
#include <memory>
#include <vector>

/**
 * Trivial class whose only function is to reverse a string.
 * Should use std::reverse instead but want to have example with own class
 */
class LightController
{
    private:
    std::shared_ptr<LightSwitch> lightSwitch;
    std::vector<std::shared_ptr<Light> > lights;
    std::shared_ptr<Light> light;

    public:
        LightController(std::shared_ptr<LightSwitch> &lightSwitch, std::vector<std::shared_ptr<Light> > &lights);
        LightController(std::shared_ptr<Light> &light);

        void updateSwitch();
        void updateLights(const char * lightStatus);

        void blinkLight();
};

// LightController(Input input, Light[] lights)
// if(input.isOn())
// light[0].turnOn();
#endif
