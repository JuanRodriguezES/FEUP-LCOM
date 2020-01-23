#pragma once

#include <lcom/lcf.h>
#include "graphics_card.h"
#include "kbd.h"

#include "Images/alavanca-aberta.xpm"
#include "Images/alavanca-fechada.xpm"

/** @struct Lever
 *  @brief Struct relativa às Alavancas
 *  @var Lever::img
 *  XPM da Alavanca
 *  @var Lever::x
 *  Posição dos x da Alavanca
 *  @var Lever::y
 *  Posição dos y da Alavanca
 *  @var Lever::active
 *  Boleano: 1 se a Alavanca estiver ativada, 0 caso contrário
 */
typedef struct {
  xpm_image_t img;

  int x, y;

  bool active;

} Lever;

#include "Level.h"

/**
 *  @brief Aloca memória e cria a Alavanca
 *  @param x Posição dos x da Alavanca
 *  @param y Posição dos y da Alavanca
 *  @return Alavanca criada
 */
Lever * createLever(int x, int y);

/**
 *  @brief Apresenta a Alavanca no ecrã
 *  @param lever Alavanca a apresentar no ecrã
 */
void draw_lever(Lever * lever);

/**
 *  @brief Remove a Alavanca do ecrã
 *  @param lever Alavanca a remover do ecrã
 */
void clean_lever(Lever * lever);

/**
 *  @brief Ativa uma Alavanca
 *  @param lever Alavanca a ativar
 */
void open_lever(Lever * lever);

/**
 *  @brief Adiciona a Alavanca ao Fundo do Nível
 *  @param lever Alavanca a adicionar ao Fundo do Nível
 */
void add_lever_background(Lever * lever);

/**
 *  @brief Remove a Alavanca do Fundo do Nível
 *  @param lever Alavanca a remover do Fundo do Nível
 */
void remove_lever_background(Lever * lever);

