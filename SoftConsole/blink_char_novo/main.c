/*******************************************************************************
 *
 *
 * Simple SmartFusion2 Microcontroller subsystem (MSS) GPIO example program.
 *
 *
 */
#include "drivers/mss_gpio/mss_gpio.h"
#include "drivers/mss_uart/mss_uart.h"
#include "CMSIS/system_m2sxxx.h"
#include "protocol.h"
#include "ring_buffer.h"

/*==============================================================================
  Private functions.
 */

// functions
static void delay(void);
void Toggle_GPIO_Pin(uint8_t GPIO_MASK);

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
    
    /*
     * Configure MSS GPIOs.
     */
    MSS_GPIO_config( MSS_GPIO_0 , MSS_GPIO_OUTPUT_MODE );
    MSS_GPIO_config( MSS_GPIO_1 , MSS_GPIO_OUTPUT_MODE );
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
    		delay();
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




