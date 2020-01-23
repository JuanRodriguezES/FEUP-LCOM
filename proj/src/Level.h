#pragma once

#include <lcom/lcf.h>
#include "graphics_card.h"
#include "Enemy.h"
#include "Door.h"
#include "Lever.h"

#include "Images/ArenaWalls.xpm"

#include "Images/Level1.xpm"
#include "Images/Level1_Walls.xpm"
#include "Images/Level2.xpm"
#include "Images/Level2_Walls.xpm"
#include "Images/Level3.xpm"
#include "Images/Level3_Walls.xpm"
#include "Images/Level4.xpm"
#include "Images/Level4_Walls.xpm"
#include "Images/Level5.xpm"
#include "Images/Level5_Walls.xpm"
#include "Images/Level6.xpm"
#include "Images/Level6_Walls.xpm"
#include "Images/Level7.xpm"
#include "Images/Level7_Walls.xpm"
#include "Images/Level8.xpm"
#include "Images/Level8_Walls.xpm"
#include "Images/Level9.xpm"
#include "Images/Level9_Walls.xpm"


#include "Images/ammo.xpm"

/** @struct Ammo
 *  @brief Struct relativa à Munição do Nível
 *  @var Ammo::img 
 *  XPM da Munição
 *  @var Ammo::x
 *  Posição dos x da Munição
 *  @var Ammo::y
 *  Posição dos y da Munição
 */
typedef struct {
  xpm_image_t img;
  unsigned int x;
  unsigned int y;
} Ammo;

/** @struct FinalPos
 *  @brief Struct relativa à Zona Final do Nível
 *  @var FinalPos::posfinalx
 *  Posição dos x da Zona Final
 *  @var FinalPos::posfinaly
 *  Posição dos y da Zona Final
 *  @var FinalPos::lado
 *  Comprimento do lado da Zona Final (x16 pixeis)
 */
typedef struct {
  int posfinalx;
  int posfinaly;
  int lado;
} FinalPos;

/** @struct Level
 *  @brief Struct relativa ao Nível
 *  @var Level::levelnum
 *  Número do Nível
 *  @var Level::level_background
 *  XPM do Fundo do Nível
 *  @var Level::level_walls_xpm
 *  XPM das Paredes do Nível (útil na deteção de colisões)
 *  @var Level::level_back
 *  Apontador para os Bytes de Fundo do Nível
 *  @var Level::level_walls
 *  Apontador para os Bytes das Paredes do Nível
 *  @var Level::finalPos
 *  Apontador para o objeto da Posição Final do Nível
 *  @var Level::ammoList
 *  Array de todos os objetos de Munição existentes no Nível
 *  @var Level::numAmmo
 *  Número de objetos de Munição existentes no Nível
 *  @var Level::doorList
 *  Array de todos os objetos de Portas existentes no Nível
 *  @var Level::numDoors
 *  Número de objetos de Portas existentes no Nível
 *  @var Level::leverList
 *  Array de todos os objetos de Alavancas existentes no Nível
 *  @var Level::numLevers
 *  Número de objetos de Alavancas existentes no Nível
 *  @var Level::enemyList
 *  Array de todos os objetos de Inimigos existentes no Nível
 *  @var Level::numEnemies
 *  Número de objetos de Inimigos existentes no Nível
 */
typedef struct {
  unsigned int levelnum;

  xpm_image_t level_background;
  xpm_image_t level_walls_xpm;

  uint32_t * level_back;
  uint32_t * level_walls;

  FinalPos *finalPos;

  Ammo ** ammoList;
  unsigned int numAmmo;

  Door ** doorList;
  unsigned int numDoors;

  Lever ** leverList;
  unsigned int numLevers;
  
  Enemy ** enemyList;
  unsigned int numEnemies;

} Level;

/**
 *  @brief Aloca memória e cria a Zona Final
 *  @param posfinalx Posição dos x da Zona Final
 *  @param posfinaly Posição dos y da Zona Final
 *  @param posfinalx Lado da Zona Final (x16 bits)
 *  @return Zona Final criada
 */
FinalPos * createFinalPos(int posfinalx, int posfinaly, int lado);

/**
 *  @brief Aloca memória e cria a Munição
 *  @param x Posição dos x da Munição
 *  @param y Posição dos y da Munição
 *  @return Munição criada
 */
Ammo * createAmmo(int x, int y);

/**
 *  @brief Carrega o Nível especificado no parâmetro
 *  @param levelNum Número do Nível a ser carregado
 *  @return Nível carregado
 */
Level * load_level(unsigned int levelNum);

/**
 *  @brief Liberta a memória ocupada pelo Nível
 */
void destroy_level();

/**
 *  @brief Apresenta no ecrã o fundo do Nível
 */
void draw_level_background();

/**
 *  @brief Apresenta no ecrã todas as Munições do Nível
 */
void draw_ammo_level();

/**
 *  @brief Apresenta no ecrã todos os Inimigos do Nível
 */
void draw_enemies_level();

/**
 *  @brief Apresenta no ecrã todas as Portas do Nível
 */
void draw_doors_level();

/**
 *  @brief Apresenta no ecrã todas as Alavancas do Nível
 */
void draw_levers_level();

/**
 *  @brief Remove a Munição do Ecrã quando o Jogador a apanha
 *  @param x Posição dos x da Munição apanhada
 *  @param y Posição dos y da Munição apanhada
 */
void clean_picked_ammo(unsigned int x, unsigned int y);

/**
 *  @brief Remove todas as Munições do Ecrã
 */
void clean_ammo_level();

/**
 *  @brief Apresenta no ecrã uma Porta
 *  @param doors Porta a apresentar no ecrã
 */
void draw_doors(xpm_image_t *doors);

/**
 *  @brief Decide a Porta a abrir 
 */
void decide_doors();
