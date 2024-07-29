/*******************************************************************************
 *
 *
 * Simple SmartFusion2 Microcontroller subsystem (MSS) GPIO example program.
 *
 *
 */
#include "drivers/mss_gpio/mss_gpio.h"
#include "drivers/mss_uart/mss_uart.h"
#include "drivers/mss_timer/mss_timer.h"
#include "CMSIS/system_m2sxxx.h"
#include "bibliotecas/protocol.h"
#include "bibliotecas/ring_buffer.h"

/*==============================================================================
  Private functions.
 */

// functions
static void delay(void);
void Toggle_GPIO_Pin(uint8_t GPIO_MASK);
int count = 0;
//uint32_t tim_count;

/*==============================================================================
 * main() function.
 */
int main()
{
	int bytes_in_buffer = 0;
	uint8_t message = 0xAA;
	uint8_t rx_buff;
	uint32_t rx_idx  = 0;

	RingBuffer rBuff;

	initBuffer(&rBuff);

//	int element;
//	removeElement(&rBuff, &element);

    /*
     * Initialize MSS GPIOs.
     */
    MSS_GPIO_init();
    MSS_UART_init(&g_mss_uart0,
            MSS_UART_57600_BAUD,
            MSS_UART_DATA_8_BITS | MSS_UART_NO_PARITY | MSS_UART_ONE_STOP_BIT);
    MSS_TIM1_init(MSS_TIMER_PERIODIC_MODE);
    /*
     * Configure MSS GPIOs.
     */
    MSS_GPIO_config( MSS_GPIO_0 , MSS_GPIO_OUTPUT_MODE );
    MSS_GPIO_config( MSS_GPIO_1 , MSS_GPIO_OUTPUT_MODE );


//    Configurando o timer
    MSS_TIM1_enable_irq();
    MSS_TIM1_load_immediate(50000);
    MSS_TIM1_start();

    /*
     * Infinite loop.
     */
    for(;;)
    {

//    	Transmitindo a mensagem
    	MSS_UART_polled_tx(&g_mss_uart0, &message, 1);
    	Toggle_GPIO_Pin(MSS_GPIO_0_MASK);
    	int count = 10;
    	while(count > 0)
    	{
//    		delay();
    		count--;
    	}

//    	Recebendo a mensagem
    	while(MSS_UART_get_rx(&g_mss_uart0, &rx_buff, sizeof(rx_buff)) == 0){
    		continue;
    	}
    	addElement(&rBuff, rx_buff);
    	Toggle_GPIO_Pin(MSS_GPIO_1_MASK);


    	bytes_in_buffer = bytesInBuffer(&rBuff);
    }
    
    return 0;
}

/*==============================================================================
  Delay between displays of the watchdog counter value.
 */
static void delay(void)
{
    volatile uint32_t delay_count = SystemCoreClock / 512u;
    
    while(delay_count > 0u)
    {
        --delay_count;
    }
}

/*==============================================================================
  Muda o estado do GPIO de acordo com a MASK passada.
 */
void Toggle_GPIO_Pin(uint8_t GPIO_MASK)
{
    uint32_t gpio_pattern;
    /*
     * Decrement delay counter.
     */
    delay();

    /*
     * Toggle GPIO output pattern by doing an exclusive OR of all
     * pattern bits with ones.
     */
    gpio_pattern = MSS_GPIO_get_outputs();
    gpio_pattern ^= GPIO_MASK;
    MSS_GPIO_set_outputs( gpio_pattern );

}

void Timer1_IRQHandler(void)
{
	MSS_TIM1_clear_irq();
	count++;

}




