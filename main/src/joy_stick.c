#include "joy_stick.h"

esp_err_t joystick_init(joystick_t* joystick) {
    // Configura ADC1
    adc1_config_width(ADC_WIDTH_BIT_12);
    adc1_config_channel_atten(joystick->x_channel, ADC_ATTEN_DB_11);
    adc1_config_channel_atten(joystick->y_channel, ADC_ATTEN_DB_11);

    // Configura GPIO del pulsante
    gpio_config_t io_conf = {
        .pin_bit_mask = (1ULL << joystick->sw_gpio),
        .mode = GPIO_MODE_INPUT,
        .pull_up_en = GPIO_PULLUP_ENABLE,
        .pull_down_en = GPIO_PULLDOWN_DISABLE,
        .intr_type = GPIO_INTR_DISABLE
    };
    return gpio_config(&io_conf);
}

esp_err_t joystick_read(joystick_t* joystick, joystick_state_t* state) {
    state->x_value = adc1_get_raw(joystick->x_channel);
    state->y_value = adc1_get_raw(joystick->y_channel);
    state->button_pressed = (gpio_get_level(joystick->sw_gpio) == 0); // attivo basso
    return ESP_OK;
}

