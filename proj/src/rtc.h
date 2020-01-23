#include <lcom/lcf.h>

#include "rtc_const.h"

/**
 *  @brief Proibe as atualizações do RTC
 *  @param enable Boleano: 1 se o RTC estiver ativado, 0 caso contrário
 *  @return 0 em caso de sucesso, 1 caso contrário
 */
int inhibit_updates(bool enable);

/**
 *  @brief Ativa as atualizações do RTC
 *  @param enable Boleano: 1 se o RTC estiver ativado, 0 caso contrário
 *  @return 0 em caso de sucesso, 1 caso contrário
 */
int enable_update_interrupts(bool enable);

/**
 *  @brief Subscreve as interrupções do RTC
 *  @param bit_no Variavél que armazena o valor da IRQ do RTC
 *  @return 0 em caso de sucesso, 1 caso contrário
 */
int (rtc_subscribe_int)(uint8_t *bit_no);

/**
 *  @brief Torna as interrupções do RTC não subscritas
 *  @return 0 em caso de sucesso, 1 caso contrário
 */
int (rtc_unsubscribe_int)();

/**
 *  @brief Controlo das interrupções do RTC
 */
void (rtc_ih)();

/**
 *  @brief Ativa o RTC
 *  @return 0 em caso de sucesso, 1 caso contrário
 */
int rtc_enable();

/**
 *  @brief Desativa o RTC
 *  @return 0 em caso de sucesso, 1 caso contrário
 */
int rtc_disable();

/**
 *  @brief Realiza a espera até receção de um RTC válido
 *  @return 0 em caso de sucesso, 1 caso contrário
 */
int wait_valid_rtc();

/**
 *  @brief Realiza a leitura de um registo do RTC
 *  @param reg Registo do qual se realiza a leitura
 *  @return 0 em caso de sucesso, 1 caso contrário
 */
int rtc_read(uint8_t reg);

/**
 *  @brief Realiza a conversão de um número BCD num número decimal
 *  @param bcdNum Número BCD a converter
 *  @return Número convertido em decimal
 */
uint8_t convert_from_bcd (uint8_t bcdNum);

/**
 *  @brief Carrega o RTC - Leitura dos Dados
 */
void LoadRtc();

