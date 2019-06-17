#ifndef CIRCULAR_QUEUE_H
#define CIRCULAR_QUEUE_H

#include "kerneldata.h"

#define CIRCULAR_QUEUE_CAPACITY 10

typedef struct _CircularQueue{
    
    int start;
    int end;
    char data[CIRCULAR_QUEUE_CAPACITY];
} CircularQueue;

typedef CircularQueue* CircularQueuePtr;

void AddToQueue(CircularQueuePtr, char);
char RemoveFromQueue(CircularQueuePtr);
bool IsQueueEmpty(CircularQueuePtr);
bool IsQueueFull(CircularQueuePtr);

#endif
