#include "Menu.h"

extern uint8_t scancode;
extern unsigned int hres, vres;
extern struct packet pack;

extern GameState gameState;
extern Player * player;
extern Level * level;
extern Cursor * cursor;
extern DateTime * dateTime;

xpm_image_t background_menu;
xpm_image_t clean_background_menu;

static Button ** pauseMenuButtons;
static Button ** mainMenuButtons;
static Button * continueButton;

void MainMenuInterruptHandler(Device device) {
  static struct mouse_ev * mouseEvent;
  static bool overExit = false, overSingleplayer = false, overMultiplayer = false, overHelp = false;
  bool clickedExit = false, clickedSingleplayer = false, clickedMultiplayer = false, clickedHelp = false;

  switch (device) {
    case TIMER:
      ReceivedSPInterruptFromMenu();

      switch(check_collision_main_menu()) {
        case 0:
          if (overExit) {
            overExit = false;
            mainMenuButtons[3]->mouseOver = false;
            add_button_to_background(mainMenuButtons[3]);
            draw_button(mainMenuButtons[3]);
          }
          else if (overSingleplayer) {
            overSingleplayer = false;
            mainMenuButtons[0]->mouseOver = false;
            add_button_to_background(mainMenuButtons[0]);
            draw_button(mainMenuButtons[0]);
          }
          else if (overMultiplayer) {
            overMultiplayer = false;
            mainMenuButtons[1]->mouseOver = false;
            add_button_to_background(mainMenuButtons[1]);
            draw_button(mainMenuButtons[1]);
          }
          else if (overHelp) {
            overHelp = false;
            mainMenuButtons[2]->mouseOver = false;
            add_button_to_background(mainMenuButtons[2]);
            draw_button(mainMenuButtons[2]);
          }
          break;
        case 1:
          if (mouseEvent->type == LB_RELEASED) {
            clickedExit = true;
            break;
          }
          if (!overExit) {
            overExit = true;
            mainMenuButtons[3]->mouseOver = true;
            add_button_to_background(mainMenuButtons[3]);
            draw_button(mainMenuButtons[3]);
          }
          break;
        case 3:
          if (mouseEvent->type == LB_RELEASED) {
            clickedSingleplayer = true;
            break;
          }
          if (!overSingleplayer) {
            overSingleplayer = true;
            mainMenuButtons[0]->mouseOver = true;
            add_button_to_background(mainMenuButtons[0]);
            draw_button(mainMenuButtons[0]);
          }
          break;
        case 4:
          if (mouseEvent->type == LB_RELEASED) {
            clickedMultiplayer = true;
            break;
          }
          if (!overMultiplayer) {
            overMultiplayer = true;
            mainMenuButtons[1]->mouseOver = true;
            add_button_to_background(mainMenuButtons[1]);
            draw_button(mainMenuButtons[1]);
          }
          break;
        case 5: 
          if (mouseEvent->type == LB_RELEASED) {
            clickedHelp = true;
            break;
          }
          if (!overHelp) {
            overHelp = true;
            mainMenuButtons[2]->mouseOver = true;
            add_button_to_background(mainMenuButtons[2]);
            draw_button(mainMenuButtons[2]);
          }
          break;
      }
      break;
    case KEYBOARD: // NAO FAZER NADA
      break;
    case MOUSE:
      mouseEvent = mouse_events(&pack);
      mouse_update(&pack);
      break;
    case RTC:
      //print_clock();
      clean_clock();
      updateDateTime();
      draw_clock();
      break;
    case SERIALPORT:
      sp_ih();
      //ReceivedSPInterruptFromMenu();
      break;
  }

  if (clickedExit) // Sair
    gameState = EXIT;
  else if (clickedSingleplayer) { // Entrar no modo Singleplayer
    gameState = SINGLEPLAYER;
    clean_clock();
    LoadSinglePLayer(1,true);
  }
  else if (clickedMultiplayer) { // Entrar no modo Multiplayer
    addToTransmitQueue(0xFF);
    gameState = WAITING;
    clean_clock();
    LoadWaitingMenu();
  }
  else if (clickedHelp) { // Entrar no Help
    gameState = HELP;
    draw_help_background();
    return;
  }
  //else
    //return;
}

void PauseMenuInterruptHandler(Device device) {
  static struct mouse_ev * mouseEvent;
  static bool overExit = false, overContinue = false;
  bool clickedExit = false, clickedContinue = false;

  switch (device) {
    case TIMER:
      switch(check_collision_pause_menu()) {
        case 0:
          if (overExit) {
            overExit = false;
            pauseMenuButtons[1]->mouseOver = false;
            add_button_to_background(pauseMenuButtons[1]);
            draw_button(pauseMenuButtons[1]);
          }
          else if (overContinue) {
            overContinue = false;
            pauseMenuButtons[0]->mouseOver = false;
            add_button_to_background(pauseMenuButtons[0]);
            draw_button(pauseMenuButtons[0]);
          }
          break;
        case 1:
          if (mouseEvent->type == LB_RELEASED) {
            clickedExit = true;
            break;
          }
          if (!overExit) {
            overExit = true;
            pauseMenuButtons[1]->mouseOver = true;
            add_button_to_background(pauseMenuButtons[1]);
            draw_button(pauseMenuButtons[1]);
          }
          break;
        case 2:
          if (mouseEvent->type == LB_RELEASED) {
            clickedContinue = true;
            break;
          }
          if (!overContinue) {
            overContinue = true;
            pauseMenuButtons[0]->mouseOver = true;
            add_button_to_background(pauseMenuButtons[0]);
            draw_button(pauseMenuButtons[0]);
          }
          break;
      }
      break;
    case KEYBOARD:
      if (scancode == ESC) {
        gameState = SINGLEPLAYER;
        LoadSinglePLayer(level->levelnum, false);
      }
      break;
    case MOUSE:
      mouseEvent = mouse_events(&pack);
      mouse_update(&pack);
      break;
    case RTC:
      print_clock();
      clean_clock();
      updateDateTime();
      draw_clock();
      break;
    case SERIALPORT:
      break;
  }

  if (clickedExit) {
    gameState = MAINMENU;
    LoadRtc();
    LoadMainMenu(false);
  }
  else if (clickedContinue){
    gameState = SINGLEPLAYER;
    LoadSinglePLayer(level->levelnum, false);
  }
  else 
    return;
}

void HelpMenuInterruptHandler(Device device) {
  switch (device) {
    case TIMER:
      break;
    case KEYBOARD:
      if (scancode == ESC) {
        gameState = MAINMENU;
        LoadRtc();
        LoadMainMenu(false);
      }
      break;
    case MOUSE:
      break;
    case RTC:
      break;
    case SERIALPORT:
      break;
  }
}

void GameWonInterruptHandler(Device device) {
  static struct mouse_ev * mouseEvent;
  static bool overContinue = false;
  bool clickedContinue = false;

  switch (device) {
    case TIMER:
      switch(check_collision_won_menu()) {
        case 0:
          if (overContinue) {
            overContinue = false;
            continueButton->mouseOver = false;
            add_button_to_background(continueButton);
            draw_button(continueButton);
          }
          break;
        case 1:
          if (mouseEvent->type == LB_RELEASED) {
            clickedContinue = true;
            break;
          }
          if (!overContinue) {
            overContinue = true;
            continueButton->mouseOver = true;
            add_button_to_background(continueButton);
            draw_button(continueButton);
          }
          break;
      }
      break;
    case KEYBOARD:
      if (scancode == ESC) {
        gameState = MAINMENU;
        LoadRtc();
        LoadMainMenu(false);
      }
      break;
    case MOUSE:
      mouseEvent = mouse_events(&pack);
      mouse_update(&pack);
      break;
    case RTC:
      break;
    case SERIALPORT:
      break;
  }

  if (clickedContinue) {
    gameState = MAINMENU;
    LoadMainMenu(false);
    LoadRtc();
  }
}

void GameLostInterruptHandler(Device device) {
  static struct mouse_ev * mouseEvent;
  static bool overContinue = false;
  bool clickedContinue = false;

  switch (device) {
    case TIMER:
      switch(check_collision_won_menu()) {
        case 0:
          if (overContinue) {
            overContinue = false;
            continueButton->mouseOver = false;
            add_button_to_background(continueButton);
            draw_button(continueButton);
          }
          break;
        case 1:
          if (mouseEvent->type == LB_RELEASED) {
            clickedContinue = true;
            break;
          }
          if (!overContinue) {
            overContinue = true;
            continueButton->mouseOver = true;
            add_button_to_background(continueButton);
            draw_button(continueButton);
          }
          break;
      }
      break;
    case KEYBOARD:
      if (scancode == ESC) {
        gameState = MAINMENU;
        LoadRtc();
        LoadMainMenu(false);
      }
      break;
    case MOUSE:
      mouseEvent = mouse_events(&pack);
      mouse_update(&pack);
      break;
    case RTC:
      break;
    case SERIALPORT:
      break;
  }

  if (clickedContinue) {
    gameState = MAINMENU;
    LoadRtc();
    LoadMainMenu(false);
  }
}

//--------------------------------------------------------------------------------------------------

void LoadMainMenu(bool firstLoad) {
  load_background();

  cursor = load_cursor();

  mainMenuButtons = (Button **) malloc(4 * sizeof(Button *));

  mainMenuButtons[0] = createButton(BUTTON_SINGLEPLAYER,96,384);
  mainMenuButtons[1] = createButton(BUTTON_MULTIPLAYER,544,384);
  mainMenuButtons[2] = createButton(BUTTON_HELP,96,576);
  mainMenuButtons[3] = createButton(BUTTON_EXIT,544,576);

  static xpm_image_t logotip;

  if (firstLoad)
    xpm_load(OneShot_xpm, XPM_8_8_8_8, &logotip);
  
  add_button_to_background(mainMenuButtons[0]);
  add_button_to_background(mainMenuButtons[1]);
  add_button_to_background(mainMenuButtons[2]);
  add_button_to_background(mainMenuButtons[3]);
  add_to_background(&logotip,50,170);

  draw_menu_background();
}

void LoadPauseMenu() {
  load_background();
  cursor = load_cursor();

  pauseMenuButtons = (Button **) malloc(2 * sizeof(Button *));

  pauseMenuButtons[0] = createButton(BUTTON_CONTINUE,320,384);
  pauseMenuButtons[1] = createButton(BUTTON_EXIT,320,576);
  
  add_button_to_background(pauseMenuButtons[0]);
  add_button_to_background(pauseMenuButtons[1]);

  draw_menu_background();
}

void LoadWonMenu() {
  load_background();
  cursor = load_cursor();

  xpm_image_t img;
  xpm_load(YouWon_xpm, XPM_8_8_8_8, &img);

  uint32_t * map = (uint32_t *)img.bytes;

  for (int i = 0; i < img.height; i++) {
    for (int j = 0; j < img.width; j++) {
      if (*(map + j + i * img.width) != xpm_transparency_color(XPM_8_8_8_8))
        *((uint32_t *)background_menu.bytes + (240 + j) + (170 + i)*hres) = *(map + j + i * img.width);
    }
  }

  continueButton = createButton(BUTTON_CONTINUE,320,484);
  
  add_button_to_background(continueButton);

  draw_menu_background();
}

void LoadLostMenu() {
  load_background();
  cursor = load_cursor();

  xpm_image_t img;
  xpm_load(YouLost_xpm, XPM_8_8_8_8, &img);

  uint32_t * map = (uint32_t *)img.bytes;

  for (int i = 0; i < img.height; i++) {
    for (int j = 0; j < img.width; j++) {
      if (*(map + j + i * img.width) != xpm_transparency_color(XPM_8_8_8_8))
        *((uint32_t *)background_menu.bytes + (230 + j) + (170 + i)*hres) = *(map + j + i * img.width);
    }
  }

  continueButton = createButton(BUTTON_CONTINUE,320,484);
  
  add_button_to_background(continueButton);

  draw_menu_background();
}

//--------------------------------------------------------------------------------------------------

void load_background() {
    xpm_load(BackgroundMenu_xpm, XPM_8_8_8_8, &background_menu);
    xpm_load(BackgroundMenu_xpm, XPM_8_8_8_8, &clean_background_menu);
}

void draw_menu_background() {

  uint32_t* map = (uint32_t*) background_menu.bytes;

  for(unsigned int i = 0; i < background_menu.width; i++) {
    for (unsigned int j = 0; j < background_menu.height; j++) {
      changePixelColor(i,j,*(map + i + j*hres));
    }
  }
}

void draw_help_background() {
  xpm_image_t img;
  xpm_load(Help_xpm, XPM_8_8_8_8, &img);

  uint32_t* map = (uint32_t*) img.bytes;

  for(unsigned int i = 0; i < img.width; i++) {
    for (unsigned int j = 0; j < img.height; j++) {
      changePixelColor(i,j,*(map + i + j*hres));
    }
  }
}

void clean_help_background() {
  uint32_t* map = (uint32_t*) background_menu.bytes;

  for (int i = 0; i < (int)hres; i++) {
    for (int j = 0; j < (int)vres; j++) {
      if (i < (int)hres - 1 && j < (int)vres - 1)
        changePixelColor(i,j,*(map + i + j * hres));
    }
  }
}

void add_to_background(xpm_image_t * img, int x, int y) {
  uint32_t * map, * imgMap;

  map = (uint32_t *)background_menu.bytes;

  imgMap = (uint32_t *)img->bytes;

  for(int i = 0; i < img->width; i++) {
    for (int j = 0; j < img->height; j++) {
      if (*(imgMap + i + j*img->width) != xpm_transparency_color(XPM_8_8_8_8))
        *(map + (x + i) + (y + j) * hres) = *(imgMap + i + j*img->width);
    }
  }
}




