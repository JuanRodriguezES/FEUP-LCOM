#include "Door.h"

extern unsigned int hres, vres;
extern Level * level;

Door * createDoor(int x, int y, Direction direction, bool longDoor) {
    
  Door * door = (Door *) malloc (sizeof(Door));

  door->x = x;
  door->y = y;
  door->active = true;
  door->direction = direction;
  door->longDoor = longDoor;

  xpm_image_t img;

  //Load move animation
  switch (direction) {
    case UP:
      if (longDoor)
        xpm_load(door_h_3_inv_xpm, XPM_8_8_8_8, &img);
      else
        xpm_load(door_h_2_inv_xpm, XPM_8_8_8_8, &img);
      break;
    case DOWN:
      if (longDoor)
        xpm_load(door_h_3_xpm, XPM_8_8_8_8, &img);
      else
        xpm_load(door_h_2_xpm, XPM_8_8_8_8, &img);
      break;
    case RIGHT:
      if (longDoor)
        xpm_load(door_v_3_xpm, XPM_8_8_8_8, &img);
      else 
        xpm_load(door_v_2_xpm, XPM_8_8_8_8, &img);
      break;
    case LEFT:
      if (longDoor)
        xpm_load(door_v_3_inv_xpm, XPM_8_8_8_8, &img);
      else
        xpm_load(door_v_2_inv_xpm, XPM_8_8_8_8, &img);
      break;
  }

  door->img = img;

  return door;
}

void draw_door(Door * door) {
  uint32_t * doors_map = (uint32_t *)door->img.bytes;

  for(int i = 0; i < door->img.width; i++) {
    for (int j = 0; j < door->img.height; j++) {
      if (*(doors_map + i + j*door->img.width) != xpm_transparency_color(XPM_8_8_8_8))
        changePixelColor(door->x+i,door->y+j,*(doors_map + i + j*door->img.width));
    }
  }
}

void clean_door(Door * door) {
  if (!door->active)
    return;

  for (int i = door->x; i <= door->x + door->img.width; i++) {
    for (int j = door->y; j <= door->y + door->img.height; j++) {
      if (i < (int)hres - 1 && j < (int)vres - 1)
        changePixelColor(i,j,*(level->level_back + i + j * hres));
    }
  }
}

void open_door(Door * door) {
  clean_door(door);
  door->active = false;
}

void add_door_background(Door * door) {
  uint32_t * doors_map = (uint32_t *)door->img.bytes;
  
  for(int i = 0; i < door->img.width; i++) {
    for (int j = 0; j < door->img.height; j++) {
      if (*(doors_map + i + j*door->img.width) != xpm_transparency_color(XPM_8_8_8_8))
        *((uint32_t*)level->level_background.bytes + (door->x + i) + (door->y + j) * hres) = *(doors_map + i + j*door->img.width);
    }
  }

  for(int i = 0; i < door->img.width; i++) {
    for (int j = 0; j < door->img.height; j++) {
      if (*(doors_map + i + j*door->img.width) != xpm_transparency_color(XPM_8_8_8_8))
        *((uint32_t*)level->level_walls_xpm.bytes + (door->x + i) + (door->y + j) * hres) = 0x000000;
    }
  }
}

void remove_door_background(Door * door) {
  uint32_t * doors_map = (uint32_t *)door->img.bytes;
  
  for(int i = 0; i < door->img.width; i++) {
    for (int j = 0; j < door->img.height; j++) {
      if (*(doors_map + i + j*door->img.width) != xpm_transparency_color(XPM_8_8_8_8))
        *((uint32_t*)level->level_background.bytes + (door->x + i) + (door->y + j) * hres) = 0x634300;
    }
  }

  for(int i = 0; i < door->img.width; i++) {
    for (int j = 0; j < door->img.height; j++) {
      if (*(doors_map + i + j*door->img.width) != xpm_transparency_color(XPM_8_8_8_8))
        *((uint32_t*)level->level_walls_xpm.bytes + (door->x + i) + (door->y + j) * hres) = 0xFFFFFF;
    }
  }
}
