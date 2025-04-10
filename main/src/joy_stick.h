#ifndef JOYSTICK_H_
#define JOYSTICK_H_

#include "driver/adc.h"
#include "driver/gpio.h"

typedef struct {
    adc1_channel_t x_channel;
    adc1_channel_t y_channel;
    gpio_num_t sw_gpio;
} joystick_t;

typedef struct {
    int x_value;       // 0 - 4095
    int y_value;       // 0 - 4095
    bool button_pressed;
} joystick_state_t;

esp_err_t joystick_init(joystick_t* joystick);
esp_err_t joystick_read(joystick_t* joystick, joystick_state_t* state);

#endif // JOYSTICK_H_

