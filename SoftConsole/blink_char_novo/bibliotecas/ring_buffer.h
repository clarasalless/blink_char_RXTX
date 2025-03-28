/*
 * ring_buffer.h
 *
 *  Created on: 23/07/2024
 *      Author: Clara
 */

#ifndef RING_BUFFER_H_
#define RING_BUFFER_H_

// defines
#define BUFFER_SIZE 255  // Define the size of the ring buffer

// typedefs
typedef struct{
    uint8_t buffer[BUFFER_SIZE];
    int head;
    int tail;
    int count;
} RingBuffer;

void initBuffer(RingBuffer *rb);
int addElement(RingBuffer *rb, uint8_t element);
int removeElement(RingBuffer *rb, int *element);
int bytesInBuffer(RingBuffer *rb);

#endif /* RING_BUFFER_H_ */


