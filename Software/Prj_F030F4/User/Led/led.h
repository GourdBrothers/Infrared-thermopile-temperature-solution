#ifndef __LED_H
#define __LED_H

#include "stm32f0xx.h"

#define LED_OFF                       GPIOA->BSRR = 0x10
#define LED_ON                        GPIOA->BRR  = 0x10 
#define LED_TURN                      GPIOA->ODR ^= 0x10

void LED_Init(void);

#endif
