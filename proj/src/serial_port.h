#include <lcom/lcf.h>

#include "serial_port_const.h"
#include "MultiPlayer.h"
#include "queue.h"

/**
 *  @brief Devolve o LSB de um valor especificado
 *  @param val Valor do qual retiramos o LSB
 *  @param lsb Variável em que armazenamos o valor do LSB requerido
 *  @return 0 em caso de sucesso, 1 caso contrário
 */
int(util_get_LSB)(uint16_t val, uint8_t *lsb);

/**
 *  @brief Devolve o MSB de um valor especificado
 *  @param val Valor do qual retiramos o MSB
 *  @param msb Variável em que armazenamos o valor do MSB requerido
 *  @return 0 em caso de sucesso, 1 caso contrário
 */
int(util_get_MSB)(uint16_t val, uint8_t *msb);

/**
 *  @brief Configura o UART para meter o número especificado de bits por char
 *  @param val Número de bits por char a configurar no UART
 *  @return 0 em caso de sucesso, 1 caso contrário
 */
int sp_set_number_of_bits_per_char(uint8_t number_of_bits);

/**
 *  @brief Configura o UART para meter a paridade especificada
 *  @param parity Paridade a configurar no UART
 *  @return 0 em caso de sucesso, 1 caso contrário
 */
int sp_set_parity(uint8_t parity);

/**
 *  @brief Configura o UART para meter o bitrate especificado
 *  @param bitrate Bitrate a configurar no UART
 *  @return 0 em caso de sucesso, 1 caso contrário
 */
int sp_set_bitrate(int bitrate);

/**
 *  @brief Mete os bits da macro especificada a 1 ou 0, consoante o boleano especificado, para o registo IER
 *  @param macro Macro a alterar
 *  @param enable Boleano: 1 se for para meter os bits a 1, 0 caso contrário
 *  @return 0 em caso de sucesso, 1 caso contrário
 */
int sp_enable_ier(uint8_t macro, bool enable);

/**
 *  @brief Mete os bits da macro especificada a 1 ou 0, consoante o boleano especificado, para o registo FCR
 *  @param macro Macro a alterar
 *  @param enable Boleano: 1 se for para meter os bits a 1, 0 caso contrário
 *  @return 0 em caso de sucesso, 1 caso contrário
 */
int sp_enable_fcr(uint8_t macro, bool enable);

/**
 *  @brief Chama todas as funções necessárias para configurar a Serial Port no início do programa
 *  @return 0 em caso de sucesso, 1 caso contrário
 */
int sp_configure_init();

/**
 *  @brief Chama todas as funções necessárias para desativar as Interrupções da Serial Port
 *  @return 0 em caso de sucesso, 1 caso contrário
 */
int sp_configure_end();

/**
 *  @brief Subscreve as interrupções da Serial Port
 *  @param bit_no Variavél que armazena o valor da IRQ da Serial Port
 *  @return 0 em caso de sucesso, 1 caso contrário
 */
int (sp_subscribe_int)(uint8_t *bit_no);

/**
 *  @brief Torna as interrupções da Serial Port não subscritas
 *  @return 0 em caso de sucesso, 1 caso contrário
 */
int (sp_unsubscribe_int)();

/**
 *  @brief Leitura do registo LSR e verificação da possibilidade de escrita deste
 *  @return Boleano: true se puder escrever, false caso contrário
 */
bool sp_check_write();

/**
 *  @brief Leitura do registo LSR e verificação da possibilidade de leitura deste
 *  @return Boleano: true se puder ler, false caso contrário
 */
bool sp_check_read();

/**
 *  @brief Envio de mensagem para a Serial Port
 *  @return 0 em caso de sucesso, 1 caso contrário
 */
int sp_write();

/**
 *  @brief Receção de mensagem da Serial Port
 *  @return 0 em caso de sucesso, 1 caso contrário
 */
int sp_read();

/**
 *  @brief Controlo das interrupções da Serial Port
 *  @return 0 em caso de sucesso, 1 caso contrário
 */
uint8_t (sp_ih)();

/**
 *  @brief Leitura do Primeiro elemento da Receive Queue
 *  @return Primeiro elemento da Receive Queue
 */
uint8_t readFromQueue();

/**
 *  @brief Adiciona elemento à Transmit Queue
 *  @param data Elemento a adicionar à Transmit Queue
 */
void addToTransmitQueue(uint8_t data);

