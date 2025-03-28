/*
 * protocol.h
 *
 *  Created on: 23/07/2024
 *      Author: Clara
 */

#ifndef DRIVERS_MSS_GPIO_PROTOCOL_H_
#define DRIVERS_MSS_GPIO_PROTOCOL_H_

#include <stdint.h>  // Include this header to define uint8_t
#include "ring_buffer.h"

// Enum para os estados do protocolo
typedef enum {
    IDLE,
    ID,
    FUNC,
    DATA,
    CRC
} ProtocolState;

// Defini��o da estrutura Contexto
typedef struct {
    uint8_t id;
    uint32_t timeout;
    uint32_t last_time;
    ProtocolState state;
    uint8_t function;
    uint16_t size;
    RingBuffer buffer;
    uint8_t crc;
    uint32_t count = 0;
} Contexto;

void protocol_poll(Contexto *con, uint8_t data);
void protocol_flush(Contexto *con);
static uint8_t calculate_checksum(const uint8_t* buffer, uint8_t length);
int validate_crc(Contexto* con);
int expected_data_length(Contexto* con);
void process_message(Contexto* con);


#endif /* DRIVERS_MSS_GPIO_PROTOCOL_H_ */

