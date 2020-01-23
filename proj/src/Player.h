#pragma once

#include <lcom/lcf.h>
#include "graphics_card.h"
#include "kbd.h"
#include "Level.h"

#include "Images/player_idle_0.xpm"
#include "Images/player_idle_1.xpm"
#include "Images/player_idle_2.xpm"
#include "Images/player_idle_3.xpm"
#include "Images/player_idle_4.xpm"
#include "Images/player_reload_0.xpm"
#include "Images/player_reload_1.xpm"
#include "Images/player_reload_2.xpm"
#include "Images/player_reload_3.xpm"
#include "Images/player_reload_4.xpm"
#include "Images/player_reload_5.xpm"
#include "Images/player_shoot_0.xpm"
#include "Images/player_shoot_1.xpm"
#include "Images/player_shoot_2.xpm"

#include "Images/Blue/player_idle_0_blue.xpm"
#include "Images/Blue/player_idle_1_blue.xpm"
#include "Images/Blue/player_idle_2_blue.xpm"
#include "Images/Blue/player_idle_3_blue.xpm"
#include "Images/Blue/player_idle_4_blue.xpm"
#include "Images/Blue/player_reload_0_blue.xpm"
#include "Images/Blue/player_reload_1_blue.xpm"
#include "Images/Blue/player_reload_2_blue.xpm"
#include "Images/Blue/player_reload_3_blue.xpm"
#include "Images/Blue/player_reload_4_blue.xpm"
#include "Images/Blue/player_reload_5_blue.xpm"
#include "Images/Blue/player_shoot_0_blue.xpm"
#include "Images/Blue/player_shoot_1_blue.xpm"
#include "Images/Blue/player_shoot_2_blue.xpm"

#include "Images/Red/player_idle_0_red.xpm"
#include "Images/Red/player_idle_1_red.xpm"
#include "Images/Red/player_idle_2_red.xpm"
#include "Images/Red/player_idle_3_red.xpm"
#include "Images/Red/player_idle_4_red.xpm"
#include "Images/Red/player_reload_0_red.xpm"
#include "Images/Red/player_reload_1_red.xpm"
#include "Images/Red/player_reload_2_red.xpm"
#include "Images/Red/player_reload_3_red.xpm"
#include "Images/Red/player_reload_4_red.xpm"
#include "Images/Red/player_reload_5_red.xpm"
#include "Images/Red/player_shoot_0_red.xpm"
#include "Images/Red/player_shoot_1_red.xpm"
#include "Images/Red/player_shoot_2_red.xpm"

/** @struct Player
 *  @brief Struct relativa ao Jogador
 *  @var Player::img 
 *  XPM do Jogador
 *  @var Player::x
 *  Posição dos x do Jogador
 *  @var Player::y
 *  Posição dos y do Jogador
 *  @var Player::xspeed
 *  Velocidade na direção horizontal do Jogador
 *  @var Player::yspeed
 *  Velocidade na direção vertical do Jogador
 *  @var Player::isIdle
 *  Boleano: 1 se o Jogador estiver parado, 0 caso contrário
 *  @var Player::isReloading
 *  Boleano: 1 se o Jogador estiver a recarregar a arma, 0 caso contrário
 *  @var Player::isShooting
 *  Boleano: 1 se o Jogador estiver a disparar a arma, 0 caso contrário
 *  @var Player::hasAmmo
 *  Boleano: 1 se o Jogador tiver a arma recarregada, 0 caso contrário
 *  @var Player::IdleRight
 *  Array dos XPMs que formam a animação do Jogador quando parado
 *  @var Player::ReloadRight
 *  Array dos XPMs que formam a animação de recarregar a arma do Jogador
 *  @var Player::ShootRight
 *  Array dos XPMs que formam a animação de disparar do Jogador
 *  @var Player::direction
 *  Direção para a qual o Jogador está virado
 *  @var Player::numLives
 *  Número de vidas do Jogador
 *  @var Player::playerNum
 *  Número do Jogador
 */
typedef struct {
  xpm_image_t img;

  int x, y;
  int xspeed, yspeed;

  bool isIdle;
  bool isReloading;
  bool isShooting;
  bool hasAmmo;

  xpm_image_t IdleRight[5];
  xpm_image_t ReloadRight[6];
  xpm_image_t ShootRight[3];

  Direction direction;

  int numLives;
  unsigned int playerNum;

} Player;

/**
 *  @brief Aloca memória e cria o Jogador
 *  @param playerNum Número do Jogador
 *  @return Jogador criado
 */
Player * createPlayer (unsigned int playerNum);

/**
 *  @brief Apresenta o Jogador no ecrã
 *  @param player Jogador a apresentar no ecrã
 */
void draw_player(Player * player);

/**
 *  @brief Remove o Jogador do ecrã
 *  @param player Jogador a remover do ecrã
 */
void clean_player(Player * player);

/**
 *  @brief Controlo da Direção do Jogador
 *  @param player Jogador a controlar a direção
 *  @param scancode Scancode recebido do Teclado
 *  @param up Boleano: 1 se o Jogador estiver virado para Cima, 0 caso contrário
 *  @param down Boleano: 1 se o Jogador estiver virado para Baixo, 0 caso contrário
 *  @param left Boleano: 1 se o Jogador estiver virado para a Esquerda, 0 caso contrário
 *  @param right Boleano: 1 se o Jogador estiver virado para a Direita, 0 caso contrário
 */
void update_movement_direction(Player * player, uint8_t scancode, bool * up, bool * down, bool * left, bool * right);

/**
 *  @brief Controlo do Movimento do Jogador
 *  @param player Jogador a controlar o movimento
 *  @param upPtr Boleano: 1 se o Jogador se virar para Cima, 0 caso contrário
 *  @param downPtr Boleano: 1 se o Jogador se virar para Baixo, 0 caso contrário
 *  @param leftPtr Boleano: 1 se o Jogador se virar para a Esquerda, 0 caso contrário
 *  @param rightPtr Boleano: 1 se o Jogador se virar para a Direita, 0 caso contrário
 */
void check_movement(Player * player, bool * upPtr, bool * downPtr, bool * leftPtr, bool * rightPtr);

/**
 *  @brief Controlo da Animação do Jogador quando parado
 *  @param player Jogador a controlar a animação
 */
void idle_animation(Player * player);

/**
 *  @brief Controlo da Animação do Jogador quando está a recarregar a arma
 *  @param player Jogador a controlar a animação
 */
void reload_animation(Player * player);

/**
 *  @brief Controlo da Animação do Jogador quando está a disparar
 *  @param player Jogador a controlar a animação
 */
void shoot_animation(Player * player);

/**
 *  @brief Verifica se o Jogador colide com as Paredes
 *  @param player Jogador a verificar colisões
 *  @param direction Direção para a qual o Jogador está virado
 *  @return Boleano: 1 se houver colisões, 0 caso contrário
 */
bool check_collision_walls(Player * player, Direction direction);

/**
 *  @brief Verifica se o Jogador colide com as Balas
 *  @param player Jogador a verificar colisões
 *  @param direction Direção para a qual o Jogador está virado
 *  @return Boleano: 1 se houver colisões, 0 caso contrário
 */
bool check_collision_ammo(Player * player, Direction direction);

/**
 *  @brief Verifica se o Jogador colide com os Inimigos
 *  @param player Jogador a verificar colisões
 *  @param direction Direção para a qual o Jogador está virado
 *  @param enemies Conjunto de Inimigos do Nível
 *  @param numEnemies Número de Inimigos do Nível
 *  @return Boleano: 1 se houver colisões, 0 caso contrário
 */
bool check_collision_enemy(Player * player, Direction direction, Enemy ** enemies, unsigned int numEnemies);

//--------------------------------------------------------------------------------------------------

/**
 *  @brief Aloca memória e cria a Bala disparada pelo Jogador
 *  @param player Jogador que dispara a Bala
 *  @param type Tipo de Bala disparada pelo Jogador
 *  @return Bala criada
 */
Bullet * createBullet (Player * player, BulletType type);

/**
 *  @brief Controlo de um disparo pelo Jogador
 *  @param player Jogador que dispara a Bala
 *  @return Bala disparada
 */
Bullet * shoot(Player * player);

/**
 *  @brief Controlo da animação de uma Bala disparada por um Inimigo
 *  @param bullet Bala disparada pelo Inimigo
 *  @param player Jogador a testar colisões com a Bala
 *  @return Boleano: 1 se houver colisões, 0 caso contrário
 */
bool enemyBulletAnimation(Bullet * bullet, Player * player);

/**
 *  @brief Verifica colisões da Bala de um Inimigo com um Jogador
 *  @param bullet Bala disparada pelo Inimigo
 *  @param player Jogador a testar colisões com a Bala
 *  @return Boleano: 1 se houver colisões, 0 caso contrário
 */
bool check_collision_with_player(Bullet * bullet, Player * player);

