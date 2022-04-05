#include "util.h"
#include "nrf.h"
#include "nrf_drv_timer.h"

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
    nrf_drv_timer_config_t timer_cfg = NRFX_TIMER_DEFAULT_CONFIG;
    nrf_drv_timer_init(&TIMER_COUNTER, &timer_cfg, timer_counter_event_handler);
    uint32_t time_ticks = nrf_drv_timer_ms_to_ticks(&TIMER_COUNTER, 1); // (1ms)

    nrf_drv_timer_extended_compare(&TIMER_COUNTER, NRF_TIMER_CC_CHANNEL0, time_ticks, NRF_TIMER_SHORT_COMPARE0_CLEAR_MASK, true);
    nrf_drv_timer_enable(&TIMER_COUNTER);
}

unsigned long millis(void) {
    return ms_counter;
}