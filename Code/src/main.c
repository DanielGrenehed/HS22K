/*

*/

#include <stdbool.h>
#include <stdint.h>

#include "nrf_delay.h"

#include "hs22k_board.h"
#include "key_input.h"
#include "leds.h"


int main(void)
{
    /* Configure board. */
    config_leds();
    config_input();

    /* Toggle LEDs. */
    while (true) {
        handle_button_matrix();

        if (is_button_pressed(0, 1)) set_led(0);
        else clear_led(0);

        nrf_delay_ms(10);
        
    }
}
