#pragma once

#define SPACEBAR 0xB9
#define E 0x12

#include "Images/RedLightLever.xpm"
#include "Images/GreenLightLever.xpm"
#include "Images/LeverPos0.xpm"
#include "Images/LeverPos1.xpm"
#include "Images/LeverPos2.xpm"
#include "Images/LeverPos3.xpm"
#include "Images/LeverPos4.xpm"
#include "Images/LeverPos5.xpm"
#include "Images/LeverPos6.xpm"
#include "Images/CleanLever.xpm"

#include <lcom/lcf.h>
#include "graphics_card.h"
#include "graphics_card_const.h"
#include "i8042.h"
#include "i8254.h"
#include "kbd.h"

typedef enum {TIMER, KEYBOARD, MOUSE, RTC, SERIALPORT} Device;

typedef enum {MAINMENU, SINGLEPLAYER, LOST, WON, LEVER, PAUSEMENU, MULTIPLAYER, WAITING, HELP, EXIT} GameState;

typedef enum {BEGIN, MOVE_NOTDONE, MOVE_DONE} LeverState;

typedef enum {L1, L2, L3, L4, L5, L6, L7, L8, L9, PAUSE, END} SinglePlayerGameState;

#include "Level.h"
#include "Player.h"
#include "Bullet.h"
#include "DateTime.h"
#include "Menu.h"
#include "MultiPlayer.h"

//--------------------------------------------------------------------------------------------------

/**
 *  @brief Loop Principal do Jogo
 *  @return 0 em caso de sucesso, 1 caso contrário
 */
int GameMainLoop();

/**
 *  @brief Controlo geral de Interrupções para um qualquer dispositivo
 *  @param device Dispositivo que gerou interrupções
 */
void GeneralInterrupt(Device device);

/**
 *  @brief Controlo de Interrupções relativas ao Single-Player para um qualquer dispositivo
 *  @param device Dispositivo que gerou interrupções
 */
void SinglePlayerInterruptHandler(Device device);

/**
 *  @brief Controlo de Interrupções relativas às Alavancas para um qualquer dispositivo
 *  @param device Dispositivo que gerou interrupções
 */
void LeverInterruptHandler(Device device);

/**
 *  @brief Carregar estado de um Nível
 *  @param levelNum Número do Nível
 *  @param begin Boleano: 1 se o Nível estiver no estado inicial, 0 caso contrário
 */
void LoadSinglePLayer(unsigned int levelNum, bool begin);

/**
 *  @brief Carregar XPM das Alavancas
 */
void LoadLeverXPM();

/**
 *  @brief Carregar uma Alavanca conforme o seu estado
 *  @param state Estado da Alavanca
 *  @param lever Alavanca a carregar
 */
void LoadLever(unsigned int state, Lever * lever);

/**
 *  @brief Verifica se o Jogador está perto da Alavanca
 *  @return 0 em caso de sucesso, 1 caso contrário
 */
int check_lever_position();

/**
 *  @brief Verifica se o Jogador está perto da Zona Final
 *  @return Boleano: 1 se o Jogador estiver perto da Zona Final, 0 caso contrário
 */
bool check_final_position();

/**
 *  @brief Adiciona a Zona Final ao Fundo do Nível
 *  @param posfinalx Posição dos x da Zona Final
 *  @param posfinaly Posição dos y da Zona Final
 *  @param lado Comprimento do lado da Zona Final (x16 pixeis)
 */
void add_final_position_background(int *posfinalx, int *posfinaly, int *lado);

/**
 *  @brief Controlo do Rato conforme o Mouse Packet Recebido
 *  @param pack Mouse Packet com as informações do Rato
 *  @return Tipo de evento causado pelo Mouse Packet recebido
 */
struct mouse_ev * mouse_events(struct packet * pack);

/**
 *  @brief Controlo do Movimendo da Alavanca no Modo Alavanca
 *  @param xlen Movimento na direção dos x
 *  @param state Estado da Alavanca
 *  @param mouse_event Tipo de evento recebido do Rato
 *  @return Boleano: 1 se o movimento da Alavanca tiver terminado, 0 caso contrário
 */
bool lever_move_handler(int * xlen, LeverState * state, struct mouse_ev * mouse_event);

