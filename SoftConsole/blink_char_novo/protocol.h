/*
 * protocol.h
 *
 *  Created on: 23/07/2024
 *      Author: Clara
 */

#ifndef DRIVERS_MSS_GPIO_PROTOCOL_H_
#define DRIVERS_MSS_GPIO_PROTOCOL_H_



#endif /* DRIVERS_MSS_GPIO_PROTOCOL_H_ */

#include <stdint.h>  // Include this header to define uint8_t

typedef struct {
	uint8_t context;
	uint8_t timeout;
	uint8_t last_time;
	uint8_t state;
	uint8_t function;
} Contexto;

void protocol_poll(Contexto con, uint8_t data);
void protocol_flush(Contexto con);
