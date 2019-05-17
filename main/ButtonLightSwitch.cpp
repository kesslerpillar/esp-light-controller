#include "ButtonLightSwitch.h"
#include "driver/gpio.h"

#define BUTTON GPIO_NUM_12

ButtonLightSwitch::ButtonLightSwitch() {
    gpio_pad_select_gpio(BUTTON);
    gpio_set_direction(BUTTON, GPIO_MODE_INPUT);
}

bool ButtonLightSwitch::isOn() {
    return gpio_get_level(BUTTON);
}