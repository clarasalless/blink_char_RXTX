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

#define CRC8_POLY 0x07  // Polin�mio para CRC-8 (x^8 + x^2 + x + 1)

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
                con->state = FUNC;
                con->id = data;
            }
            else
            {
                protocol_flush(con);
            }
            break;

        case FUNC:
            con->function = data;
            con->state = DATA;
            break;

        case DATA:
            if (addElement(&con->buffer, data) == -1) {
                // Buffer cheio, tratar erro conforme necess�rio
            }
            // FUNC: Read
			if(con->function == 0x01){
				if(con->count < 4){
					addElement(con->buffer, data); // armazena o endere�o no buffer
					con->count++;
				}
				else
					con->state = CRC;
			}
			// FUNC: Write
			if(con->function == 0x02){
				if(con->count < 4){
					addElement(con->buffer, data); // armazena o endere�o no buffer
					con->count++;
				}
				else if(con->count > 4 && con->count < 7){

				}
			}

//            // Verifica se foi recebido um esc byte
//            if(data == esc_byte){
//            	esc_byte = 1;
//            }
//            // Verifica se o byte seguinte � 0xFF indicando o fim da transmiss�o da mensagem
//            if(esc_byte != 0 && data == 0xFF){
//            	con->state = CRC;
//            }
//            esc_byte = 0; // reseta o valor da vari�vel esc_byte
            break;

        case CRC:
            con->crc = data;
            if (validate_crc(con)) {
                // Mensagem completa e CRC-8 v�lido
                process_message(con);
            } else {
                // CRC-8 inv�lido, tratar erro conforme necess�rio
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

// Fun��o para calcular o CRC-8
static uint8_t calculate_crc8(const uint8_t* buffer, uint8_t length)
{
    uint8_t crc = 0x00;  // Inicializa o CRC com 0
    for (uint8_t i = 0; i < length; ++i) {
        crc ^= buffer[i];  // XOR o byte atual com o CRC

        // Aplica o polin�mio para cada bit do byte
        for (uint8_t j = 0; j < 8; ++j) {
            if (crc & 0x80) {  // Se o bit mais significativo for 1
                crc = (crc << 1) ^ CRC8_POLY;
            } else {
                crc <<= 1;
            }
        }
    }
    return crc;
}

// Fun��o para validar o CRC-8
int validate_crc(Contexto* con)
{
    RingBuffer* buff = &con->buffer;
    if (con->checksum == calculate_crc8(buff->buffer, bytesInBuffer(buff))) {
        return 1;
    } else {
        return 0;
    }
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
