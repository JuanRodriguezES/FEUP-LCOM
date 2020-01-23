#include "Lever.h"

extern unsigned int hres, vres;
extern Level * level;

Lever * createLever(int x, int y) {

  Lever * lever = (Lever *) malloc (sizeof(Lever));

  lever->x = x;
  lever->y = y;
  lever->active = false;

  xpm_image_t img;

  xpm_load(alavanca_fechada_xpm, XPM_8_8_8_8, &img);

  lever->img = img;

  return lever;
}

void draw_lever(Lever * lever) {
  uint32_t * lever_map = (uint32_t *)lever->img.bytes;
  for(int i = 0; i < lever->img.width; i++) {
    for (int j = 0; j < lever->img.height; j++) {
      if (*(lever_map + i + j*lever->img.width) != xpm_transparency_color(XPM_8_8_8_8))
        changePixelColor(lever->x+i,lever->y+j,*(lever_map + i + j*lever->img.width));
    }
  }
}

void clean_lever(Lever * lever) {
  for(int i = 0; i < lever->img.width; i++) {
    for (int j = 0; j < lever->img.height; j++) {
      changePixelColor(lever->x+i,lever->y+j,0x634300);
    }
  }
}

void open_lever(Lever * lever) {

  clean_lever(lever);

  remove_lever_background(lever);

  lever->active = true;

  xpm_image_t img;

  xpm_load(alavanca_aberta_xpm, XPM_8_8_8_8, &img);

  lever->img = img;

  add_lever_background(lever);

  draw_lever(lever);
}


void add_lever_background(Lever * lever) {
  uint32_t * lever_map = (uint32_t *)lever->img.bytes;
  
  for(int i = 0; i < lever->img.width; i++) {
    for (int j = 0; j < lever->img.height; j++) {
      if (*(lever_map + i + j*lever->img.width) != xpm_transparency_color(XPM_8_8_8_8))
        *((uint32_t*)level->level_background.bytes + (lever->x + i) + (lever->y + j) * hres) = *(lever_map + i + j*lever->img.width);
    }
  }
}

void remove_lever_background(Lever * lever) {
  uint32_t * lever_map = (uint32_t *)lever->img.bytes;
  
  for(int i = 0; i < lever->img.width; i++) {
    for (int j = 0; j < lever->img.height; j++) {
      if (*(lever_map + i + j*lever->img.width) != xpm_transparency_color(XPM_8_8_8_8))
        *((uint32_t*)level->level_background.bytes + (lever->x + i) + (lever->y + j) * hres) = 0x634300;
    }
  }
}
