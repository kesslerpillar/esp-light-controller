#include "PhysicalLight.h"
#include "driver/gpio.h"

#define LED GPIO_NUM_15

const int ON = 0;
const int OFF = 1;

PhysicalLight::PhysicalLight() {
    gpio_pad_select_gpio(LED);
    gpio_set_direction(LED, GPIO_MODE_OUTPUT);
    turnOff();
}

void PhysicalLight::turnOn() {
    gpio_set_level(LED, ON);
    isOn = 1;
}

void PhysicalLight::turnOff() {
    gpio_set_level(LED, OFF);
    isOn = 0;
}
