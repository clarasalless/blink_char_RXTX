/*
 * ring_buffer.c
 *
 *  Created on: 23/07/2024
 *      Author: Clara
 */
#include <stdint.h>  // Include this header to define uint8_t
#include "ring_buffer.h"

// Initialize the ring buffer
void initBuffer(RingBuffer *rb) {
    rb->head = 0;
    rb->tail = 0;
    rb->count = 0;
}

// Add an element to the ring buffer
int addElement(RingBuffer *rb, uint8_t element) {
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
