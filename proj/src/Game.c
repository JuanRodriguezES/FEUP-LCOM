#include "Game.h"

//--------------------------------------------------------------------------------------------------

//Variáveis Globais
//TIMER
extern unsigned int counter;
//KBC
extern uint8_t scancode;
//MOUSE
struct packet pack;
struct mouse_ev mouse_event;
//GRAPHICS
extern unsigned int hres, vres;

//OTHER
static Player * player;
extern Level * level;
extern Cursor * cursor;
extern DateTime * dateTime;
GameState gameState = MAINMENU;

static Lever * leverBeingUsed;
static xpm_image_t LeverPositions[7];
static xpm_image_t LeverColors[2];
static xpm_image_t CleanLever;


//--------------------------------------------------------------------------------------------------


int GameMainLoop() {
  int ipc_status,r;
  message msg;

  uint32_t irq_set_timer = BIT(TIMER0_IRQ);
  uint32_t irq_set_kbd = BIT(KBD_IRQ);
  uint32_t irq_set_mouse = BIT(MOUSE_IRQ);
  uint32_t irq_set_rtc = BIT(RTC_IRQ);
  uint32_t irq_set_sp = BIT(SP_COM1_IRQ);

  uint8_t timer_bit_no, kbd_bit_no, mouse_bit_no, rtc_bit_no, sp_bit_no;

  bool KbdReadSecond = false;
  bool MouseReadSecond = false, MouseReadThird = false;

  uint8_t kbd_bytes[2];

  uint8_t ms_bytes[3];

  LoadMainMenu(true);

  //SUBSCRIBES
  if (timer_subscribe_int(&timer_bit_no) != 0) {return 1;}
  if (kbd_subscribe_int(&kbd_bit_no) != 0) {return 1;}
  if (rtc_subscribe_int(&rtc_bit_no) != 0) {return 1;}
  if (mouse_enable_data_report() != 0) {return 1;}
  if (mouse_subscribe_int(&mouse_bit_no) != 0) {return 1;}
  if (sp_subscribe_int(&sp_bit_no) != 0) {return 1;}

  LoadMultiPlayerXPM();
  LoadLeverXPM();
  dateTime = LoadDateTime();
  LoadRtc();
  addToTransmitQueue(VM_CONNECTED);

  while(gameState != EXIT) {
    if ( (r = driver_receive(ANY, &msg, &ipc_status)) != 0 ) { 
      printf("driver_receive failed with: %d", r);
      continue;
    }
    if (is_ipc_notify(ipc_status)) {
      switch (_ENDPOINT_P(msg.m_source)) {
          case HARDWARE: 
            if (msg.m_notify.interrupts & irq_set_kbd) {
              kbc_ih();
              if (KbdReadSecond) {
                KbdReadSecond = false;
                kbd_bytes[1] = scancode;
              }
              else {
                kbd_bytes[0] = scancode;
                if (scancode == SIZE) {
                  KbdReadSecond = true;
                }
              }
              GeneralInterrupt(KEYBOARD);
            }
            if (msg.m_notify.interrupts & irq_set_mouse) {
              mouse_ih();
              if (!MouseReadSecond && !MouseReadThird && (scancode & BIT(3))){
                ms_bytes[0] = scancode;
                MouseReadSecond = true;
              }
              else if (MouseReadSecond) {
                ms_bytes[1] = scancode;
                MouseReadThird = true;
                MouseReadSecond = false;
              }
              else if (MouseReadThird) {
                ms_bytes[2] = scancode;
                MouseReadThird = false;
                for(unsigned int i = 0; i < 3; i++)
                  pack.bytes[i] = ms_bytes[i];
                buildPacket(&pack);
                GeneralInterrupt(MOUSE);
              }
            }
            if (msg.m_notify.interrupts & irq_set_rtc) {
              rtc_ih();
              GeneralInterrupt(RTC);
            }
            if (msg.m_notify.interrupts & irq_set_sp) {
              GeneralInterrupt(SERIALPORT);
            }
            if (msg.m_notify.interrupts & irq_set_timer) {
              timer_int_handler();
              GeneralInterrupt(TIMER);
              double_buffer();
            } 
            break;
        default:
          break; 
      }
    }
    if (gameState != MULTIPLAYER)
      sp_write();
  }

  addToTransmitQueue(VM_DISCONNECTED);

  //UNSUBSCRIBES
  if (sp_unsubscribe_int() != 0) {return 1;}
  if (mouse_unsubscribe_int() != 0) {return 1;}
  if (mouse_disable_data_report() != 0) {return 1;}
  if (rtc_unsubscribe_int() != 0) {return 1;}
  if (kbd_unsubscribe_int() != 0) {return 1;}
  if (timer_unsubscribe_int() != 0) {return 1;}

  free(level);

  return 0;
}

void GeneralInterrupt(Device device) {
  switch (gameState){
    case MAINMENU:
      MainMenuInterruptHandler(device);
      break;
    case PAUSEMENU:
      PauseMenuInterruptHandler(device);
      break;
    case HELP:
      HelpMenuInterruptHandler(device);
      break;
    case SINGLEPLAYER:
      SinglePlayerInterruptHandler(device);
      break;
    case LEVER:
      LeverInterruptHandler(device);
      break;
    case MULTIPLAYER:
      MultiPlayerInterrupthandler(device);
      break;
    case WAITING:
      WaitingInterruptHandler(device);
      break;
    case WON:
      GameWonInterruptHandler(device);
      break;
    case LOST:
      GameLostInterruptHandler(device);
      break;
    case EXIT:
      break;
  }
}

void SinglePlayerInterruptHandler(Device device) {
  static Bullet * playerBullet;
  srand(time(NULL));
  static unsigned int randomTimeShoot = 180;
  static bool enemyShoot = true;
  static bool bulletOnMap = false;
  static int checkLever;
  static bool up = false, down = false, left = false, right = false;

  switch (device) {
    case TIMER:
      if (player->numLives == 0) {
        gameState = LOST;
        up = false; down = false; left = false; right = false;
        check_movement(player, &up, &down, &left, &right);
        LoadLostMenu();
        break;
      }

      //CHECKS IF IT IS IN THE POSITION TO GO TO NEXT LEVEL
      if (check_final_position() /*|| scancode == 0x19 USED FOR DEBUGGING*/) {
        enemyShoot = true;
        up = false; down = false; left = false; right = false;
        check_movement(player, &up, &down, &left, &right);
        LoadSinglePLayer(level->levelnum + 1, true);
        break;
      }

      for (unsigned int i = 0; i < level->numLevers; i++) {
        if (level->leverList[i]->active && level->doorList[i]->active) {
          if (level->levelnum == 1) {
            remove_door_background(level->doorList[i+1]);
            clean_door(level->doorList[i+1]);
            level->doorList[i+1]->active = false;
          }
          remove_door_background(level->doorList[i]);
          clean_door(level->doorList[i]);
          level->doorList[i]->active = false;
        }
      }

      //PLAYER ANIMATION
      if (counter % 10 == 0 && !player->isReloading && !player->isShooting)
        idle_animation(player);
      else if (counter % 5 == 0 && player->isReloading)
        reload_animation(player);  
      else if (counter % 3 == 0 && player->isShooting)
        shoot_animation(player); 

      //BULLET ANIMATION
      if (bulletOnMap) {
        bulletOnMap = bulletAnimation(playerBullet, level->enemyList, level->numEnemies);
        if (!playerBullet->active)
          clean_bullet(playerBullet);
      }

      //CHECKS IF IT IS NEAR A LEVER TO ACTIVATE IT
      checkLever = check_lever_position();

      //UPDATE PLAYER POSITION
      check_movement(player, &up, &down, &left, &right);

      //ENEMY ANIMATION AND SHOOTS
      for (unsigned int i = 0; i < level->numEnemies; i++) {
        if (level->enemyList[i]->bullet->active && level->enemyList[i]->isStatic)
          enemyBulletAnimation(level->enemyList[i]->bullet, player);

        if (level->enemyList[i]->dead)
          continue;

        if (counter % 10 == 0 && !level->enemyList[i]->isReloading)
          enemy_idle_animation(level->enemyList[i]);
        else if (counter % 5 == 0 && level->enemyList[i]->isReloading)
          enemy_reload_animation(level->enemyList[i]);

        enemy_movement(level->enemyList[i]);

        if (counter == randomTimeShoot && level->enemyList[i]->isStatic) {
          enemy_shoot(level->enemyList[i]);
          enemyShoot = true;
        }
      }

      if (enemyShoot) {
        randomTimeShoot = counter + (rand() % 280) + 120;
        enemyShoot = false;
      }

      //CHECKS IF IT COLLIDED WITH ANY ENEMY
      if (check_collision_enemy(player, player->direction, level->enemyList, level->numEnemies)) {
        gameState = LOST;
      }

      if (gameState == LOST) {
        up = false; down = false; left = false; right = false;
        check_movement(player, &up, &down, &left, &right);
        LoadLostMenu();
      }

      break;
    case KEYBOARD:
      //PAUSE MENU
      if (scancode == ESC) {
        gameState = PAUSEMENU;
        LoadRtc();
        LoadPauseMenu();
        break;
      }

      //SHOOT
      if (scancode == SPACEBAR && !player->isReloading && player->hasAmmo) {
        playerBullet = shoot(player);
        //draw_ammo_level();
        bulletOnMap = true;
      }

      //ACTIVATE LEVER
      if (checkLever != 0 && scancode == E) {
        enemyShoot = true;
        up = false; down = false; left = false; right = false;
        check_movement(player, &up, &down, &left, &right);
        gameState = LEVER;
        LoadLever(0,level->leverList[checkLever - 1]);
      }

      //UPDATE MOVING DIRECTION
      update_movement_direction(player, scancode, &up, &down, &left, &right);
      break;
    case MOUSE: // NAO FAZER NADA
      break;
    case RTC:
      break;
    case SERIALPORT:
      break;
  }
}

void LeverInterruptHandler(Device device) {
  static LeverState leverState = BEGIN;
  static struct mouse_ev * mouseEvent;

  static int xlen = 0;
  static int leverPos = 1;

  static bool open = false;

  open = leverBeingUsed->active;

  switch(device) {
    case TIMER:
      if (!open) {
        if (xlen < 227) {
          if (leverPos == 1) {
            leverPos = -1;
            LoadLever(1, leverBeingUsed);
          }
          else if (leverPos != -1){
            leverPos = 1;
          }
        }
        else if (xlen < 277) {
          if (leverPos == 2) {
            leverPos = -2;
            LoadLever(2, leverBeingUsed);
          }
          else if (leverPos != -2){
            leverPos = 2;
          }
        }
        else if (xlen < 400) {
          if (leverPos == 3) {
            leverPos = -3;
            LoadLever(3, leverBeingUsed);
          }
          else if (leverPos != -3){
            leverPos = 3;
          }
        }
        else if (xlen < 571) {
          if (leverPos == 4) {
            leverPos = -4;
            LoadLever(4, leverBeingUsed);
          }
          else if (leverPos != -4){
            leverPos = 4;
          }
        }
        else if (xlen < 670) {
          if (leverPos == 5) {
            leverPos = -5;
            LoadLever(5, leverBeingUsed);
          }
          else if (leverPos != -5){
            leverPos = 5;
          }
        }
        else if (xlen < 750) {
          if (leverPos == 6) {
            leverPos = -6;
            LoadLever(6, leverBeingUsed);
          }
          else if (leverPos != -6){
            leverPos = 6;
          }
        }
        else {
          if (leverPos == 7) {
            leverPos = -7;
            LoadLever(7, leverBeingUsed);
          }
          else if (leverPos != -7){
            leverPos = 7;
          }
        }
      }
      else {
        if (leverPos == 7) {
          leverPos = -7;
          LoadLever(7, leverBeingUsed);
        }
        else if (leverPos != -7){
          leverPos = 7;
        }
      }
      break;
    case KEYBOARD:
      if (scancode == E) {
        gameState = SINGLEPLAYER;
        LoadSinglePLayer(level->levelnum, false);
      }

      if (scancode == ESC) {
        gameState = PAUSEMENU;
        LoadPauseMenu();
      }
      break;
    case MOUSE:
      mouseEvent = mouse_events(&pack);
      mouse_update(&pack);
      if (!open) {
        open = lever_move_handler(&xlen, &leverState, mouseEvent);
        if (open) {
          leverPos = 7;
          open_lever(leverBeingUsed);
        }
      }
      break;
    case RTC:
      break;
    case SERIALPORT:
      break;
  }
}

//--------------------------------------------------------------------------------------------------

void LoadSinglePLayer(unsigned int levelNum, bool begin) {
  static SinglePlayerGameState singlePlayerState = L1;

  if (begin) {
    switch (levelNum) {
      case 1:
        player = createPlayer(0);
        singlePlayerState = L1;
        player->direction = UP;
        player->x = 105;
        player->y = 650;
        break;
      case 2:
        singlePlayerState = L2;
        player->direction = DOWN;
        player->x = 910;
        player->y = 50;
        break;
      case 3:
        singlePlayerState = L3;
        player->direction = UP;
        player->x = 479;
        player->y = 690;
        break;
      case 4:
        singlePlayerState = L4;
        player->direction = RIGHT;
        player->x = 20;
        player->y = 352;
        break;
      case 5:
        singlePlayerState = L5;
        player->direction = RIGHT;
        player->x = 20;
        player->y = 672;
        break;
      case 6:
        singlePlayerState = L6;
        player->direction = LEFT;
        player->x = 912;
        player->y = 656;
        break;
      case 7:
        singlePlayerState = L7;
        player->direction = DOWN;
        player->x = 96;
        player->y = 48;
        break;
      case 8:
        singlePlayerState = L8;
        player->direction = LEFT;
        player->x = 864;
        player->y = 512;
        break;
      case 9:
        singlePlayerState = L9;
        player->direction = UP;
        player->x = 32;
        player->y = 62;
        break;
      case 10:
        gameState = WON;
        free(player);
        LoadWonMenu();
        break;
      default:
        break;
    }

    if (gameState == SINGLEPLAYER) {
      level = load_level(levelNum);
      player->hasAmmo = false;
    }
  }
  else {
    draw_level_background();
    draw_enemies_level();
    draw_player(player);

    //if (!player->hasAmmo)
      //draw_ammo_level();
  }

  scancode = 0x00;
}

void LoadLeverXPM() {
  xpm_image_t img;

  xpm_load(LeverPos0_xpm, XPM_8_8_8_8, &img);
  LeverPositions[0] = img;
  xpm_load(LeverPos1_xpm, XPM_8_8_8_8, &img);
  LeverPositions[1] = img;
  xpm_load(LeverPos2_xpm, XPM_8_8_8_8, &img);
  LeverPositions[2] = img;
  xpm_load(LeverPos3_xpm, XPM_8_8_8_8, &img);
  LeverPositions[3] = img;
  xpm_load(LeverPos4_xpm, XPM_8_8_8_8, &img);
  LeverPositions[4] = img;
  xpm_load(LeverPos5_xpm, XPM_8_8_8_8, &img);
  LeverPositions[5] = img;
  xpm_load(LeverPos6_xpm, XPM_8_8_8_8, &img);
  LeverPositions[6] = img;

  xpm_load(RedLightLever_xpm, XPM_8_8_8_8, &img);
  LeverColors[0] = img;
  xpm_load(GreenLightLever_xpm, XPM_8_8_8_8, &img);
  LeverColors[1] = img;

  xpm_load(CleanLever_xpm, XPM_8_8_8_8, &img);
  CleanLever = img;

  free(&img);
}

void LoadLever(unsigned int state, Lever * lever) {
  
  switch (state) {
    case 0:
      load_background();

      add_to_background(&LeverColors[0], 192, 418);
      add_to_background(&LeverPositions[0], 175, 175);

      cursor = load_cursor();

      leverBeingUsed = lever;
      break;
    case 1:
      add_to_background(&CleanLever, 92, 48);
      add_to_background(&LeverColors[0], 192, 416);
      add_to_background(&LeverPositions[0], 175, 176);
      break;
    case 2:
      add_to_background(&CleanLever, 92, 48);
      add_to_background(&LeverColors[0], 192, 416);
      add_to_background(&LeverPositions[1], 227, 130);
      break;
    case 3:
      add_to_background(&CleanLever, 92, 48);
      add_to_background(&LeverColors[0], 192, 416);
      add_to_background(&LeverPositions[2], 290, 93);
      break;
    case 4:
      add_to_background(&CleanLever, 92, 48);
      add_to_background(&LeverColors[0], 192, 416);
      add_to_background(&LeverPositions[3], 423, 61);
      break;
    case 5:
      add_to_background(&CleanLever, 92, 48);
      add_to_background(&LeverColors[1], 192, 416);
      add_to_background(&LeverPositions[4], 485, 67);
      break;
    case 6:
      add_to_background(&CleanLever, 92, 48);
      add_to_background(&LeverColors[1], 192, 416);
      add_to_background(&LeverPositions[5], 485, 115);
      break;
    case 7:
      add_to_background(&CleanLever, 92, 48);
      add_to_background(&LeverColors[1], 192, 416);
      add_to_background(&LeverPositions[6], 485, 219);
      break;
  }

  draw_menu_background();
  draw_mouse_cursor();
}

//--------------------------------------------------------------------------------------------------

bool check_final_position() {

  if (player->x > level->finalPos->posfinalx && player->x + player->img.width < level->finalPos->posfinalx + level->finalPos->lado * 16)
    if (player->y > level->finalPos->posfinaly && player->y + player->img.height < level->finalPos->posfinaly + level->finalPos->lado * 16)
      return true;
  
  return false;
}

int check_lever_position() {
  for (unsigned int i = 0; i < level->numLevers; i++) {
    if (level->leverList[i]->active)
        continue;
    if (player->x > level->leverList[i]->x - 32 && player->x + player->img.width < level->leverList[i]->x + level->leverList[i]->img.width + 32)
      if (player->y > level->leverList[i]->y - 64 && player->y + player->img.height < level->leverList[i]->y + level->leverList[i]->img.height + 64)
        return i + 1;
  }

  return 0;
}

void add_final_position_background(int *posfinalx, int *posfinaly, int *lado) {

  for(int i = 0; i < *lado * 16; i++) {
    for (int j = 0; j < *lado * 16; j++) {
      *((uint32_t*)level->level_background.bytes + (*posfinalx + i) + (*posfinaly + j)*hres) = 0x00FF00;
    }
  }
}

struct mouse_ev * mouse_events(struct packet * pack) {
  static bool lb_pressed = false, rb_pressed = false, mb_pressed = false;

  mouse_event.delta_x = pack->delta_x;
  mouse_event.delta_y = pack->delta_y;

  if (!lb_pressed && pack->lb && !rb_pressed && !mb_pressed && !pack->mb && !pack->rb) {
    lb_pressed = true;
    mouse_event.type = LB_PRESSED;
  }
  else if (!rb_pressed && pack->rb && !lb_pressed && !mb_pressed && !pack->mb && !pack->lb) {
    rb_pressed = true;
    mouse_event.type = RB_PRESSED;
  }
  else if (lb_pressed && !pack->lb && !rb_pressed && !mb_pressed && !pack->mb && !pack->rb) {
    lb_pressed = false;
    mouse_event.type = LB_RELEASED;
  }
  else if (rb_pressed && !pack->rb && !lb_pressed && !mb_pressed && !pack->mb && !pack->lb) {
    rb_pressed = false;
    mouse_event.type = RB_RELEASED;
  }
  else if (!mb_pressed && pack->mb) {
    mb_pressed = true;
    mouse_event.type = BUTTON_EV;
  }
  else if(mb_pressed && !pack->mb) {
    mb_pressed = false;
    mouse_event.type = BUTTON_EV;
  }
  else 
    mouse_event.type = MOUSE_MOV;

  return &mouse_event;
}

bool lever_move_handler(int * xlen, LeverState * state, struct mouse_ev * mouse_event) {
  
  switch (*state) {
    case BEGIN:
      *xlen = 177;
      if (mouse_event->type == LB_PRESSED && cursor->x > 170 && cursor->x < 320 && cursor->y > 180 && cursor->y < 290) {
        *state = MOVE_NOTDONE;
      }
      break;
    case MOVE_NOTDONE:
      if (mouse_event->type == MOUSE_MOV) {
        *xlen += mouse_event->delta_x;

        if (*xlen >= 571) {   
          *state = MOVE_DONE;                 
        }
      }   
      else {
        *state = BEGIN;
      }                                                   
      break;
    case MOVE_DONE:
      if (mouse_event->type == LB_RELEASED) {
        *state = BEGIN;
        return true;
      }
      else if (mouse_event->type == MOUSE_MOV) {
        *xlen += mouse_event->delta_x;

        if (*xlen < 571) {   
          *state = MOVE_NOTDONE;                 
        }
      }   
      else {
        *state = BEGIN;
      }                                                   
      break;
  }

  return false;
}









