#include "PhysicalLight.h"
#include "driver/gpio.h"

#define LED GPIO_NUM_15
#define OFF 1
#define ON 0

PhysicalLight::PhysicalLight() {
    gpio_pad_select_gpio(LED);
    gpio_set_direction(LED, GPIO_MODE_OUTPUT);
    turnOff();
}

void PhysicalLight::turnOn() {
    gpio_set_level(LED, ON);
}

void PhysicalLight::turnOff() {
    gpio_set_level(LED, OFF);
}
