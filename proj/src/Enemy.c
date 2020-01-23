#include "Enemy.h"

extern unsigned int hres, vres;
extern Level * level;
extern Player * player;

Enemy * createEnemy (int x, int y, Direction direction, bool isStatic) {
  Enemy * enemy = (Enemy *) malloc (sizeof(Enemy));

  enemy->x = x;
  enemy->y = y;
  
  enemy->moveAnimation = 0;
  enemy->reloadAnimation = 0;
  enemy->isReloading = false;

  enemy->xspeed = 3;
  enemy->yspeed = 3;
  enemy->isMoving = true;
  enemy->isAttacking = false;
  enemy->dead = false;
  enemy->direction = direction;
  enemy->isStatic = isStatic;

  enemy->bullet = (Bullet *) malloc(sizeof(Bullet));

  enemy->bullet->type = NORMAL;
  enemy->bullet->direction = enemy->direction;
  enemy->bullet->x = enemy->x;
  enemy->bullet->y = enemy->y;
  enemy->bullet->speed = 17;

  xpm_load(Bullet_xpm, XPM_8_8_8_8, &enemy->bullet->img);
;
  enemy->bullet->active = false;

  xpm_image_t img;

  //Load move animation
  if (!isStatic) {
    xpm_load(enemy_idle_0_xpm, XPM_8_8_8_8, &img);
    enemy->MoveRight[0] = img;
    xpm_load(enemy_idle_1_xpm, XPM_8_8_8_8, &img);
    enemy->MoveRight[1] = img;
    xpm_load(enemy_idle_2_xpm, XPM_8_8_8_8, &img);
    enemy->MoveRight[2] = img;
    xpm_load(enemy_idle_3_xpm, XPM_8_8_8_8, &img);
    enemy->MoveRight[3] = img;
    xpm_load(enemy_idle_4_xpm, XPM_8_8_8_8, &img);
    enemy->MoveRight[4] = img;
    xpm_load(enemy_idle_5_xpm, XPM_8_8_8_8, &img);
    enemy->MoveRight[5] = img;

  }
  else {
    xpm_load(enemy_idle_0_xpm, XPM_8_8_8_8, &img);
    enemy->MoveRight[0] = img;
    xpm_load(enemy_idle_1_xpm, XPM_8_8_8_8, &img);
    enemy->MoveRight[1] = img;
    xpm_load(enemy_idle_2_xpm, XPM_8_8_8_8, &img);
    enemy->MoveRight[2] = img;
    xpm_load(enemy_idle_3_xpm, XPM_8_8_8_8, &img);
    enemy->MoveRight[3] = img;
    xpm_load(enemy_idle_4_xpm, XPM_8_8_8_8, &img);
    enemy->MoveRight[4] = img;
    xpm_load(enemy_idle_5_xpm, XPM_8_8_8_8, &img);
    enemy->MoveRight[5] = img;

    xpm_load(enemy_reload_0_xpm, XPM_8_8_8_8, &img);
    enemy->ReloadRight[0] = img;
    xpm_load(enemy_reload_1_xpm, XPM_8_8_8_8, &img);
    enemy->ReloadRight[1] = img;
    xpm_load(enemy_reload_2_xpm, XPM_8_8_8_8, &img);
    enemy->ReloadRight[2] = img;
    xpm_load(enemy_reload_3_xpm, XPM_8_8_8_8, &img);
    enemy->ReloadRight[3] = img;
    xpm_load(enemy_reload_4_xpm, XPM_8_8_8_8, &img);
    enemy->ReloadRight[4] = img;
    xpm_load(enemy_reload_5_xpm, XPM_8_8_8_8, &img);
    enemy->ReloadRight[5] = img;
    xpm_load(enemy_reload_6_xpm, XPM_8_8_8_8, &img);
    enemy->ReloadRight[6] = img;
    xpm_load(enemy_reload_7_xpm, XPM_8_8_8_8, &img);
    enemy->ReloadRight[7] = img;

  }
  
  enemy->img = enemy->MoveRight[0];

  return enemy;
}

void draw_enemy(Enemy * enemy) {

  if (enemy->dead)
    return;

  uint32_t* map = (uint32_t*) enemy->img.bytes;

  switch(enemy->direction) {
    case UP:
    {
      for(int j = 0 ; j < enemy->img.height; j++) {
        for (int i = 0 ; i < enemy->img.width ; i++) {
          if (*(map + i + j*enemy->img.width) != xpm_transparency_color(XPM_8_8_8_8))
            changePixelColor(enemy->x + j,enemy->y + enemy->img.width - i ,*(map + i + j*enemy->img.width));
        }
      }
      break;
    }
    case DOWN:
    {
      for(int i = 0; i < enemy->img.width; i++) {
        for (int j = 0; j < enemy->img.height; j++) {
          if (*(map + i + j*enemy->img.width) != xpm_transparency_color(XPM_8_8_8_8))
            changePixelColor(enemy->x + enemy->img.height - j,enemy->y + i,*(map + i + j*enemy->img.width));
        }
      }
      break;
    }
    case LEFT:
    {
      map += enemy->img.height * enemy->img.width - 1;

      for(int i = 0; i < enemy->img.width; i++) {
        for (int j = 0; j < enemy->img.height; j++) {
          if (*(map - i - j*enemy->img.width) != xpm_transparency_color(XPM_8_8_8_8))
            changePixelColor(enemy->x+i,enemy->y+j,*(map - i - j*enemy->img.width));
        }
      }
      break;
    }
    case RIGHT:
    {
      for(int i = 0; i < enemy->img.width; i++) {
        for (int j = 0; j < enemy->img.height; j++) {
          if (*(map + i + j*enemy->img.width) != xpm_transparency_color(XPM_8_8_8_8))
            changePixelColor(enemy->x+i,enemy->y+j,*(map + i + j*enemy->img.width));
        }
      }
      break;
    }
  }
}

void clean_enemy(Enemy * enemy) {
  if (enemy->dead)
    return;

  for (int i = enemy->x; i <= enemy->x + enemy->img.width; i++) {
    for (int j = enemy->y; j <= enemy->y + enemy->img.height; j++) {
      if (i < (int)hres - 1 && j < (int)vres - 1)
        changePixelColor(i,j,*(level->level_back + i + j * hres));
    }
  }
}

void enemy_death(Enemy * enemy) {
  clean_enemy(enemy);
  enemy->dead = true;
}

void enemy_movement(Enemy * enemy) {
  if (enemy->dead || enemy->isStatic || enemy->isAttacking)
    return;

  bool up = false, down = false, right = false, left = false;

  switch(enemy->direction) {
    case UP:
      up = true;
      break;
    case DOWN:
      down = true;
      break;
    case LEFT:
      left = true;
      break;
    case RIGHT:
      right = true;
      break;
  }

  if (up) {
    if(!check_enemy_collision_walls(enemy)) {
      clean_enemy(enemy);

      if (enemy->y - enemy->yspeed < 0) {
        enemy->direction = DOWN;
        enemy->y = 0;
      }
      else  
        enemy->y -= enemy->yspeed;
  
      draw_enemy(enemy);
    }
    else {
      enemy->direction = DOWN;
    }
  }
  else if (down) {
    if (!check_enemy_collision_walls(enemy)) {
      clean_enemy(enemy);

      if (enemy->y + enemy->yspeed > (int)vres - enemy->img.height) {
        enemy->direction = UP;
        enemy->y = (int)vres - enemy->img.height - 1;
      }
      else  
        enemy->y += enemy->yspeed;
      
      draw_enemy(enemy);
    }
    else {
      enemy->direction = UP;
    }
  }
  else if (right) {
    if(!check_enemy_collision_walls(enemy)) {
      clean_enemy(enemy);

      if (enemy->x + enemy->xspeed + enemy->img.width > (int)hres) {
        enemy->direction = LEFT;
        enemy->x = (int)hres - enemy->img.width - 1;
      }
      else
        enemy->x += enemy->xspeed;
      
      draw_enemy(enemy);
    }
    else {
      enemy->direction = LEFT;
    }
  }
  else if (left) {
    if(!check_enemy_collision_walls(enemy)) {
      clean_enemy(enemy);

      if (enemy->x - enemy->xspeed < 0) {
        enemy->direction = RIGHT;
        enemy->x = 0;
      }
      else  
        enemy->x -= enemy->xspeed;

      draw_enemy(enemy);
    }
    else {
      enemy->direction = RIGHT;
    }
  }
  
}

bool check_enemy_collision_walls(Enemy * enemy) {
  switch (enemy->direction) {
    case UP:
      for (int i = enemy->x; i <= enemy->x + enemy->img.width; i++) {
        for (int j = enemy->y; j >= enemy->y - enemy->yspeed; j--) {
          if(*(level->level_walls + i + j * hres) == 0)
            return true;
        }
      }
      break;
    case DOWN:
      for (int i = enemy->x; i <= enemy->x + enemy->img.width; i++) {
        for (int j = enemy->y + enemy->img.height; j <= enemy->y + enemy->img.height + enemy->yspeed; j++) {
          if(*(level->level_walls + i + j * hres) == 0)
            return true;
        }
      }
      break;
    case LEFT:
      for (int i = enemy->x; i >= enemy->x - enemy->xspeed; i--) {
        for (int j = enemy->y; j <= enemy->y + enemy->img.height; j++) {
          if(*(level->level_walls + i + j * hres) == 0)
            return true;
        }
      }
      break;
    case RIGHT:
      for (int i = enemy->x + enemy->img.width; i <= enemy->x + enemy->xspeed + enemy->img.width; i++) {
        for (int j = enemy->y; j <= enemy->y + enemy->img.height; j++) {
          if(*(level->level_walls + i + j * hres) == 0)
            return true;
        }
      }
      break;    
  }

  return false;
}


void enemy_idle_animation(Enemy * enemy) {
  clean_enemy(enemy);
  draw_enemy(enemy);
  enemy->img = enemy->MoveRight[enemy->moveAnimation];
  enemy->moveAnimation++;
  if (enemy->moveAnimation == 6) {
    enemy->moveAnimation = 0;
  }
}

void enemy_reload_animation(Enemy * enemy) {
  clean_enemy(enemy);
  draw_enemy(enemy);
  enemy->img = enemy->ReloadRight[enemy->reloadAnimation];
  enemy->reloadAnimation++;
  if (enemy->reloadAnimation == 8) {
    enemy->reloadAnimation = 0;
    enemy->moveAnimation = 0;
    enemy->isReloading = false;
  }
}

