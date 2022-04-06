#ifndef COMMON_H
#define COMMON_H

#include "nrf_gpio.h"

/*************
 * Nice!Nano nRF52840 pin configuration
*/

#define P006    NRF_GPIO_PIN_MAP(0,6)
#define P008    NRF_GPIO_PIN_MAP(0,8)

#define P017    NRF_GPIO_PIN_MAP(0,17)
#define P020    NRF_GPIO_PIN_MAP(0,20)

#define P022    NRF_GPIO_PIN_MAP(0,22)
#define P024    NRF_GPIO_PIN_MAP(0,24)
#define P100    NRF_GPIO_PIN_MAP(1,0)

#define P011    NRF_GPIO_PIN_MAP(0,11)
#define P104    NRF_GPIO_PIN_MAP(1,4)
#define P106    NRF_GPIO_PIN_MAP(1,6)

#define P009    NRF_GPIO_PIN_MAP(0,9)
#define P010    NRF_GPIO_PIN_MAP(0,10)
#define P111    NRF_GPIO_PIN_MAP(1,11)
#define P113    NRF_GPIO_PIN_MAP(1,13)
#define P115    NRF_GPIO_PIN_MAP(1,15)
#define P002    NRF_GPIO_PIN_MAP(0,2)
#define P029    NRF_GPIO_PIN_MAP(0,29)
#define P031    NRF_GPIO_PIN_MAP(0,31)

#define P101    NRF_GPIO_PIN_MAP(1,1)
#define P102    NRF_GPIO_PIN_MAP(1,2)
#define P107    NRF_GPIO_PIN_MAP(1,7)

#define P015    NRF_GPIO_PIN_MAP(0,15)

#define BLED_PIN        P015

/************
 * HS22K board definitions
*/

/*
    Button matrix(BM) pins
*/
#define BM_ROW_0        P002
#define BM_ROW_1        P029
#define BM_ROW_2        P031

#define BM_COL_0        P115
#define BM_COL_1        P113
#define BM_COL_2        P111
#define BM_COL_3        P010
#define BM_COL_4        P009
#define BM_COL_5        P106
#define BM_COL_6        P104
#define BM_COL_7        P011

#define BM_ROW_COUNT       3
#define BM_COL_COUNT       8
#define BM_BUTTON_COUNT (BM_ROW_COUNT * BM_COL_COUNT)

#define BM_DEBOUNCE_TIME_MS 6


#define UART_TX         P006
#define UART_RX         P008

#define PIM447_INT_PIN  P102

#define LED_PIN         BLED_PIN
#define LED_COUNT       1

#define SPI_CS_RIGHT    P101
#define SPI_CS_LEFT     P107

#define SPI_SCK         P022
#define SPI_MISO        P024
#define SPI_MOSI        P100

#endif /* ifndef COMMON_H */