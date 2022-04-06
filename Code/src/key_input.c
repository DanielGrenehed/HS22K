#include "key_input.h"
#include "hs22k_board.h"

static const uint32_t button_matrix_row_pins[] = { BM_ROW_0, BM_ROW_1, BM_ROW_2 };
static const uint32_t button_matrix_col_pins[] = { BM_COL_0, BM_COL_1, BM_COL_2, BM_COL_3, BM_COL_4, BM_COL_5, BM_COL_6, BM_COL_7};

typedef struct {
    unsigned long debounce;
    uint8_t state;
} Button;

static Button button_matrix[BM_BUTTON_COUNT];
static volatile uint8_t active_row = 0;

#define BM_PIN_IS_HIGH(i) nrf_gpio_pin_read(button_matrix_col_pins[i])
#define BM_SET_PIN(i) nrf_gpio_pin_set(button_matrix_row_pins[i])
#define BM_CLEAR_PIN(i) nrf_gpio_pin_clear(button_matrix_row_pins[i])

#define BUTTON_DEBOUNCED 1
#define BUTTON_PRESSED 0

#define BUTTON_STATE(row, col) button_matrix[row*BM_COL_COUNT + col].state

/* 
    Sets all row pins high
*/
void enable_all_rows() {
    for (int i = 0; i < BM_ROW_COUNT; i++) BM_SET_PIN(i);
}

/*
    Sets all row pins low
*/
void clear_all_rows() {
    for (int i = 0; i < BM_ROW_COUNT; i++) BM_CLEAR_PIN(i);
}

/*
    Disables all rows but row, and sets row high
*/
void set_row(uint8_t row) {
    for (int i = 0; i < BM_ROW_COUNT; i++) {
        if (i != row) BM_CLEAR_PIN(i);
        else BM_SET_PIN(i);
    }
}

void poll_cols() {
    for (int col = 0; col < BM_COL_COUNT; col++) {
        Button *btn = &button_matrix[active_row*BM_COL_COUNT + col];
        uint8_t btn_prs = BM_PIN_IS_HIGH(col);
        if (!btn->debounce && (btn->state & (1 << BUTTON_PRESSED)) != btn_prs) {
            // set debounce mode
            btn->debounce = BM_DEBOUNCE_TIME_MS; // BM_DEBOUNCE_TIME_MS -> millis()
        } else if (12 - btn->debounce >= BM_DEBOUNCE_TIME_MS) { // 12-> millis()
            if ((btn->state & (1 << BUTTON_PRESSED)) != btn_prs) {
                btn->state = btn_prs | (1 << BUTTON_DEBOUNCED);
            }
            btn->debounce = 0;
        }
    }
}

void handle_button_matrix() {
    /*
        run state machine
    */
    for (int i = 0; i < BM_ROW_COUNT; i++) {
        active_row = i;
        set_row(active_row);
        poll_cols();
    }
}

uint8_t is_button_debounced(uint8_t row, uint8_t col) {
    if (BUTTON_STATE(row, col) & (1 << BUTTON_DEBOUNCED)) {
        BUTTON_STATE(row, col) &= ~(1 << BUTTON_DEBOUNCED);
        return 1;
    }
    return 0;
}

uint8_t is_button_pressed(uint8_t row, uint8_t col) {
    if (BUTTON_STATE(row, col) & (1 << BUTTON_PRESSED)) return 1;
    return 0;
}

/*
    Returns a byte with the states of the column pins
*/
uint8_t get_button_states() {
    uint8_t out = 0;
    for (int i = 0; i < BM_COL_COUNT; i++) if (BM_PIN_IS_HIGH(i)) out |= (1 << i);
    return out;
}



/* 
    Setup matrix pins 
    and initialize button matrix
 */
void config_input() {
    for (int i = 0; i < BM_ROW_COUNT; i++) nrf_gpio_cfg_output(button_matrix_row_pins[i]);
    for (int i = 0; i < BM_COL_COUNT; i++) nrf_gpio_cfg_input(button_matrix_col_pins[i], NRF_GPIO_PIN_PULLDOWN); 

    for (int i = 0; i < BM_BUTTON_COUNT; i++) button_matrix[i] = (Button){0,0};
}

