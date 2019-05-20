#ifndef LIGHT_CONTROLLER_LIGHT_H
#define LIGHT_CONTROLLER_LIGHT_H

class Light {
    public:
        virtual void turnOn() = 0;
        virtual void turnOff() = 0;
        bool isOn = 0;
};

#endif