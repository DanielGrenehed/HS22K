#ifndef COMMON_H
#define COMMON_H

#include "nrf_gpio.h"

/*
    Row pins
*/
#define P002 NRF_GPIO_PIN_MAP(0,2)
#define P029 NRF_GPIO_PIN_MAP(0,29)
#define P031 NRF_GPIO_PIN_MAP(0,31)

/*
    Column pins
*/
#define P115 NRF_GPIO_PIN_MAP(1,15)
#define P113 NRF_GPIO_PIN_MAP(1,13)
#define P111 NRF_GPIO_PIN_MAP(1,11)
#define P010 NRF_GPIO_PIN_MAP(0,10)
#define P009 NRF_GPIO_PIN_MAP(0,9)
#define P106 NRF_GPIO_PIN_MAP(1,6)
#define P104 NRF_GPIO_PIN_MAP(1,4)
#define P011 NRF_GPIO_PIN_MAP(0,11)

#define P102 NRF_GPIO_PIN_MAP(1,2)
#define P015 NRF_GPIO_PIN_MAP(0,15)

#define P101 NRF_GPIO_PIN_MAP(1,1)
#define P107 NRF_GPIO_PIN_MAP(1,7)
#define P017 NRF_GPIO_PIN_MAP(0,17)
#define P020 NRF_GPIO_PIN_MAP(0,20)
#define P006 NRF_GPIO_PIN_MAP(0,6)
#define P008 NRF_GPIO_PIN_MAP(0,8)

#define P022 NRF_GPIO_PIN_MAP(0,22)
#define P024 NRF_GPIO_PIN_MAP(0,24)
#define P100 NRF_GPIO_PIN_MAP(1,0)

#define UART_TX P006
#define UART_RX P008

#define PIM447_INT_PIN P102

#define LED_PIN P015

#define SPI_CS_RIGHT P101
#define SPI_CS_LEFT P107

#define SPI_SCK P022
#define SPI_MISO P024
#define SPI_MOSI P100


#endif /* ifndef COMMON_H */