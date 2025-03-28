/*
 * timer_utils.h
 *
 *  Created on: 30/07/2024
 *      Author: Clara
 */

#ifndef BIBLIOTECAS_TIMER_UTILS_H_
#define BIBLIOTECAS_TIMER_UTILS_H_

#include "../drivers/mss_timer/mss_timer.h"
#include "../CMSIS/system_m2sxxx.h"

// Funções para inicialização e delay
void Timer_init(void);
void Timer_delay_ms(uint32_t delay_ms);
//void Timer_delay_us(uint32_t delay_us);
uint32_t Timer_get_tick(void);

#endif /* BIBLIOTECAS_TIMER_UTILS_H_ */

