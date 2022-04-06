#include "leds.h"
#include "nrf_gpio.h"
#include "hs22k_board.h"

static const uint32_t led_pins[] = { LED_PIN };

void config_leds() {
    for (int i = 0; i < LED_COUNT; i++) nrf_gpio_cfg_output(led_pins[i]);
}


void toggle_led(unsigned int led) {
    if (led < LED_COUNT) nrf_gpio_pin_toggle(led_pins[led]);
}

void set_led(unsigned int led) {
    if (led < LED_COUNT) nrf_gpio_pin_set(led_pins[led]);
}

void clear_led(unsigned int led) {
    if (led < LED_COUNT) nrf_gpio_pin_clear(led_pins[led]);
}