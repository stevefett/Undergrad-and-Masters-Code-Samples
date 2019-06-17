#include "circularqueue.h"
#include "kerneldata.h"

void AddToQueue(CircularQueuePtr queue, char ch){
    int index = queue->end;
    queue->data[index++] = ch;
    queue->end = index % CIRCULAR_QUEUE_CAPACITY;
}

char RemoveFromQueue(CircularQueuePtr queue){
    int index = queue->start;
    char c = queue->data[index++];
    queue->start = index % CIRCULAR_QUEUE_CAPACITY;
    return c;
}

bool IsQueueEmpty(CircularQueuePtr queue){
    return queue->start == queue->end ? TRUE : FALSE;
}

bool IsQueueFull(CircularQueuePtr queue){
    return FALSE;
}