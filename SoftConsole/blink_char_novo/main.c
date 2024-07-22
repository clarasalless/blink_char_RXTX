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

/*==============================================================================
  Private functions.
 */

// defines
#define BUFFER_SIZE 10  // Define the size of the ring buffer

// typedefs
typedef struct {
    int buffer[BUFFER_SIZE];
    int head;
    int tail;
    int count;
} RingBuffer;

typedef struct {
	uint8_t context;
	uint8_t timeout;
	uint8_t last_time;
	uint8_t current_time;
} Contexto;

// functions
static void delay(void);
void Toggle_GPIO_Pin(uint8_t GPIO_MASK);
void initBuffer(RingBuffer *rb);
int addElement(RingBuffer *rb, int element);
int removeElement(RingBuffer *rb, int *element);
int bytesInBuffer(RingBuffer *rb);
void protocol_poll(Contexto con, uint8_t data);
void protocol_flush(Contexto con);


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

// Initialize the ring buffer
void initBuffer(RingBuffer *rb) {
    rb->head = 0;
    rb->tail = 0;
    rb->count = 0;
}

// Add an element to the ring buffer
int addElement(RingBuffer *rb, int element) {
    if (rb->count == BUFFER_SIZE) {
//        printf("Buffer is full. Overwriting oldest element.\n");
        rb->tail = (rb->tail + 1) % BUFFER_SIZE;
        rb->count--;
    }
    rb->buffer[rb->head] = element;
    rb->head = (rb->head + 1) % BUFFER_SIZE;
    rb->count++;
    return 1;  // Success
}

// Remove an element from the ring buffer
int removeElement(RingBuffer *rb, int *element) {
    if (rb->count == 0) {
//        printf("Buffer is empty.\n");
        return 0;  // Failure
    }
    *element = rb->buffer[rb->tail];
    rb->tail = (rb->tail + 1) % BUFFER_SIZE;
    rb->count--;
    return 1;  // Success
}

// Return the number of bytes in the buffer that have not been read yet
int bytesInBuffer(RingBuffer *rb) {
    return rb->count * sizeof(uint8_t);  // Assuming each element is an int
}


void protocol_poll(Contexto con, uint8_t data)
{
	if(con.last_time - con.current_time < con.timeout)
	{
		protocol_flush(con);
	}

}

void protocol_flush(Contexto con)
{
	con.context = 0;
	con.timeout = 0;
	con.last_time = 0;
	con.current_time = 0;
}
