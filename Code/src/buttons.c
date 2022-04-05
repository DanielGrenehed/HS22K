#include "buttons.h"
#include "common.h"
#include "nrf_gpio.h"



static uint32_t rows[] = { P002, P029, P031 };
static uint32_t columns[] = { P115, P113, P111, P010, P009, P106, P104, P011 };

/*
    Button Debounce and state macine

    Enable row 0
        get button states
    disable row 0

    enable row 1 
        get button states
    disable row 1

    enable row 2
        get button states
    disable row 2

    repeat
    
*/

typedef struct {
    unsigned long debounce;
    uint8_t state;
} Button;

#define BUTTON_DEBOUNCED 1
#define BUTTON_PRESSED 0

Button button_matrix[BUTTON_COUNT];

typedef enum {
    pause, row_set, read_input, get_states
} button_state_state_machine;

static button_state_state_machine bs_machine = pause;
volatile static uint8_t current_row = 0;

void config_buttons() {
    /*
        Set up row pins as outputs
    */
   for (int i = 0; i < ROW_COUNT; i++) nrf_gpio_cfg_output(rows[i]);

    /*
        Setup columns as inputs with pulldowns
    */
   for (int i = 0; i < COL_COUNT; i++) nrf_gpio_cfg_input(columns[i], NRF_GPIO_PIN_PULLDOWN);

    /*
        Initialize matrix
    */
    for (int i = 0; i < BUTTON_COUNT; i++) button_matrix[i] = (Button){0, 0};
        
}

uint8_t get_button_states() {
    uint8_t out = 0;
    for (int i = 0; i < COL_COUNT; i++) {if (nrf_gpio_pin_read(columns[i])) out |= (1 << i);}
    return out;
}


void set_row() {
    for (int i = 0; i < ROW_COUNT; i++) {
        if (i == current_row) nrf_gpio_pin_set(rows[i]);
        else nrf_gpio_pin_clear(rows[i]);
    }
}

void poll_buttons() {
    /* check button in row if statechanged, 
        if changed and not in debounce
        enter debounce
        if debounce ecceded set debounce flag if state changed
    */
    for (int i = 0; i < COL_COUNT; i++) {
        Button * button = &button_matrix[current_row * COL_COUNT + i];
        uint8_t pcs = nrf_gpio_pin_read(columns[i]);
        if (button->debounce) {
            // if debounce exceeded debounce time
            // else do nothing
        } else if ((button->state & (1 << BUTTON_PRESSED)) != pcs) {

        }
    }
}

void handle_buttons() {
    switch (bs_machine) {
        case pause:
            bs_machine = row_set;
        break;
        case row_set:
            set_row(current_row);
            bs_machine = read_input;
        break;
        case read_input:
            poll_buttons();
            current_row++;
            if (current_row == ROW_COUNT) {
                set_row(current_row); // clear rows
                current_row = 0;
                bs_machine = get_states;
            } else {
                bs_machine = row_set;
            }
        break;
        case get_states:
            /*
                Do nothing until states are read
            */
        break;
    }
}


uint8_t buttons_ready() {
    if (bs_machine == get_states) {
        bs_machine = pause;
        return 1;
    } 
    return 0;
}

uint8_t button_debounced(uint8_t row, uint8_t col) {
    if (row >= ROW_COUNT || col >= COL_COUNT) return 0;
    return (button_matrix[row*COL_COUNT + col].state & (1 << BUTTON_DEBOUNCED));
}

uint8_t is_button_pressed(uint8_t row, uint8_t col) {
    if (row >= ROW_COUNT || col >= COL_COUNT) return 0;
    return (button_matrix[row*COL_COUNT + col].state & (1 << BUTTON_PRESSED));
}

void enable_all_rows() {
    nrf_gpio_pin_set(rows[0]);
    nrf_gpio_pin_set(rows[1]);
    nrf_gpio_pin_set(rows[2]);
}

