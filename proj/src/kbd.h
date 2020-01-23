#include <lcom/lcf.h>
#include <stdint.h>
#include "i8042.h"

/**
 *  @brief Subscreve as interrupções do Teclado
 *  @param bit_no Variavél que armazena o valor da IRQ do Teclado
 *  @return 0 em caso de sucesso, 1 caso contrário
 */
int (kbd_subscribe_int)(uint8_t *bit_no);

/**
 *  @brief Torna as interrupções do Teclado não subscritas
 *  @return 0 em caso de sucesso, 1 caso contrário
 */
int (kbd_unsubscribe_int)();

/**
 *  @brief Função criada para uso de Leituras de Registos
 *  @param port Registo do qual se vai ler
 *  @param value Variável que armazena o valor lido
 *  @return 0 em caso de sucesso, 1 caso contrário
 */
int (utils_sys_inb)(int port, uint8_t *value);

/**
 *  @brief Controlo das interrupções do Teclado
 */
void (kbc_ih)();

/**
 *  @brief Ativação do Teclado
 *  @return 0 em caso de sucesso, 1 caso contrário
 */
int (kbd_enable)();
