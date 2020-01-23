#pragma once

#include <lcom/lcf.h>
#include "graphics_card.h"
#include "kbd.h"

#include "Images/enemy_idle_0.xpm"
#include "Images/enemy_idle_1.xpm"
#include "Images/enemy_idle_2.xpm"
#include "Images/enemy_idle_3.xpm"
#include "Images/enemy_idle_4.xpm"
#include "Images/enemy_idle_5.xpm"

#include "Images/enemy_reload_0.xpm"
#include "Images/enemy_reload_1.xpm"
#include "Images/enemy_reload_2.xpm"
#include "Images/enemy_reload_3.xpm"
#include "Images/enemy_reload_4.xpm"
#include "Images/enemy_reload_5.xpm"
#include "Images/enemy_reload_6.xpm"
#include "Images/enemy_reload_7.xpm"

#include "Images/enemy_move_0.xpm"

typedef enum {NORMAL} BulletType;

/** @struct Bullet
 *  @brief Struct relativa à Bala
 *  @var Bullet::x
 *  Posição dos x da Bala
 *  @var Bullet::y
 *  Posição dos y da Bala
 *  @var Bullet::speed
 *  Velocidade da Bala (frame-rate)
 *  @var Bullet::img
 *  XPM da Bala
 *  @var Bullet::type
 *  Tipo da Bala
 *  @var Bullet::direction
 *  Direção do movimento da Bala
 *  @var Bullet::active
 *  Boleano: 1 se a Bala estiver a ser disparada (em campo), 0 caso contrário
 */
typedef struct {
  unsigned int x;
  unsigned int y;

  unsigned int speed;

  xpm_image_t img;
  BulletType type;
  Direction direction;

  bool active;
} Bullet;

/** @struct Enemy
 *  @brief Struct relativa aos Inimigos
 *  @var Enemy::img 
 *  XPM do Inimigo
 *  @var Enemy::x
 *  Posição dos x do Inimigo
 *  @var Enemy::y
 *  Posição dos y do Inimigo
 *  @var Enemy::xspeed
 *  Velocidade na direção horizontal do Inimigo
 *  @var Enemy::yspeed
 *  Velocidade na direção vertical do Inimigo
 *  @var Enemy::isMoving
 *  Boleano: 1 se o Inimigo estiver em Movimento, 0 caso contrário
 *  @var Enemy::isAttacking
 *  Boleano: 1 se o Inimigo estiver a atacar, 0 caso contrário
 *  @var Enemy::MoveRight
 *  Array dos XPMs que formam a animação de movimento do Inimigo
 *  @var Enemy::AttackRight
 *  Array dos XPMs que formam a animação de ataque do Inimigo
 *  @var Enemy::ReloadRight
 *  Array dos XPMs que formam a animação de recarregar a arma do Inimigo
 *  @var Enemy::moveAnimation
 *  Número do XPM de animação de movimento do Inimigo
 *  @var Enemy::reloadAnimation
 *  Número do XPM de animação de recarregar a arma do Inimigo
 *  @var Enemy::direction
 *  Direção para a qual o Inimigo está virado
 *  @var Enemy::dead
 *  Boleano: 1 se o Inimigo estiver morto, 0 caso contrário
 *  @var Enemy::isStatic
 *  Boleano: 1 se o Inimigo for estático (Atirador), 0 caso contrário (Guarda)
 *  @var Enemy::isReloading
 *  Boleano: 1 se o Inimigo estiver a recarregar a arma, 0 caso contrário
 *  @var Enemy::bullet
 *  Objeto da Bala disparada pelo Inimigo
 */
typedef struct {
  xpm_image_t img;

  int x, y;
  int xspeed, yspeed;

  bool isMoving;
  bool isAttacking;

  xpm_image_t MoveRight[6];
  xpm_image_t AttackRight[6];
  xpm_image_t ReloadRight[8];

  unsigned int moveAnimation;
  unsigned int reloadAnimation;

  Direction direction;

  bool dead;
  bool isStatic;
  bool isReloading;

  Bullet * bullet;

} Enemy;

#include "Level.h"
#include "Bullet.h"

/**
 *  @brief Aloca memória e cria o Inimigo
 *  @param x Posição dos x do Inimigo
 *  @param y Posição dos y do Inimigo
 *  @param direction Direção para a qual o Inimigo está virado
 *  @param isStatic Boleano: 1 se o Inimigo for estático (Atirador), 0 caso contrário (Guarda)
 *  @return Inimigo criado
 */
Enemy * createEnemy(int x, int y, Direction direction, bool isStatic);

/**
 *  @brief Apresenta o Inimigo no ecrã
 *  @param enemy Inimigo a apresentar no ecrã
 */
void draw_enemy(Enemy * enemy);

/**
 *  @brief Remove o Inimigo no ecrã
 *  @param enemy Inimigo a remover do ecrã
 */
void clean_enemy(Enemy * enemy);

/**
 *  @brief Torna o Inimigo morto
 *  @param enemy Inimigo a tornar morto
 */
void enemy_death(Enemy * enemy);

/**
 *  @brief Controlo do Movimento do Inimigo
 *  @param enemy Inimigo que se movimenta
 */
void enemy_movement(Enemy * enemy);

/**
 *  @brief Verifica se o Inimigo colide com as Paredes
 *  @param enemy Inimigo a verificar colisões
 *  @return Boleano: 1 se houver colisões, 0 caso contrário
 */
bool check_enemy_collision_walls(Enemy * enemy);

/**
 *  @brief Controlo da Animação do Inimigo quando parado
 *  @param enemy Inimigo a controlar a animação
 */
void enemy_idle_animation(Enemy * enemy);

/**
 *  @brief Controlo da Animação do Inimigo quando está a recarregar a arma
 *  @param enemy Inimigo a controlar a animação
 */
void enemy_reload_animation(Enemy * enemy);
