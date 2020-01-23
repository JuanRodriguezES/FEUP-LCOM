#pragma once

#include <lcom/lcf.h>
#include "graphics_card.h"
#include "kbd.h"

#include "Images/door_h_2.xpm"
#include "Images/door_h_2_inv.xpm"
#include "Images/door_h_3.xpm"
#include "Images/door_h_3_inv.xpm"
#include "Images/door_v_2.xpm"
#include "Images/door_v_2_inv.xpm"
#include "Images/door_v_3.xpm"
#include "Images/door_v_3_inv.xpm"

/** @struct Door
 *  @brief Struct relativa às Portas do Nível
 *  @var Door::img 
 *  XPM da Porta
 *  @var Door::x
 *  Posição dos x da Porta
 *  @var Door::y
 *  Posição dos y da Porta
 *  @var Door::direction
 *  Direção para a qual a Porta está virada
 *  @var Door::longDoor
 *  Boleano: 1 se o comprimento da Porta ocupar 96 bits e 0 se ocupar 64 bits
 *  @var Door::active
 *  Boleano: 1 se a Porta estiver ativa(fechada) e 0 se estiver inativa(aberta)
 */
typedef struct {
  xpm_image_t img;

  int x, y;

  Direction direction;

  bool longDoor;

  bool active;

} Door;

#include "Level.h"

/**
 *  @brief Aloca memória e cria a Porta
 *  @param x Posição dos x da Porta
 *  @param y Posição dos y da Porta
 *  @param direction Direção para a qual a Porta está virada
 *  @param longDoor Boleano: 1 se o comprimento da Porta ocupar 96 bits e 0 se ocupar 64 bits
 *  @return Porta criada
 */
Door * createDoor(int x, int y, Direction direction, bool longDoor);

/**
 *  @brief Apresenta a Porta no ecrã
 *  @param door Porta a apresentar no ecrã
 */
void draw_door(Door * door);

/**
 *  @brief Remove do ecrã a Porta
 *  @param door Porta a remover do ecrã
 */
void clean_door(Door * door);

/**
 *  @brief Abre uma Porta (torna-a inativa)
 *  @param door Porta a abrir
 */
void open_door(Door * door);

/**
 *  @brief Adiciona a Porta ao Fundo do Nível
 *  @param door Porta a adicionar ao Fundo do Nível
 */
void add_door_background(Door * door);

/**
 *  @brief Remove a Porta do Fundo do Nível
 *  @param door Porta a remover do Fundo do Nível
 */
void remove_door_background(Door * door);

