#ifndef __REVERSE_H__
#define __REVERSE_H__

#include <string>
#include "api/LightSwitch.h"
#include "api/Light.h"
#include <memory>

class LightController
{
    private:
    std::shared_ptr<LightSwitch> lightSwitch;
    std::shared_ptr<Light> light;

    public:
        LightController(std::shared_ptr<LightSwitch> &lightSwitch, std::shared_ptr<Light> &light);
        LightController(std::shared_ptr<Light> &light);

        void updateSwitch();
        void updateLights(const char * lightStatus);

        void blinkLight();
};

#endif