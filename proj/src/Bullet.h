#pragma once

#include <lcom/lcf.h>
#include "graphics_card.h"

#include "Images/Bullet.xpm"
#include "Enemy.h"
#include "Player.h"
#include "Menu.h"

/**
 *  @brief Inicia o disparo por um Inimigo
 *  @param enemy Inimigo que dispara
 */
void enemy_shoot(Enemy * enemy);

/**
 *  @brief Controlo do Movimento da Bala
 *  @param bullet Bala que se movimenta
 *  @param enemies Conjunto de Inimigos do Nível
 *  @param numEnemies Número de Inimigos do Nível
 *  @return Boleano: false se houver colisões, true caso contrário
 */
bool bulletAnimation(Bullet * bullet, Enemy ** enemies, unsigned int numEnemies);

/**
 *  @brief Apresenta no ecrã a Bala
 *  @param bullet Bala a apresentar no ecrã
 */
void draw_bullet(Bullet * bullet);

/**
 *  @brief Remove do ecrã a Bala
 *  @param bullet Bala a remover do ecrã
 */
void clean_bullet(Bullet * bullet);

/**
 *  @brief Verifica se a Bala colide com um Inimigo ou com as Paredes
 *  @param bullet Bala a verificar colisões
 *  @param enemies Conjunto de Inimigos do Nível
 *  @param numEnemies Número de Inimigos do Nível
 *  @return Boleano: true se houver colisões, false caso contrário
 */
bool check_collisions_bullet(Bullet * bullet, Enemy ** enemies, unsigned int numEnemies);
