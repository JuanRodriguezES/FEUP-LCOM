#pragma once

#include <lcom/lcf.h>

/** @struct Queue
 *  @brief Struct relativa à Transmissão/Receção de Informação da Serial Port
 *  @var Queue::front
 *  Índice do primeiro elemento da Queue
 *  @var Queue::rear
 *  Índice do último elemento da Queue
 *  @var Queue::size
 *  Número de elementos da Queue
 *  @var Queue::capacity
 *  Número máximo de elementos da Queue
 *  @var Queue::array
 *  Lista dos elementos da Queue
 */
typedef struct {

  uint8_t front, rear, size; 
  unsigned capacity; 
  uint8_t * array; 

} Queue;

/**
 *  @brief Aloca memória e cria a Queue
 *  @param capacity Número máximo de elementos da Queue
 *  @return Queue criada
 */
Queue * createQueue(unsigned capacity);

/**
 *  @brief Verifica se a Queue está cheia
 *  @param queue Queue a verificar se está cheia
 *  @return 1 se a Queue estiver Cheia, 0 caso contrário
 */
int queueIsFull(Queue * queue);

/**
 *  @brief Verifica se a Queue está vazia
 *  @param queue Queue a verificar se está vazia
 *  @return 1 se a Queue estiver Vazia, 0 caso contrário
 */
int queueIsEmpty(Queue * queue);

/**
 *  @brief Adiciona um Item à Queue
 *  @param queue Queue à qual se vai adicionar o Item
 *  @param item Item a adicionar à Queue
 */
void addToQueue(Queue * queue, uint8_t item);

/**
 *  @brief Remove um Item da Queue
 *  @param queue Queue da qual se vai remover o Item
 *  @return Elemento removido da Queue
 */
uint8_t removeFromQueue(Queue * queue);

/**
 *  @brief Devolve o elemento da frente da Queue
 *  @param queue Queue da qual se vai devolver o elemento da frente
 *  @return Elemento da frente da Queue
 */
int queueFront(Queue * queue);

/**
 *  @brief Devolve o último elemento da Queue
 *  @param queue Queue da qual se vai devolver o último elemento
 *  @return 0 em caso de sucesso, 1 caso contrário
 */
int queueRear(Queue * queue);
