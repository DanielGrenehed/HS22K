/**
 * Copyright (c) 2014 - 2021, Nordic Semiconductor ASA
 *
 * All rights reserved.
 *
 * Redistribution and use in source and binary forms, with or without modification,
 * are permitted provided that the following conditions are met:
 *
 * 1. Redistributions of source code must retain the above copyright notice, this
 *    list of conditions and the following disclaimer.
 *
 * 2. Redistributions in binary form, except as embedded into a Nordic
 *    Semiconductor ASA integrated circuit in a product or a software update for
 *    such product, must reproduce the above copyright notice, this list of
 *    conditions and the following disclaimer in the documentation and/or other
 *    materials provided with the distribution.
 *
 * 3. Neither the name of Nordic Semiconductor ASA nor the names of its
 *    contributors may be used to endorse or promote products derived from this
 *    software without specific prior written permission.
 *
 * 4. This software, with or without modification, must only be used with a
 *    Nordic Semiconductor ASA integrated circuit.
 *
 * 5. Any software provided in binary form under this license must not be reverse
 *    engineered, decompiled, modified and/or disassembled.
 *
 * THIS SOFTWARE IS PROVIDED BY NORDIC SEMICONDUCTOR ASA "AS IS" AND ANY EXPRESS
 * OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED WARRANTIES
 * OF MERCHANTABILITY, NONINFRINGEMENT, AND FITNESS FOR A PARTICULAR PURPOSE ARE
 * DISCLAIMED. IN NO EVENT SHALL NORDIC SEMICONDUCTOR ASA OR CONTRIBUTORS BE
 * LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR
 * CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE
 * GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION)
 * HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT
 * LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT
 * OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 *
 */
/** @file
 *
 * @defgroup blinky_example_main main.c
 * @{
 * @ingroup blinky_example
 * @brief Blinky Example Application main file.
 *
 * This file contains the source code for a sample application to blink LEDs.
 *
 */

#include <stdbool.h>
#include <stdint.h>
#include "nrf_delay.h"
#include "nrf_gpio.h"

#define LEDS 1
static uint32_t leds[] = { 15 };

void config_leds() {
    // p0.15 BLED
    for (int i = 0; i < LEDS; i++) nrf_gpio_cfg_output(leds[i]);
}

#define ROWS 3
static uint32_t rows[] = { NRF_GPIO_PIN_MAP(0,2), NRF_GPIO_PIN_MAP(0,29), NRF_GPIO_PIN_MAP(0,31) };

void config_rows() {
    // output
    for (int i = 0; i < ROWS; i++) nrf_gpio_cfg_output(rows[i]);
}

#define COLUMS 8
static uint32_t columns[] = { NRF_GPIO_PIN_MAP(1,15), NRF_GPIO_PIN_MAP(1,13), NRF_GPIO_PIN_MAP(1,11), NRF_GPIO_PIN_MAP(0,10), NRF_GPIO_PIN_MAP(0,9), NRF_GPIO_PIN_MAP(1, 6), NRF_GPIO_PIN_MAP(1,4), NRF_GPIO_PIN_MAP(0,11)};

void config_cols() {
    // input
    for (int i = 0; i < COLUMS; i++) nrf_gpio_cfg_input(columns[i], NRF_GPIO_PIN_PULLDOWN);   
}

uint8_t get_button_states() {
    uint8_t out = 0;
    for (int i = 0; i < COLUMS; i++) {
        if (nrf_gpio_pin_read(columns[i])) out |= (1 << i);
        
    }
    return out;
}

void config_input() {
    config_rows();
    config_cols();
}

void toggle_led() {
    nrf_gpio_pin_toggle(leds[0]);
}

/**
 * @brief Function for application main entry.
 */
int main(void)
{
    /* Configure board. */
    config_leds();
    config_input();

    nrf_gpio_pin_set(rows[0]);
    nrf_gpio_pin_set(rows[1]);
    nrf_gpio_pin_set(rows[2]);

    /* Toggle LEDs. */
    while (true) {
        if (get_button_states()) {
            nrf_gpio_pin_set(leds[0]);
        } else {
            nrf_gpio_pin_clear(leds[0]);
        }
        nrf_delay_ms(50);
        
    }
}

/**
 *@}
 **/

