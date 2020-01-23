#include <lcom/lcf.h>

#include <stdint.h>
#include <stdio.h>

#include "i8042.h"
#include "graphics_card.h"
#include "kbd.h"

#include "Images/cursor.xpm"

/** @struct Cursor
 *  @brief Struct relativa ao Cursor
 *  @var Cursor::x
 *  Posição dos x do Cursor
 *  @var Cursor::y
 *  Posição dos y do Cursor
 *  @var Cursor::img
 *  XPM do Cursor
 */
typedef struct {
    int x, y;
    xpm_image_t img;
} Cursor;

/**
 *  @brief Converte um número em Complemento para 2 num número decimal
 *  @param number Número a Converter
 *  @param msb Bit mais significativo do Número
 *  @param pacote Mouse Packet com as informações do Rato
 *  @return Número convertido em decimal
 */
uint16_t convert_2_complement(uint8_t number, uint8_t msb, struct packet * pacote);

/**
 *  @brief Verifica se o Input Buffer está cheio
 *  @return 1 caso o Input Buffer estiver cheio, 0 caso contrário
 */
bool (check_input_buffer)();

/**
 *  @brief Verifica se o Output Buffer está cheio
 *  @return 1 caso o Output Buffer estiver cheio, 0 caso contrário
 */
bool (check_output_buffer)();

/**
 *  @brief Subscreve as interrupções do Rato
 *  @param bit_no Variavél que armazena o valor da IRQ do Rato
 *  @return 0 em caso de sucesso, 1 caso contrário
 */
int (mouse_subscribe_int)(uint8_t *bit_no);

/**
 *  @brief Torna as interrupções do Rato não subscritas
 *  @return 0 em caso de sucesso, 1 caso contrário
 */
int (mouse_unsubscribe_int)();

/**
 *  @brief Controlo das interrupções do Rato
 */
void (mouse_ih)();

/**
 *  @brief Constrói um Mouse Packet com as Informações do Rato
 *  @param pacote Mouse Packet com as informações do Rato contruído
 */
void (buildPacket)(struct packet * pacote);

/**
 *  @brief Ativa a Data Report do Rato
 *  @return 0 em caso de sucesso, 1 caso contrário
 */
int (mouse_enable_data_report)();

/**
 *  @brief Desativa a Data Report do Rato
 *  @return 0 em caso de sucesso, 1 caso contrário
 */
int (mouse_disable_data_report)();

/**
 *  @brief Escreve um comando para o Rato
 *  @param cmd Comando a escrever para o Rato
 *  @param resp Resposta resultante da escrita do comando
 *  @return 0 em caso de sucesso, 1 caso contrário
 */
int(mouse_write_cmd)(uint32_t cmd, uint8_t *resp);

/**
 *  @brief Mete o Rato em modo Stream
 *  @return 0 em caso de sucesso, 1 caso contrário
 */
int (mouse_stream)();

/**
 *  @brief Mete o Rato em modo Remote
 *  @return 0 em caso de sucesso, 1 caso contrário
 */
int (mouse_remote)();

/**
 *  @brief Ativa a Read Data do Rato
 *  @return 0 em caso de sucesso, 1 caso contrário
 */
int (mouse_read_data)();

/**
 *  @brief Aloca memória e cria o Cursor
 *  @return Cursor criado
 */
Cursor * load_cursor();

/**
 *  @brief Controlo do movimento do Cursor
 *  @param pacote Mouse Packet com as informações do Rato
 */
void mouse_update(struct packet * pacote);

/**
 *  @brief Apresenta o Cursor no ecrã
 */
void draw_mouse_cursor();

/**
 *  @brief Remove o Cursor do ecrã
 */
void clean_cursor();

/**
 *  @brief Verifica as colisões do Cursor com os Botões do Main Menu
 *  @return Número identificativo da colisão
 */
unsigned int check_collision_main_menu ();

/**
 *  @brief Verifica as colisões do Cursor com os Botões do Pause Menu
 *  @return Número identificativo da colisão
 */
unsigned int check_collision_pause_menu ();

/**
 *  @brief Verifica as colisões do Cursor com os Botões do Won Menu
 *  @return Número identificativo da colisão
 */
unsigned int check_collision_won_menu();
