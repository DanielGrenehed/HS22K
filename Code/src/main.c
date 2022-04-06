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
#include "common.h"
#include "buttons.h"
#include "util.h"

/*
#include "nrf.h"
#include "nrf_drv_timer.h"
//#include "bsp.h"
//#include "app_error.h"

const nrf_drv_timer_t TIMER_COUNTER = NRF_DRV_TIMER_INSTANCE(0);


static volatile unsigned long ms_counter = 0;

void timer_counter_event_handler(nrf_timer_event_t event_type, void* p_context) {
    switch (event_type) {
        case NRF_TIMER_EVENT_COMPARE0:
            ms_counter++;
            break;
        default:
            break;

    }
}

void config_timers() {
    nrf_drv_timer_config_t timer_cfg = (nrf_drv_timer_config_t) { 
        .frequency = NRF_TIMER_FREQ_125kHz,
        .mode = NRF_TIMER_MODE_TIMER,
        .bit_width = NRF_TIMER_BIT_WIDTH_16,
        .interrupt_priority = 7,
        .p_context = NULL
    };
    nrf_drv_timer_init(&TIMER_COUNTER, &timer_cfg, timer_counter_event_handler);
    uint32_t time_ticks = nrf_drv_timer_ms_to_ticks(&TIMER_COUNTER, 1); // (1ms)

    nrf_drv_timer_extended_compare(&TIMER_COUNTER, NRF_TIMER_CC_CHANNEL0, time_ticks, NRF_TIMER_SHORT_COMPARE0_CLEAR_MASK, true);
    nrf_drv_timer_enable(&TIMER_COUNTER);
}

unsigned long millis(void) {
    return ms_counter;
}
*/
#define LEDS 1
static uint32_t leds[] = { LED_PIN };

void config_leds() {
    // p0.15 BLED
    for (int i = 0; i < LEDS; i++) nrf_gpio_cfg_output(leds[i]);
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
    config_buttons();
    config_timers();

    enable_all_rows();
    
    /* Toggle LEDs. */
    while (true) {
        handle_buttons();
        if (buttons_ready() && is_button_pressed(0, 1)) {
            if (is_button_pressed(0, 1)) nrf_gpio_pin_set(leds[0]);
            else nrf_gpio_pin_clear(leds[0]);
        } 
        
    }
}

/**
 *@}
 **/

