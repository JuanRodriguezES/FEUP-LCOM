#include "Level.h"

extern unsigned int hres, vres;

Level * level;

Ammo * createAmmo(int x, int y) {
    
  Ammo * ammo = (Ammo *) malloc (sizeof(Ammo));

  ammo->x = x;
  ammo->y = y;

  xpm_image_t img;

  xpm_load(ammo_xpm, XPM_8_8_8_8, &img);

  ammo->img = img;

  return ammo;
}

FinalPos * createFinalPos(int posfinalx, int posfinaly, int lado) {
    
  FinalPos * finalPos = (FinalPos *) malloc (sizeof(FinalPos));

  finalPos->posfinalx = posfinalx;
  finalPos->posfinaly = posfinaly;
  finalPos->lado = lado;

  return finalPos;
}

Level * load_level(unsigned int levelNum) {
  free(level);
  level = (Level *) malloc (sizeof(Level));

  level->levelnum = levelNum;

  switch (levelNum) {
    case 0:
      xpm_load(BackgroundMenu_xpm, XPM_8_8_8_8, &level->level_background);
      xpm_load(ArenaWalls_xpm, XPM_8_8_8_8, &level->level_walls_xpm);
      level->numAmmo = 1;
      level->numDoors = 0;
      level->numLevers = 0;
      level->numEnemies = 0;
      level->ammoList = (Ammo **) malloc (level->numAmmo * sizeof(Ammo *));
      level->ammoList[0] = createAmmo(512,350);
      break;
    case 1:
      xpm_load(Level1_xpm, XPM_8_8_8_8, &level->level_background);
      xpm_load(Level1_Walls_xpm, XPM_8_8_8_8, &level->level_walls_xpm);
      level->finalPos = createFinalPos(832,64,6);
      level->numAmmo = 0;
      level->numDoors = 2;
      level->numLevers = 1;
      level->doorList = (Door **) malloc (level->numDoors * sizeof(Door *));
      level->doorList[0] = createDoor(576,448,DOWN,true);
      level->doorList[1] = createDoor(576,416,UP,true);
      add_door_background(level->doorList[0]);
      add_door_background(level->doorList[1]);
      level->leverList = (Lever **) malloc (level->numLevers * sizeof(Lever *));
      level->leverList[0] = createLever(384,704);
      add_lever_background(level->leverList[0]);
      level->numEnemies = 0;
      break;
    case 2:
      xpm_load(Level2_xpm, XPM_8_8_8_8, &level->level_background);
      xpm_load(Level2_Walls_xpm, XPM_8_8_8_8, &level->level_walls_xpm);
      level->finalPos = createFinalPos(576,320,6);
      level->numAmmo = 2;
      level->numDoors = 0;
      level->numLevers = 0;
      level->numEnemies = 2;
      level->ammoList = (Ammo **) malloc (level->numAmmo * sizeof(Ammo *));
      level->ammoList[0] = createAmmo(512,672);
      level->ammoList[1] = createAmmo(448,64);
      level->enemyList = (Enemy **) malloc (level->numEnemies * sizeof(Enemy *));
      level->enemyList[0] = createEnemy(40,100,DOWN,false);
      level->enemyList[1] = createEnemy(775,50,DOWN,false);
      break;
    case 3:
      xpm_load(Level3_xpm, XPM_8_8_8_8, &level->level_background);
      xpm_load(Level3_Walls_xpm, XPM_8_8_8_8, &level->level_walls_xpm);
      level->finalPos = createFinalPos(88,56,5);
      level->numAmmo = 2;
      level->numDoors = 1;
      level->numLevers = 1;
      level->ammoList = (Ammo **) malloc (level->numAmmo * sizeof(Ammo *));
      level->ammoList[0] = createAmmo(544,704);
      level->ammoList[1] = createAmmo(496,96);
      level->doorList = (Door **) malloc (level->numDoors * sizeof(Door *));
      level->doorList[0] = createDoor(96,160,DOWN,false);
      add_door_background(level->doorList[0]);
      level->leverList = (Lever **) malloc (level->numLevers * sizeof(Lever *));
      level->leverList[0] = createLever(880,32);
      add_lever_background(level->leverList[0]);
      level->numEnemies = 2;
      level->enemyList = (Enemy **) malloc (level->numEnemies * sizeof(Enemy *));
      level->enemyList[0] = createEnemy(96,560,RIGHT,true);
      level->enemyList[1] = createEnemy(848,288,LEFT,true);
      break;
    case 4:
      xpm_load(Level4_xpm, XPM_8_8_8_8, &level->level_background);
      xpm_load(Level4_Walls_xpm, XPM_8_8_8_8, &level->level_walls_xpm);
      level->finalPos = createFinalPos(320,304,6);
      level->numAmmo = 3;
      level->numDoors = 2;
      level->numLevers = 2;
      level->ammoList = (Ammo **) malloc (level->numAmmo * sizeof(Ammo *));
      level->ammoList[0] = createAmmo(192,480);
      level->ammoList[1] = createAmmo(896,128);
      level->ammoList[2] = createAmmo(864,608);
      level->doorList = (Door **) malloc (level->numDoors * sizeof(Door *));
      level->doorList[0] = createDoor(832,544,DOWN,true);
      level->doorList[1] = createDoor(320,416,DOWN,true);
      add_door_background(level->doorList[0]);
      add_door_background(level->doorList[1]);
      level->leverList = (Lever **) malloc (level->numLevers * sizeof(Lever *));
      level->leverList[0] = createLever(64,288);
      level->leverList[1] = createLever(896,288);
      add_lever_background(level->leverList[0]);
      add_lever_background(level->leverList[1]);
      level->numEnemies = 3;
      level->enemyList = (Enemy **) malloc (level->numEnemies * sizeof(Enemy *));
      level->enemyList[0] = createEnemy(50,40,RIGHT,true);
      level->enemyList[1] = createEnemy(905,592,LEFT,true);
      level->enemyList[2] = createEnemy(600,300,RIGHT,false);
      break;
    case 5:
      xpm_load(Level5_xpm, XPM_8_8_8_8, &level->level_background);
      xpm_load(Level5_Walls_xpm, XPM_8_8_8_8, &level->level_walls_xpm);
      level->finalPos = createFinalPos(632,360,5);
      level->numAmmo = 4;
      level->numDoors = 3;
      level->numLevers = 3;
      level->ammoList = (Ammo **) malloc (level->numAmmo * sizeof(Ammo *));
      level->ammoList[0] = createAmmo(288,704);
      level->ammoList[1] = createAmmo(704,64);
      level->ammoList[2] = createAmmo(256,576);
      level->ammoList[3] = createAmmo(256,64);
      level->doorList = (Door **) malloc (level->numDoors * sizeof(Door *));
      level->doorList[0] = createDoor(864,64,RIGHT,false);
      level->doorList[1] = createDoor(480,544,RIGHT,false);
      level->doorList[2] = createDoor(576,352,LEFT,true);
      add_door_background(level->doorList[0]);
      add_door_background(level->doorList[1]);
      add_door_background(level->doorList[2]);
      level->leverList = (Lever **) malloc (level->numLevers * sizeof(Lever *));
      level->leverList[0] = createLever(928,32);
      level->leverList[1] = createLever(576,608);
      level->leverList[2] = createLever(240,160);
      add_lever_background(level->leverList[0]);
      add_lever_background(level->leverList[1]);
      add_lever_background(level->leverList[2]);
      level->numEnemies = 5;
      level->enemyList = (Enemy **) malloc (level->numEnemies * sizeof(Enemy *));
      level->enemyList[0] = createEnemy(912,64,DOWN,true);
      level->enemyList[1] = createEnemy(780,64,DOWN,false);
      level->enemyList[2] = createEnemy(60,40,DOWN,true);
      level->enemyList[3] = createEnemy(368,64,DOWN,false);
      level->enemyList[4] = createEnemy(200,395,RIGHT,true);
      break;
    case 6:
      xpm_load(Level6_xpm, XPM_8_8_8_8, &level->level_background);
      xpm_load(Level6_Walls_xpm, XPM_8_8_8_8, &level->level_walls_xpm);
      level->finalPos = createFinalPos(896,40,5);
      level->numAmmo = 1;
      level->numDoors = 4;
      level->numLevers = 4;
      level->ammoList = (Ammo **) malloc (level->numAmmo * sizeof(Ammo *));
      level->ammoList[0] = createAmmo(144,672);
      level->doorList = (Door **) malloc (level->numDoors * sizeof(Door *));
      level->doorList[0] = createDoor(224,32,LEFT,true);
      level->doorList[1] = createDoor(416,32,LEFT,true);
      level->doorList[2] = createDoor(608,32,LEFT,true);
      level->doorList[3] = createDoor(800,32,LEFT,true);
      add_door_background(level->doorList[0]);
      add_door_background(level->doorList[1]);
      add_door_background(level->doorList[2]);
      add_door_background(level->doorList[3]);
      level->leverList = (Lever **) malloc (level->numLevers * sizeof(Lever *));
      level->leverList[0] = createLever(224,160);
      level->leverList[1] = createLever(416,160);
      level->leverList[2] = createLever(608,160);
      level->leverList[3] = createLever(800,160);
      add_lever_background(level->leverList[0]);
      add_lever_background(level->leverList[1]);
      add_lever_background(level->leverList[2]);
      add_lever_background(level->leverList[3]);
      level->numEnemies = 6;
      level->enemyList = (Enemy **) malloc (level->numEnemies * sizeof(Enemy *));
      level->enemyList[0] = createEnemy(784,208,DOWN,true);
      level->enemyList[1] = createEnemy(592,208,DOWN,false);
      level->enemyList[2] = createEnemy(400,208,DOWN,true);
      level->enemyList[3] = createEnemy(208,208,DOWN,false);
      level->enemyList[4] = createEnemy(48,144,DOWN,true);
      level->enemyList[5] = createEnemy(48,48,RIGHT,false);
      break;
    case 7:
      xpm_load(Level7_xpm, XPM_8_8_8_8, &level->level_background);
      xpm_load(Level7_Walls_xpm, XPM_8_8_8_8, &level->level_walls_xpm);
      level->finalPos = createFinalPos(896,344,5);
      level->numAmmo = 1;
      level->numDoors = 2;
      level->numLevers = 2;
      level->ammoList = (Ammo **) malloc (level->numAmmo * sizeof(Ammo *));
      level->ammoList[0] = createAmmo(96,672);
      level->doorList = (Door **) malloc (level->numDoors * sizeof(Door *));
      level->doorList[0] = createDoor(64,608,UP,true);
      level->doorList[1] = createDoor(832,352,LEFT,true);
      add_door_background(level->doorList[0]);
      add_door_background(level->doorList[1]);
      level->leverList = (Lever **) malloc (level->numLevers * sizeof(Lever *));
      level->leverList[0] = createLever(928,672);
      level->leverList[1] = createLever(928,64);
      add_lever_background(level->leverList[0]);
      add_lever_background(level->leverList[1]);
      level->numEnemies = 5;
      level->enemyList = (Enemy **) malloc (level->numEnemies * sizeof(Enemy *));
      level->enemyList[0] = createEnemy(896,32,LEFT,false);
      level->enemyList[1] = createEnemy(912,160,LEFT,true);
      level->enemyList[2] = createEnemy(912,224,LEFT,true);
      level->enemyList[3] = createEnemy(912,480,LEFT,true);
      level->enemyList[4] = createEnemy(912,544,LEFT,true);
      break;
    case 8:
      xpm_load(Level8_xpm, XPM_8_8_8_8, &level->level_background);
      xpm_load(Level8_Walls_xpm, XPM_8_8_8_8, &level->level_walls_xpm);
      level->finalPos = createFinalPos(64,64,6);
      level->numAmmo = 2;
      level->numDoors = 3;
      level->numLevers = 3;
      level->numEnemies = 6;
      level->ammoList = (Ammo **) malloc (level->numAmmo * sizeof(Ammo *));
      level->ammoList[0] = createAmmo(928,352);
      level->ammoList[1] = createAmmo(64,675);
      level->doorList = (Door **) malloc (level->numDoors * sizeof(Door *));
      level->doorList[0] = createDoor(896,192,UP,true);
      level->doorList[1] = createDoor(896,224,DOWN,true);
      level->doorList[2] = createDoor(352,32,RIGHT,true);
      add_door_background(level->doorList[0]);
      add_door_background(level->doorList[1]);
      add_door_background(level->doorList[2]);
      level->leverList = (Lever **) malloc (level->numLevers * sizeof(Lever *));
      level->leverList[0] = createLever(640,696);
      level->leverList[1] = createLever(352,696);
      level->leverList[2] = createLever(64,710);
      add_lever_background(level->leverList[0]);
      add_lever_background(level->leverList[1]);
      add_lever_background(level->leverList[2]);
      level->enemyList = (Enemy **) malloc (level->numEnemies * sizeof(Enemy *));
      level->enemyList[0] = createEnemy(624,600,UP,true);
      level->enemyList[1] = createEnemy(336,600,UP,true);
      level->enemyList[2] = createEnemy(48,630,UP,true);
      level->enemyList[3] = createEnemy(336,170,DOWN,true);
      level->enemyList[4] = createEnemy(624,170,DOWN,true);
      level->enemyList[5] = createEnemy(480,110,UP,true);
      break;
    case 9:
      xpm_load(Level9_xpm, XPM_8_8_8_8, &level->level_background);
      xpm_load(Level9_Walls_xpm, XPM_8_8_8_8, &level->level_walls_xpm);
      level->finalPos = createFinalPos(864,608,6);
      level->numAmmo = 2;
      level->numDoors = 2;
      level->numLevers = 2;
      level->numEnemies = 8;
      level->ammoList = (Ammo **) malloc (level->numAmmo * sizeof(Ammo *));
      level->ammoList[0] = createAmmo(816,130);
      level->ammoList[1] = createAmmo(432,240);
      level->doorList = (Door **) malloc (level->numDoors * sizeof(Door *));
      level->doorList[0] = createDoor(928,176,DOWN,false);
      level->doorList[1] = createDoor(32,368,DOWN,false);
      add_door_background(level->doorList[0]);
      add_door_background(level->doorList[1]);
      level->leverList = (Lever **) malloc (level->numLevers * sizeof(Lever *));
      level->leverList[0] = createLever(432,130);
      level->leverList[1] = createLever(816,230);
      add_lever_background(level->leverList[0]);
      add_lever_background(level->leverList[1]);
      level->enemyList = (Enemy **) malloc (level->numEnemies * sizeof(Enemy *));
      level->enemyList[0] = createEnemy(912,32,LEFT,true);
      level->enemyList[1] = createEnemy(32,270,RIGHT,true);
      level->enemyList[2] = createEnemy(150,656,UP,true);
      level->enemyList[3] = createEnemy(416,420,DOWN,true);
      level->enemyList[4] = createEnemy(662,656,UP,true);
      level->enemyList[5] = createEnemy(910,416,LEFT,true);
      level->enemyList[6] = createEnemy(910,544,LEFT,true);
      level->enemyList[7] = createEnemy(910,672,LEFT,true);
      break;
    default:
      break;
  }

  level->level_back = (uint32_t*) level->level_background.bytes;

  level->level_walls = (uint32_t*) level->level_walls_xpm.bytes;

  if (levelNum != 0)
    add_final_position_background(&level->finalPos->posfinalx, &level->finalPos->posfinaly, &level->finalPos->lado);


  draw_ammo_level();
  draw_level_background();

  if (levelNum != 0) {
    draw_enemies_level();
  }

  return level;
}

void destroy_level() {

  if (level == NULL)
    return;

  if (level->level_background.bytes)
    free(level->level_background.bytes);

  if (level->level_walls_xpm.bytes)
    free(level->level_walls_xpm.bytes);

  free(level);

  level = NULL; 
}

void draw_level_background() {
  for(unsigned int i = 0; i < level->level_background.width; i++) {
    for (unsigned int j = 0; j < level->level_background.height; j++) {
      changePixelColor(i,j,*(level->level_back + i + j*hres));
    }
  }
}

void draw_ammo_level() {
  unsigned int x, y;

  for (unsigned int k = 0; k < level->numAmmo; k++) {
    x = level->ammoList[k]->x;
    y = level->ammoList[k]->y;
    uint32_t * ammo_map = (uint32_t *)level->ammoList[k]->img.bytes;
    for(int i = 0; i < level->ammoList[k]->img.width; i++) {
      for (int j = 0; j < level->ammoList[k]->img.height; j++) {
        if (*(ammo_map + i + j*level->ammoList[k]->img.width) != xpm_transparency_color(XPM_8_8_8_8))
          *(level->level_back + (x + i) + (y + j) * hres) = *(ammo_map + i + j*level->ammoList[k]->img.width);
      }
    }
  }
}

void draw_enemies_level() {
  for (unsigned int i = 0; i < level->numEnemies; i++)
    draw_enemy(level->enemyList[i]);
}

void draw_levers_level() {
  for (unsigned int i = 0; i < level->numLevers; i++)
    draw_lever(level->leverList[i]);
}

void draw_doors_level() {
  for (unsigned int i = 0; i < level->numDoors; i++)
    draw_door(level->doorList[i]);
}

void clean_picked_ammo(unsigned int x, unsigned int y) {
  for(unsigned int i = x; i < x + 32; i++) {
    for (unsigned int j = y; j < y + 16; j++) {
      changePixelColor(i, j,*(level->level_back + i + j * hres));
    }
  }
}

void clean_ammo_level() {
  for (unsigned int i = 0; i < level->numAmmo; i++) {
    for(unsigned int j = level->ammoList[i]->x; j < level->ammoList[i]->x + 32; j++) {
      for (unsigned int k = level->ammoList[i]->y; k < level->ammoList[i]->y + 16; k++) {
        changePixelColor(j, k,*(level->level_back + j + k * hres));
      }
    }
  }
}

