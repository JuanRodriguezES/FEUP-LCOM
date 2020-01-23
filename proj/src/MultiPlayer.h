#pragma once

#include <lcom/lcf.h>

#include "Menu.h"
#include "serial_port.h"

#include "Images/WaitingForPlayers.xpm"

#include "Images/blueheart.xpm"
#include "Images/heart.xpm"

#define MakeW 0x11
#define MakeS 0x1F
#define MakeD 0x20
#define MakeA 0x1E
#define BreakW 0x91
#define BreakS 0x9F
#define BreakD 0xA0
#define BreakA 0x9E
#define MakeUpArrow 0x48
#define MakeDownArrow 0x50
#define MakeRightArrow 0x4D
#define MakeLeftArrow 0x4B
#define BreakUpArrow 0xC8
#define BreakDownArrow 0xD0
#define BreakRightArrow 0xCD
#define BreakLeftArrow 0xCB

/**
 *  @brief Controlo das Interrupções geradas pela Serial Port recebidas do Menu
 */
void ReceivedSPInterruptFromMenu();

/**
 *  @brief Controlo das Interrupções geradas por um dado dispositivo recebidas no Waiting Menu
 *  @param device Dispositivo que gerou as Interrupções
 */
void WaitingInterruptHandler(Device device);

/**
 *  @brief Controlo das Interrupções geradas por um dado dispositivo recebidas durante o Multi-Player
 *  @param device Dispositivo que gerou as Interrupções
 */
void MultiPlayerInterrupthandler(Device device);

/**
 *  @brief Carrega os XPMs do Multi-Player
 */
void LoadMultiPlayerXPM();

/**
 *  @brief Apresenta no ecrã o XPM do Waiting Menu
 */
void LoadWaitingMenu();

/**
 *  @brief Preparação para o Início do Multi-Player
 */
void LoadMultiPlayer();

/**
 *  @brief Apresenta no ecrã as vidas de cada Jogador
 */
void draw_hearts();

/**
 *  @brief Remove do ecrã as vidas de cada Jogador
 */
void clean_heart(int playerNum, int numLives);

/**
 *  @brief Controlo da data recebida
 *  @param auxcode Data recebida
 */
void handle_data(uint8_t auxcode);

