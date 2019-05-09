//
// Created by nathan.l.gordon on 2019-05-09.
//

#include "PhysicalLight.h"
#include "driver/gpio.h"

#define LED GPIO_NUM_12
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
