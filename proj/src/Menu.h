#pragma once

#include <lcom/lcf.h>

#include <stdint.h>
#include <stdio.h>

#include "i8254.h"
#include "mouse.h"
#include "rtc.h"
#include "Lever.h"
#include "Game.h"
#include "DateTime.h"
#include "Button.h"

#include "Images/BackgroundMenu.xpm"
#include "Images/OneShot.xpm"
#include "Images/Help.xpm"

#include "Images/YouWon.xpm"
#include "Images/YouLost.xpm"

/**
 *  @brief Carrega o Fundo do Nível
 */
void load_background();

/**
 *  @brief Apresenta no ecrã o Fundo do Nível
 */
void draw_menu_background();

/**
 *  @brief Apresenta no ecrã o Fundo do Menu Help
 */
void draw_help_background();

/**
 *  @brief Remove do ecrã o Fundo do Menu Help
 */
void clean_help_background();

/**
 *  @brief Adiciona ao Fundo do Nível o XPM especificado, na posição especificada
 *  @param img XPM a adicionar ao Fundo do Nível
 *  @param x Posição dos x onde se vai adicionar o XPM
 *  @param y Posição dos y onde se vai adicionar o XPM
 */
void add_to_background(xpm_image_t * img, int x, int y);

/**
 *  @brief Carrega o Fundo do Main Menu
 *  @param firstLoad Boleano: 1 se for a primeira vez que o Main Menu é carregado, 0 caso contrário
 */
void LoadMainMenu(bool firstLoad);

/**
 *  @brief Carrega o Fundo do Pause Menu
 */
void LoadPauseMenu();

/**
 *  @brief Carrega o Fundo do Won Menu
 */
void LoadWonMenu();

/**
 *  @brief Carrega o Fundo do Lost Menu
 */
void LoadLostMenu();

//--------------------------------------------------------------------------------------------------

/**
 *  @brief Controlo das Interrupções de um dado dispositivo relativas ao Main Menu
 *  @param device Dispositivo que gerou interrupções
 */
void MainMenuInterruptHandler(Device device);

/**
 *  @brief Controlo das Interrupções de um dado dispositivo relativas ao Pause Menu
 *  @param device Dispositivo que gerou interrupções
 */
void PauseMenuInterruptHandler(Device device);

/**
 *  @brief Controlo das Interrupções de um dado dispositivo relativas ao Help Menu
 *  @param device Dispositivo que gerou interrupções
 */
void HelpMenuInterruptHandler(Device device);

/**
 *  @brief Controlo das Interrupções de um dado dispositivo relativas ao Won Menu
 *  @param device Dispositivo que gerou interrupções
 */
void GameWonInterruptHandler(Device device);

/**
 *  @brief Controlo das Interrupções de um dado dispositivo relativas ao Lost Menu
 *  @param device Dispositivo que gerou interrupções
 */
void GameLostInterruptHandler(Device device);


