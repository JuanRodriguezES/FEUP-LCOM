#include "queue.h"
 
Queue * createQueue(unsigned capacity) { 

  Queue * queue = (Queue*) malloc(sizeof(Queue)); 

  queue->capacity = capacity; 
  queue->front = 0x00;
  queue->size = 0;
  queue->rear = capacity - 1; 

  queue->array = (uint8_t *) malloc(queue->capacity * sizeof(uint8_t)); 

  return queue; 
} 
   
int queueIsFull(Queue * queue) {
  return (queue->size == queue->capacity);  
} 


int queueIsEmpty(Queue * queue) {  
  return (queue->size == 0); 
} 

void addToQueue(Queue * queue, uint8_t item) {
  if (queueIsFull(queue)) 
    return; 
  
  queue->rear = (queue->rear + 1) % queue->capacity; 
  queue->array[queue->rear] = item; 
  queue->size = queue->size + 1; 
  
} 

uint8_t removeFromQueue(Queue * queue) { 
  if (queueIsEmpty(queue)) 
    return 0; 
  
  uint8_t item = queue->array[queue->front]; 
  queue->front = (queue->front + 1) % queue->capacity; 
  queue->size = queue->size - 1; 

  return item; 
} 

int queueFront(Queue * queue) { 
  if (queueIsEmpty(queue)) 
    return 0; 
  
  return queue->array[queue->front]; 
} 

int queueRear(Queue * queue) { 
  if (queueIsEmpty(queue)) 
    return 0; 

  return queue->array[queue->rear]; 
} 
