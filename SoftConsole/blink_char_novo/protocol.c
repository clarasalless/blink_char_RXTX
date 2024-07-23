/*
 * protocol.c
 *
 *  Created on: 23/07/2024
 *      Author: Clara
 */
#include <stdint.h>  // Include this header to define uint8_t
#include "protocol.h"

void protocol_poll(Contexto con, uint8_t data)
{
	if(con.last_time < con.timeout)
	{
		protocol_flush(con);
	}

}

void protocol_flush(Contexto con)
{
	con.context = 0;
	con.timeout = 0;
	con.last_time = 0;
}

