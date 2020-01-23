#include "Bullet.h"

extern Player * player;
extern Level * level;

extern GameState gameState;

extern unsigned int hres, vres;

void enemy_shoot(Enemy * enemy) {
  enemy->bullet->active = true;
  enemy->isReloading = true;

  enemy->bullet->direction = enemy->direction;

  switch (enemy->bullet->direction) {
    case UP:
      enemy->bullet->x = enemy->x + enemy->img.width - 40;
      enemy->bullet->y = enemy->y - 25;
      break;
    case DOWN:
      enemy->bullet->x = enemy->x;
      enemy->bullet->y = enemy->y + enemy->img.height + 25;
      break;
    case LEFT:
      enemy->bullet->x = enemy->x - 35;
      enemy->bullet->y = enemy->y;
      break;
    case RIGHT:
      enemy->bullet->x = enemy->x + enemy->img.width;
      enemy->bullet->y = enemy->y + enemy->img.height - 25;
      break;     
  }
}

bool bulletAnimation(Bullet * bullet, Enemy ** enemies, unsigned int numEnemies) {
  clean_bullet(bullet);

  switch (bullet->direction) {
    case UP:
      if (!check_collisions_bullet(bullet, enemies, numEnemies)) {
        bullet->y -= bullet->speed;
        draw_bullet(bullet);
        return true;
      }
      break;
    case DOWN:
      if (!check_collisions_bullet(bullet, enemies, numEnemies)) {
        bullet->y += bullet->speed;
        draw_bullet(bullet);
        return true;
      }
      break;
    case LEFT:
      if (!check_collisions_bullet(bullet, enemies, numEnemies)) {
        bullet->x -= bullet->speed;
        draw_bullet(bullet);
        return true;
      }
      break;
    case RIGHT:
      if (!check_collisions_bullet(bullet, enemies, numEnemies)) {
        bullet->x += bullet->speed;
        draw_bullet(bullet);
        return true;
      }
  }

  draw_bullet(bullet);
  return false;
}

void draw_bullet(Bullet * bullet) {
  uint32_t* map = (uint32_t*) bullet->img.bytes;

  for(unsigned int i = 0; i < bullet->img.width; i++) {
    for (unsigned int j = 0; j < bullet->img.height; j++) {
      if (*(map + i + j*bullet->img.width) != 16777215)
        changePixelColor(bullet->x+i,bullet->y+j,*(map + i + j*bullet->img.width));
    }
  }
}

void clean_bullet(Bullet * bullet) {

  for (unsigned int i = bullet->x; i <= bullet->x + bullet->img.width; i++) {
    for (unsigned int j = bullet->y; j <= bullet->y + bullet->img.height; j++) {
      if (i < hres - 1 && j < vres - 1)
        changePixelColor(i,j,*(level->level_back + i + j * hres));
    }
  }
}

bool check_collisions_bullet(Bullet * bullet, Enemy ** enemies, unsigned int numEnemies) {
  switch (bullet->direction) {
    case UP:
      // CHECK COLLISIONS WITH ENEMIES
      for (int i = bullet->x; i <= (int)bullet->x + (int)bullet->img.width; i++) {
        for (int j = bullet->y; j >= (int)bullet->y - (int)bullet->speed; j--) {
          for (unsigned int k = 0; k < numEnemies; k++) {
            if (enemies[k]->dead)
              continue;
            if (i > enemies[k]->x && i < enemies[k]->x + enemies[k]->img.width &&
                j > enemies[k]->y && j < enemies[k]->y + enemies[k]->img.height) {
                  enemy_death(enemies[k]);
                  bullet->active = false;
                  return true;
            }
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
      // CHECK COLLISIONS WITH ENEMIES
      for (int i = bullet->x; i <= (int)bullet->x + (int)bullet->img.width; i++) {
        for (int j = bullet->y + bullet->img.height; j <= (int)bullet->y + (int)bullet->img.height + (int)bullet->speed; j++) {
          for (unsigned int k = 0; k < numEnemies; k++) {
            if (enemies[k]->dead)
              continue;
            if (i > enemies[k]->x && i < enemies[k]->x + enemies[k]->img.width &&
                j > enemies[k]->y && j < enemies[k]->y + enemies[k]->img.height) {
                  enemy_death(enemies[k]);
                  bullet->active = false;
                  return true;
            }
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
      // CHECK COLLISIONS WITH ENEMIES
      for (int i = bullet->x; i >= (int)bullet->x - (int)bullet->speed; i--) {
        for (int j = bullet->y; j <= (int)bullet->y + (int)bullet->img.height; j++) {
          for (unsigned int k = 0; k < numEnemies; k++) {
            if (enemies[k]->dead)
              continue;
            if (i > enemies[k]->x && i < enemies[k]->x + enemies[k]->img.width &&
                j > enemies[k]->y && j < enemies[k]->y + enemies[k]->img.height) {
                  enemy_death(enemies[k]);
                  bullet->active = false;
                  return true;
            }
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
      // CHECK COLLISIONS WITH ENEMIES
      for (int i = bullet->x + bullet->img.width; i <= (int)bullet->x + (int)bullet->speed + bullet->img.width; i++) {
        for (int j = bullet->y; j <= (int)bullet->y + (int)bullet->img.height; j++) {
          for (unsigned int k = 0; k < numEnemies; k++) {
            if (enemies[k]->dead)
              continue;
            if (i > enemies[k]->x && i < enemies[k]->x + enemies[k]->img.width &&
                j > enemies[k]->y && j < enemies[k]->y + enemies[k]->img.height) {
                  enemy_death(enemies[k]);
                  bullet->active = false;
                  return true;
            }
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

