#ifndef __LED_H
#define __LED_H

#include "stm32f0xx.h"

#define LED_OFF                       GPIOA->BSRR = 0x40
#define LED_ON                        GPIOA->BRR  = 0x40 
#define LED_TURN                      GPIOA->ODR ^= 0x40

#define LED2_OFF                      GPIOB->BSRR = 0x08
#define LED2_ON                       GPIOB->BRR  = 0x08
#define LED2_TURN                     GPIOB->ODR ^= 0x08

void LED_Init(void);

#endif
