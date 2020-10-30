
#ifndef RINGBUFFER_H
#define	RINGBUFFER_H

#include <xc.h> // include processor files - each processor file is guarded.  

// define queue type
typedef struct queue_t;

// Read from queue
void* queue_read(queue_t *queue);

// Write to queue
int queue_write(queue_t *queue, void* handle)




#endif	/* RINGBUFFER_H */

