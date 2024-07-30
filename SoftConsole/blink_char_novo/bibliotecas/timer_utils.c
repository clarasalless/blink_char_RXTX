/*
 * timer_utils.c
 *
 *  Created on: 30/07/2024
 *      Author: Clara
 */
#include "timer_utils.h"

uint32_t timer_ticks = 0;

// Handler do Timer1 que incrementa a variável de ticks
void Timer1_IRQHandler(void)
{
	MSS_TIM1_clear_irq();
	timer_ticks++;

}

// Inicializa o timer
void Timer_init(void)
{
    MSS_TIM1_init(MSS_TIMER_PERIODIC_MODE);
    MSS_TIM1_load_immediate(50000); // Configurar para 1ms com clock de 50MHz
    MSS_TIM1_enable_irq();
    MSS_TIM1_start();
}

// Função de delay em milissegundos
void Timer_delay_ms(uint32_t delay_ms)
{
    uint32_t start_ticks = timer_ticks;
    while ((timer_ticks - start_ticks) < delay_ms)
    {
        // Aguardar
    }
}

uint32_t Timer_get_tick(void)
{
	return timer_ticks;
}

