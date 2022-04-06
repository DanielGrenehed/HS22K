#include "key_input.h"
#include "common.h"

static const uint32_t button_matrix_row_pins[] = { P002, P029, P031 };
static const uint32_t button_matrix_col_pins[] = { P115, P113, P111, P010, P009, P106, P104, P011};

uint8_t get_button_states() {
    uint8_t out = 0;
    for (int i = 0; i < COL_COUNT; i++) if (nrf_gpio_pin_read(button_matrix_col_pins[i])) out |= (1 << i);
    return out;
}

void enable_all_rows() {
    for (int i = 0; i < ROW_COUNT; i++) nrf_gpio_pin_set(button_matrix_row_pins[i]);
}

void clear_all_rows() {
    for (int i = 0; i < ROW_COUNT; i++) nrf_gpio_pin_clear(button_matrix_row_pins[i]);
}

void config_input() {
    /* 
        Setup matrix pins 
    */
    for (int i = 0; i < ROW_COUNT; i++) nrf_gpio_cfg_output(button_matrix_row_pins[i]);
    for (int i = 0; i < COL_COUNT; i++) nrf_gpio_cfg_input(button_matrix_col_pins[i], NRF_GPIO_PIN_PULLDOWN); 

}

