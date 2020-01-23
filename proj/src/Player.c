#include "Player.h"

extern unsigned int hres, vres;
extern uint8_t scancode;
extern Level * level;
extern GameState gameState;

//Player * player;

Player * createPlayer (unsigned int playerNum) {
  Player * player = (Player *) malloc (sizeof(Player));

  player->x = 0;
  player->y = 0;
  player->xspeed = 3;
  player->yspeed = 3;
  player->isIdle = true;
  player->hasAmmo = false;
  player->isReloading = false;
  player->playerNum = playerNum;

  xpm_image_t img;

  switch (playerNum) {
  case 0: // SINGLE-PLAYER
    //Load idle animation
    xpm_load(player_idle_0_xpm, XPM_8_8_8_8, &img);
    player->IdleRight[0] = img;
    xpm_load(player_idle_1_xpm, XPM_8_8_8_8, &img);
    player->IdleRight[1] = img;
    xpm_load(player_idle_2_xpm, XPM_8_8_8_8, &img);
    player->IdleRight[2] = img;
    xpm_load(player_idle_3_xpm, XPM_8_8_8_8, &img);
    player->IdleRight[3] = img;
    xpm_load(player_idle_4_xpm, XPM_8_8_8_8, &img);
    player->IdleRight[4] = img;

    //Load reload animation
    xpm_load(player_reload_0_xpm, XPM_8_8_8_8, &img);
    player->ReloadRight[0] = img;
    xpm_load(player_reload_1_xpm, XPM_8_8_8_8, &img);
    player->ReloadRight[1] = img;
    xpm_load(player_reload_2_xpm, XPM_8_8_8_8, &img);
    player->ReloadRight[2] = img;
    xpm_load(player_reload_3_xpm, XPM_8_8_8_8, &img);
    player->ReloadRight[3] = img;
    xpm_load(player_reload_4_xpm, XPM_8_8_8_8, &img);
    player->ReloadRight[4] = img;
    xpm_load(player_reload_5_xpm, XPM_8_8_8_8, &img);
    player->ReloadRight[5] = img;

    //Load shoot animation
    xpm_load(player_shoot_0_xpm, XPM_8_8_8_8, &img);
    player->ShootRight[0] = img;
    xpm_load(player_shoot_1_xpm, XPM_8_8_8_8, &img);
    player->ShootRight[1] = img;
    xpm_load(player_shoot_2_xpm, XPM_8_8_8_8, &img);
    player->ShootRight[2] = img;
    break;
  
  case 1: // MULTI-PLAYER - PLAYER 1
    player->x = 100;
    player->y = 100;

    //Load idle animation
    xpm_load(player_idle_0_blue_xpm, XPM_8_8_8_8, &img);
    player->IdleRight[0] = img;
    xpm_load(player_idle_1_blue_xpm, XPM_8_8_8_8, &img);
    player->IdleRight[1] = img;
    xpm_load(player_idle_2_blue_xpm, XPM_8_8_8_8, &img);
    player->IdleRight[2] = img;
    xpm_load(player_idle_3_blue_xpm, XPM_8_8_8_8, &img);
    player->IdleRight[3] = img;
    xpm_load(player_idle_4_blue_xpm, XPM_8_8_8_8, &img);
    player->IdleRight[4] = img;

    //Load reload animation
    xpm_load(player_reload_0_blue_xpm, XPM_8_8_8_8, &img);
    player->ReloadRight[0] = img;
    xpm_load(player_reload_1_blue_xpm, XPM_8_8_8_8, &img);
    player->ReloadRight[1] = img;
    xpm_load(player_reload_2_blue_xpm, XPM_8_8_8_8, &img);
    player->ReloadRight[2] = img;
    xpm_load(player_reload_3_blue_xpm, XPM_8_8_8_8, &img);
    player->ReloadRight[3] = img;
    xpm_load(player_reload_4_blue_xpm, XPM_8_8_8_8, &img);
    player->ReloadRight[4] = img;
    xpm_load(player_reload_5_blue_xpm, XPM_8_8_8_8, &img);
    player->ReloadRight[5] = img;

    //Load shoot animation
    xpm_load(player_shoot_0_blue_xpm, XPM_8_8_8_8, &img);
    player->ShootRight[0] = img;
    xpm_load(player_shoot_1_blue_xpm, XPM_8_8_8_8, &img);
    player->ShootRight[1] = img;
    xpm_load(player_shoot_2_blue_xpm, XPM_8_8_8_8, &img);
    player->ShootRight[2] = img;
    break;

  case 2: // MULTI-PLAYER - PLAYER 2
    player->x = 875;
    player->y = 600;

    //Load idle animation
    xpm_load(player_idle_0_red_xpm, XPM_8_8_8_8, &img);
    player->IdleRight[0] = img;
    xpm_load(player_idle_1_red_xpm, XPM_8_8_8_8, &img);
    player->IdleRight[1] = img;
    xpm_load(player_idle_2_red_xpm, XPM_8_8_8_8, &img);
    player->IdleRight[2] = img;
    xpm_load(player_idle_3_red_xpm, XPM_8_8_8_8, &img);
    player->IdleRight[3] = img;
    xpm_load(player_idle_4_red_xpm, XPM_8_8_8_8, &img);
    player->IdleRight[4] = img;

    //Load reload animation
    xpm_load(player_reload_0_red_xpm, XPM_8_8_8_8, &img);
    player->ReloadRight[0] = img;
    xpm_load(player_reload_1_red_xpm, XPM_8_8_8_8, &img);
    player->ReloadRight[1] = img;
    xpm_load(player_reload_2_red_xpm, XPM_8_8_8_8, &img);
    player->ReloadRight[2] = img;
    xpm_load(player_reload_3_red_xpm, XPM_8_8_8_8, &img);
    player->ReloadRight[3] = img;
    xpm_load(player_reload_4_red_xpm, XPM_8_8_8_8, &img);
    player->ReloadRight[4] = img;
    xpm_load(player_reload_5_red_xpm, XPM_8_8_8_8, &img);
    player->ReloadRight[5] = img;

    //Load shoot animation
    xpm_load(player_shoot_0_red_xpm, XPM_8_8_8_8, &img);
    player->ShootRight[0] = img;
    xpm_load(player_shoot_1_red_xpm, XPM_8_8_8_8, &img);
    player->ShootRight[1] = img;
    xpm_load(player_shoot_2_red_xpm, XPM_8_8_8_8, &img);
    player->ShootRight[2] = img;
    break;

  default:
    break;
  }
  
  if (playerNum != 0)
    player->numLives = 3;
  else
    player->numLives = 1;

  player->img = player->IdleRight[0];

  if (playerNum != 2)
    player->direction = RIGHT;
  else
    player->direction = LEFT;

  free(&img);

  return player;
}

void draw_player(Player * player) {
  uint32_t* map = (uint32_t*) player->img.bytes;
  switch(player->direction) {
    case UP:
    {
      for(int j = 0 ; j < player->img.height; j++) {
        for (int i = 0 ; i < player->img.width ; i++) {
          if (*(map + i + j*player->img.width) != xpm_transparency_color(XPM_8_8_8_8))
            changePixelColor(player->x + j,player->y + player->img.width - i ,*(map + i + j*player->img.width));
        }
      }
      break;
    }
    case DOWN:
    {
      for(int i = 0; i < player->img.width; i++) {
        for (int j = 0; j < player->img.height; j++) {
          if (*(map + i + j*player->img.width) != xpm_transparency_color(XPM_8_8_8_8))
            changePixelColor(player->x + player->img.height - j,player->y + i,*(map + i + j*player->img.width));
        }
      }
      break;
    }
    case LEFT:
    {
      map += player->img.height * player->img.width;

      for(int i = 0; i < player->img.width; i++) {
        for (int j = 0; j < player->img.height; j++) {
          if (*(map - i - j*player->img.width) != xpm_transparency_color(XPM_8_8_8_8))
            changePixelColor(player->x+i,player->y+j,*(map - i - j*player->img.width));
        }
      }
      break;
    }
    case RIGHT:
    {
      for(int i = 0; i < player->img.width; i++) {
        for (int j = 0; j < player->img.height; j++) {
          if (*(map + i + j*player->img.width) != xpm_transparency_color(XPM_8_8_8_8))
            changePixelColor(player->x+i,player->y+j,*(map + i + j*player->img.width));
        }
      }
      break;
    }
  }
}

void clean_player(Player * player) {

  for (int i = player->x; i <= player->x + player->img.width; i++) {
    for (int j = player->y; j <= player->y + player->img.height; j++) {
      if (i < (int)hres - 1 && j < (int)vres - 1)
        changePixelColor(i,j,*(level->level_back + i + j * hres));
    }
  }

}

void update_movement_direction(Player * player, uint8_t scancode, bool * up, bool * down, bool * left, bool * right) {

  if (scancode == 0x11 /*Make-code W*/ || scancode == 0x48 /*Make-code Up-arrow*/) {
    *up = true;
    player->direction = UP;
  }
  else if (scancode == 0x1F /*Make-code S*/ || scancode == 0x50 /*Make-code Down-arrow*/) {
    *down = true;
    player->direction = DOWN;
  }
  else if (scancode == 0x20 /*Make-code D*/ || scancode == 0x4D /*Make-code Right-arrow*/) {
    *right = true;
    player->direction = RIGHT;
  }
  else if (scancode == 0x1E /*Make-code A*/ || scancode == 0x4B /*Make-code Left-arrow*/) {
    *left = true;
    player->direction = LEFT;
  }
  else if (scancode == 0x91 /*Break-code W*/ || scancode == 0xC8 /*Break-code Up-arrow*/)
    *up = false;  
  else if (scancode == 0x9F /*Break-code S*/ || scancode == 0xD0 /*Break-code Down-arrow*/)
    *down = false;
  else if (scancode == 0xA0 /*Break-code D*/ || scancode == 0xCD /*Break-code Right-arrow*/)
    *right = false;
  else if (scancode == 0x9E /*Break-code A*/ || scancode == 0xCB /*Break-code Left-arrow*/)
    *left = false;

}

void check_movement(Player * player, bool * upPtr, bool * downPtr, bool * leftPtr, bool * rightPtr) {

  static bool up, down, left, right;

  up = *upPtr; down = *downPtr; left = *leftPtr; right = *rightPtr; 

  if (up && !right && !left && !down)
    player->direction = UP;
  else if (down && !right && !left && !up) 
    player->direction = DOWN;
  else if (!up && right && !left && !down)
    player->direction = RIGHT;
  else if (!up && !right && left && !down) 
    player->direction = LEFT;

  if (up && !check_collision_walls(player,UP) && !player->isReloading) {
    if (!player->hasAmmo && check_collision_ammo(player,UP)) {
      player->hasAmmo = true;
      player->isReloading = true;
      player->isIdle = false;
    }

    player->isIdle = false;
    clean_player(player);
    if (player->y - player->yspeed < 0)
      player->y = 0;
    else  
      player->y -= player->yspeed;

    if (right && !check_collision_walls(player,RIGHT)) {
      if (!player->hasAmmo && check_collision_ammo(player,RIGHT)) {
        player->hasAmmo = true;
        player->isReloading = true;
        player->isIdle = false;
      }
      if (player->x + player->xspeed + player->img.width > (int)hres)
        player->x = (int)hres - player->img.width;
      else  
        player->x += player->xspeed;
    }
    if (left && !check_collision_walls(player,LEFT)) {
      if (!player->hasAmmo && check_collision_ammo(player,LEFT)) {
        player->hasAmmo = true;
        player->isReloading = true;
        player->isIdle = false;
      }
      if (player->x - player->xspeed < 0)
        player->x = 0;
      else  
        player->x -= player->xspeed;
    }
    if (down && !check_collision_walls(player,DOWN)) {
      if (!player->hasAmmo && check_collision_ammo(player,DOWN)) {
        player->hasAmmo = true;
        player->isReloading = true;
        player->isIdle = false;
      }
      if (player->y + player->yspeed > (int)vres - player->img.height - 4)
        player->y = (int)vres - player->img.height - 4;
      else  
        player->y += player->yspeed;
    } 
    draw_player(player);
  }
  else if (down && !check_collision_walls(player,DOWN) && !player->isReloading) {
    if (!player->hasAmmo && check_collision_ammo(player,DOWN)) {
      player->hasAmmo = true;
      player->isReloading = true;
      player->isIdle = false;
    }

    player->isIdle = false;
    clean_player(player);
    if (player->y + player->yspeed > (int)vres - player->img.height - 4)
      player->y = (int)vres - player->img.height - 4;
    else  
      player->y += player->yspeed;
    
    if (right && !check_collision_walls(player,RIGHT)) {
      if (!player->hasAmmo && check_collision_ammo(player,RIGHT)) {
        player->hasAmmo = true;
        player->isReloading = true;
        player->isIdle = false;
      }
      if (player->x + player->xspeed > (int)hres - player->img.width)
        player->x = (int)hres - player->img.width;
      else  
        player->x += player->xspeed;
    }
    if (left && !check_collision_walls(player,LEFT)) {
      if (!player->hasAmmo && check_collision_ammo(player,LEFT)) {
        player->hasAmmo = true;
        player->isReloading = true;
        player->isIdle = false;
      }
      if (player->x - player->xspeed < 0)
        player->x = 0;
      else  
        player->x -= player->xspeed;
    }
    draw_player(player);
  }
  else if (right && !check_collision_walls(player,RIGHT) && !player->isReloading) {
    if (!player->hasAmmo && check_collision_ammo(player,RIGHT)) {
      player->hasAmmo = true;
      player->isReloading = true;
      player->isIdle = false;
    }

    player->isIdle = false;
    clean_player(player);
    if (player->x + player->xspeed + player->img.width > (int)hres)
      player->x = (int)hres - player->img.width;
    else  
      player->x += player->xspeed;
    
    if (left && !check_collision_walls(player,LEFT)) {
      if (!player->hasAmmo && check_collision_ammo(player,LEFT)) {
        player->hasAmmo = true;
        player->isReloading = true;
        player->isIdle = false;
      }
      if (player->x - player->xspeed < 0)
        player->x = 0;
      else  
        player->x -= player->xspeed;
    }
    draw_player(player);
  }
  else if (left && !check_collision_walls(player, LEFT) && !player->isReloading) {
    if (!player->hasAmmo && check_collision_ammo(player, LEFT)) {
      player->hasAmmo = true;
      player->isReloading = true;
      player->isIdle = false;
    }

    player->isIdle = false;
    clean_player(player);
    if (player->x - player->xspeed < 0)
      player->x = 0;
    else  
      player->x -= player->xspeed;
    draw_player(player);
  }
  else if (!player->isReloading){
    player->isIdle = true;
  }
  
  if (check_collision_enemy(player, player->direction, level->enemyList, level->numEnemies)) {
    up = false;
    down = false;
    left = false;
    right = false;
  } 
  
}

void idle_animation(Player * player) {
  static unsigned int idleAnimationNum = 0;

  clean_player(player);
  draw_player(player);
  player->img = player->IdleRight[idleAnimationNum];
  idleAnimationNum++;
  if (idleAnimationNum == 5) {
    player->isReloading = false;
    player->isShooting = false;
    idleAnimationNum = 0;
  }
}

void reload_animation(Player * player) {
  static unsigned int reloadAnimationNum = 0;

  clean_player(player);
  draw_player(player);
  player->img = player->ReloadRight[reloadAnimationNum];
  reloadAnimationNum++;
  if (reloadAnimationNum == 6) {
    player->isIdle = true;
    player->isReloading = false;
    player->isShooting = false;
    reloadAnimationNum = 0;
  }
}

void shoot_animation(Player * player) {
  static unsigned int shootAnimationNum = 0;

  clean_player(player);
  draw_player(player);
  player->img = player->ShootRight[shootAnimationNum];
  shootAnimationNum++;
  if (shootAnimationNum == 2) {
    player->isIdle = true;
    player->isShooting = false;
    player->isReloading = false;
    shootAnimationNum = 0;
  }
}

bool check_collision_walls(Player * player, Direction direction) {
  switch (direction) {
    case UP:
      if (player->y + player->img.width >= (int) hres)
        player->y = hres - player->img.width - 5;
      for (int i = player->x + 3; i <= player->x + player->img.width - 3; i++) {
        for (int j = player->y; j >= player->y - player->yspeed; j--) {
          if(*(level->level_walls + i + j * hres) == 0)
            return true;
        }
      }
      break;
    case DOWN:
      if (player->y + player->img.width >= (int) hres)
        player->y = hres - player->img.width - 5;
      for (int i = player->x + 3; i <= player->x + player->img.width - 3; i++) {
        for (int j = player->y + player->img.height; j <= player->y + player->img.height + player->yspeed; j++) {
          if(*(level->level_walls + i + j * hres) == 0)
            return true;
        }
      }
      break;
    case LEFT:
      if (player->y + player->img.width >= (int) hres)
        player->y = hres - player->img.width - 5;
      for (int i = player->x; i >= player->x - player->xspeed; i--) {
        for (int j = player->y + 3; j <= player->y + player->img.height - 3; j++) {
          if(*(level->level_walls + i + j * hres) == 0)
            return true;
        }
      }
      break;
    case RIGHT:
      if (player->y + player->img.width >= (int) hres)
        player->y = hres - player->img.width - 5;
      for (int i = player->x + player->img.width; i <= player->x + player->xspeed + player->img.width; i++) {
        for (int j = player->y + 3; j <= player->y + player->img.height - 3; j++) {
          if(*(level->level_walls + i + j * hres) == 0)
            return true;
        }
      }
      break;    
  }

  return false;
}

bool check_collision_ammo(Player * player, Direction direction) {
  switch (direction) {
    case UP:
       for (int i = player->x + 16; i <= player->x + player->img.width - 16; i++) {
        for (int j = player->y + 16; j >= player->y - player->yspeed + 16; j--) {
          for (unsigned int k = 0; k < level->numAmmo; k++) {
            if ((int)level->ammoList[k]->x < i && (int)level->ammoList[k]->x + 32 > i && (int)level->ammoList[k]->y < j && (int)level->ammoList[k]->y + 16 > j) {
              clean_ammo_level();
              return true;
            }
          }
        }
      }
      break;
    case DOWN:
      for (int i = player->x + 16; i <= player->x + player->img.width - 16; i++) {
        for (int j = player->y + player->img.height - 16; j <= player->y + player->img.height + player->yspeed - 16; j++) {
          for (unsigned int k = 0; k < level->numAmmo; k++) {
            if ((int)level->ammoList[k]->x < i && (int)level->ammoList[k]->x + 32 > i && (int)level->ammoList[k]->y < j && (int)level->ammoList[k]->y + 16 > j)
            {
              clean_ammo_level();
              return true;
            }
          }
        }
      }
      break;
    case LEFT:
      for (int i = player->x + 16; i >= player->x - player->xspeed + 16; i--) {
        for (int j = player->y + 16; j <= player->y + player->img.height - 16; j++) {
          for (unsigned int k = 0; k < level->numAmmo; k++) {
            if ((int)level->ammoList[k]->x < i && (int)level->ammoList[k]->x + 32 > i && (int)level->ammoList[k]->y < j && (int)level->ammoList[k]->y + 16 > j)
            {
              clean_ammo_level();
              return true;
            }
          }
        }
      }
      break;
    case RIGHT:
      for (int i = player->x + player->img.width - 16; i <= player->x + player->xspeed + player->img.width - 16; i++) {
        for (int j = player->y + 16; j <= player->y + player->img.height - 16; j++) {
          for (unsigned int k = 0; k < level->numAmmo; k++) {
            if ((int)level->ammoList[k]->x < i && (int)level->ammoList[k]->x + 32 > i && (int)level->ammoList[k]->y < j && (int)level->ammoList[k]->y + 16 > j)
            {
              clean_ammo_level();
              return true;
            }
          }
        }
      }
      break;    
  }

  return false;
}

bool check_collision_enemy(Player * player, Direction direction, Enemy ** enemies, unsigned int numEnemies) {
  switch (direction) {
    case UP:
       for (int i = player->x + 16; i <= player->x + player->img.width - 16; i++) {
        for (int j = player->y + 16; j >= player->y - player->yspeed + 16; j--) {
          for (unsigned int k = 0; k < numEnemies; k++) {
            if (enemies[k]->dead)
              continue;
            if (i > enemies[k]->x && i < enemies[k]->x + enemies[k]->img.width &&
                j > enemies[k]->y && j < enemies[k]->y + enemies[k]->img.height) {
                  return true;
            }
          }
        }
      }
      break;
    case DOWN:
      for (int i = player->x + 16; i <= player->x + player->img.width - 16; i++) {
        for (int j = player->y + player->img.height - 16; j <= player->y + player->img.height + player->yspeed - 16; j++) {
          for (unsigned int k = 0; k < numEnemies; k++) {
            if (enemies[k]->dead)
              continue;
            if (i > enemies[k]->x && i < enemies[k]->x + enemies[k]->img.width &&
                j > enemies[k]->y && j < enemies[k]->y + enemies[k]->img.height) {
                  return true;
            }
          }
        }
      }
      break;
    case LEFT:
      for (int i = player->x + 16; i >= player->x - player->xspeed + 16; i--) {
        for (int j = player->y + 16; j <= player->y + player->img.height - 16; j++) {
          for (unsigned int k = 0; k < numEnemies; k++) {
            if (enemies[k]->dead)
              continue;
            if (i > enemies[k]->x && i < enemies[k]->x + enemies[k]->img.width &&
                j > enemies[k]->y && j < enemies[k]->y + enemies[k]->img.height) {
                  return true;
            }
          }
        }
      }
      break;
    case RIGHT:
      for (int i = player->x + player->img.width - 16; i <= player->x + player->xspeed + player->img.width - 16; i++) {
        for (int j = player->y + 16; j <= player->y + player->img.height - 16; j++) {
          for (unsigned int k = 0; k < numEnemies; k++) {
            if (enemies[k]->dead)
              continue;
            if (i > enemies[k]->x && i < enemies[k]->x + enemies[k]->img.width &&
                j > enemies[k]->y && j < enemies[k]->y + enemies[k]->img.height) {
                  return true;
            }
          }
        }
      }
      break;    
  }

  return false;
}


//--------------------------------------------------------------------------------------------------


Bullet * createBullet(Player * player, BulletType type) {
  Bullet * bullet = (Bullet *) malloc(sizeof(Bullet));

  bullet->type = type;
  bullet->direction = player->direction;
  bullet->x = player->x;
  bullet->y = player->y;
  bullet->speed = 15;
  bullet->active = true;

  xpm_load(Bullet_xpm, XPM_8_8_8_8, &bullet->img);

  return bullet;
}

Bullet * shoot(Player * player) {

  Bullet * bullet = createBullet(player, NORMAL);

  player->hasAmmo = false;
  player->isShooting = true;
  player->isIdle = false;

  switch (bullet->direction) {
    case UP:
      bullet->x += player->img.width - 40;
      bullet->y -= 25;
      break;
    case DOWN:
      bullet->x += 5;
      bullet->y += player->img.height;
      break;
    case LEFT:
      bullet->x -= 35;
      bullet->y += 5;
      break;
    case RIGHT:
      bullet->x += player->img.width;
      bullet->y += player->img.height - 35;
      break;     
  }

  return bullet;
}

bool enemyBulletAnimation(Bullet * bullet, Player * player) {
  clean_bullet(bullet);

  switch (bullet->direction) {
    case UP:
      if (!check_collision_with_player(bullet, player)) {
        bullet->y -= bullet->speed;
        draw_bullet(bullet);
        return true;
      }
      break;
    case DOWN:
      if (!check_collision_with_player(bullet, player)) {
        bullet->y += bullet->speed;
        draw_bullet(bullet);
        return true;
      }
      break;
    case LEFT:
      if (!check_collision_with_player(bullet, player)) {
        bullet->x -= bullet->speed;
        draw_bullet(bullet);
        return true;
      }
      break;
    case RIGHT:
      if (!check_collision_with_player(bullet, player)) {
        bullet->x += bullet->speed;
        draw_bullet(bullet);
        return true;
      }
  }

  return false;
}

bool check_collision_with_player(Bullet * bullet, Player * player) {
  switch (bullet->direction) {
    case UP:
      // CHECK COLLISIONS WITH PLAYER
      for (int i = bullet->x; i <= (int)bullet->x + (int)bullet->img.width; i++) {
        for (int j = bullet->y; j >= (int)bullet->y - (int)bullet->speed; j--) {
          if (i > player->x && i < player->x + player->img.width &&
              j > player->y && j < player->y + player->img.height) {
                bullet->active = false;
                draw_bullet(bullet);
                player->numLives--;
                if (player->playerNum != 0)
                  clean_heart(player->playerNum, player->numLives);
                return true;
          }
        }
      }

      // CHECK COLLISIONS WITH WALLS
      for (unsigned int i = bullet->x; i <= bullet->x + bullet->img.width; i++) {
        for (unsigned int j = bullet->y; j >= bullet->y - bullet->speed; j--) {
          if(*(level->level_walls + i + j * hres) == 0) {
            bullet->y = j + 1;
            bullet->active = false;
            return true;
          }
        }
      }
      break;
    case DOWN:
      // CHECK COLLISIONS WITH PLAYER
      for (int i = bullet->x; i <= (int)bullet->x + (int)bullet->img.width; i++) {
        for (int j = bullet->y + bullet->img.height; j <= (int)bullet->y + (int)bullet->img.height + (int)bullet->speed; j++) {
          if (i > player->x && i < player->x + player->img.width &&
              j > player->y && j < player->y + player->img.height) {
                bullet->active = false;
                draw_bullet(bullet);
                player->numLives--;
                if (player->playerNum != 0)
                  clean_heart(player->playerNum, player->numLives);
                return true;
          }
        }
      }

      // CHECK COLLISIONS WITH WALLS
      for (unsigned int i = bullet->x; i <= bullet->x + bullet->img.width; i++) {
        for (unsigned int j = bullet->y + bullet->img.height; j <= bullet->y + bullet->img.height + (int)bullet->speed; j++) {
          if(*(level->level_walls + i + j * hres) == 0) {
            bullet->y = j - 1;
            bullet->active = false;
            return true;
          }
        }
      }
      break;
    case LEFT:
      // CHECK COLLISIONS WITH PLAYER
      for (int i = bullet->x; i >= (int)bullet->x - (int)bullet->speed; i--) {
        for (int j = bullet->y; j <= (int)bullet->y + (int)bullet->img.height; j++) {
          if (i > player->x && i < player->x + player->img.width &&
              j > player->y && j < player->y + player->img.height) {
                bullet->active = false;
                draw_bullet(bullet);
                player->numLives--;
                if (player->playerNum != 0)
                  clean_heart(player->playerNum, player->numLives);
                return true;
          }
        }
      }

      // CHECK COLLISIONS WITH WALLS
      for (unsigned int i = bullet->x; i >= bullet->x - bullet->speed; i--) {
        for (unsigned int j = bullet->y; j <= bullet->y + bullet->img.height; j++) {
          if(*(level->level_walls + i + j * hres) == 0) {
            bullet->x = i - 1;
            bullet->active = false;
            return true;
          }
        }
      }
      break;
    case RIGHT:
      // CHECK COLLISIONS WITH PLAYER
      for (int i = bullet->x + bullet->img.width; i <= (int)bullet->x + (int)bullet->speed + bullet->img.width; i++) {
        for (int j = bullet->y; j <= (int)bullet->y + (int)bullet->img.height; j++) {
          if (i > player->x && i < player->x + player->img.width &&
              j > player->y && j < player->y + player->img.height) {
                bullet->active = false;
                draw_bullet(bullet);
                player->numLives--;
                if (player->playerNum != 0)
                  clean_heart(player->playerNum, player->numLives);
                return true;
          }
        }
      }

      // CHECK COLLISIONS WITH WALLS
      for (unsigned int i = bullet->x + bullet->img.width; i <= bullet->x + bullet->speed + bullet->img.width; i++) {
        for (unsigned int j = bullet->y; j <= bullet->y + bullet->img.height; j++) {
          if(*(level->level_walls + i + j * hres) == 0) {
            bullet->x = i + 1;
            bullet->active = false;
            return true;
          }
        }
      }
      break;    
  }

  return false;
}

