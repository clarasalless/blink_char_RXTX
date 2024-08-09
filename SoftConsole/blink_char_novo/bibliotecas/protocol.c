/*
 * protocol.c
 *
 *  Created on: 23/07/2024
 *      Author: Clara
 */
#include <stdint.h>  // Include this header to define uint8_t
#include "protocol.h"
#include "timer_utils.h"
#include "ring_buffer.h"

void protocol_poll(Contexto* con, uint8_t data)
{
	    // Verificar timeout
	    if ((Timer_get_tick() - con->last_time) > con->timeout) {
	        protocol_flush(con);  // Resetar o estado do protocolo
	    }

	    con->last_time = Timer_get_tick();  // Atualizar o �ltimo tempo de recebimento

	    switch (con->state) {
	        case IDLE:
	            if (data == 0xAA) { // Supondo que 0xAA seja o byte inicial esperado
	                con->state = ID;
	                con->context = data;
	            }
	            else
	            {
	            	protocol_flush(con);
	            }
	            break;

	        case ID:
	            con->context = data;
	            con->state = FUNC;
	            break;

	        case FUNC:
	            con->function = data;
	            con->state = DATA;
	            break;

	        case DATA:
	            if (addElement(&con->buffer, data) == -1) {
	                // Buffer cheio, tratar erro conforme necess�rio
	            }
	            // Checar se todos os dados esperados foram recebidos
	            if (bytesInBuffer(&con->buffer) >= expected_data_length(con)) {
	                con->state = CHECKSUM;
	            }
	            break;

	        case CHECKSUM:
	        	con->checksum = data;
	            if (validate_checksum(con)) {
	                // Mensagem completa e checksum v�lido
	                process_message(con);
	            } else {
	                // Checksum inv�lido, tratar erro conforme necess�rio
	            }
	            con->state = IDLE;
	            break;

	        default:
	            con->state = IDLE;
	            break;
	    }
}
// Apaga os dados caso a mensagem precise ser deletada
void protocol_flush(Contexto* con)
{
    initBuffer(&con->buffer);
    con->state = IDLE;
}

static uint8_t calculate_checksum(const uint8_t* buffer, uint8_t length)
{
    uint8_t checksum = 0;
    for(uint8_t i = 0; i < length; ++i)
    {
        checksum += buffer[i];
    }
    return checksum;
}
// Fun��o para validar o checksum
int validate_checksum(Contexto* con)
{
	RingBuffer* buff = &con->buffer;
    if(con->checksum == calculate_checksum(buff->buffer, bytesInBuffer(buff)))
    {
    	return 1;
    }
    else
    	return 0;
}

// Fun��o para retornar o comprimento esperado dos dados com base no contexto
int expected_data_length(Contexto* con)
{
    // Implementar l�gica para determinar o comprimento esperado dos dados
    // com base no contexto ou fun��o
    return 10; // Exemplo de valor fict�cio
}

// Fun��o para processar a mensagem completa
void process_message(Contexto* con)
{
    // Implementar processamento da mensagem completa
}
