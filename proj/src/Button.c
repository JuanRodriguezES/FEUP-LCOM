#include "Button.h"

extern xpm_image_t background_menu;
extern unsigned int hres, vres;

Button * createButton(ButtonType buttonType, unsigned int x, unsigned int y) {
  Button * button = (Button *) malloc (sizeof(Button));

  button->x = x;
  button->y = y;
  button->mouseOver = false;
  button->buttonType = buttonType;

  switch (buttonType) {
    case BUTTON_EXIT:
      xpm_load(Exit_xpm, XPM_8_8_8_8, &button->buttonImg);
      xpm_load(ExitClicked_xpm, XPM_8_8_8_8, &button->highlightedImg);
      break;
    case BUTTON_CONTINUE:
      xpm_load(Continue_xpm, XPM_8_8_8_8, &button->buttonImg);
      xpm_load(ContinueClicked_xpm, XPM_8_8_8_8, &button->highlightedImg);
      break;
    case BUTTON_SINGLEPLAYER:
      xpm_load(Single_Player_xpm, XPM_8_8_8_8, &button->buttonImg);
      xpm_load(Single_PlayerClicked_xpm, XPM_8_8_8_8, &button->highlightedImg);
      break;
    case BUTTON_MULTIPLAYER:
      xpm_load(Multi_Player_xpm, XPM_8_8_8_8, &button->buttonImg);
      xpm_load(Multi_PlayerClicked_xpm, XPM_8_8_8_8, &button->highlightedImg);
      break;
    case BUTTON_HELP:
      xpm_load(HelpButton_xpm, XPM_8_8_8_8, &button->buttonImg);
      xpm_load(HelpClicked_xpm, XPM_8_8_8_8, &button->highlightedImg);
      break;
  }

  return button;
}

void draw_button(Button * button) {
  uint32_t * map;
  if (!button->mouseOver) {
    map = (uint32_t *)button->buttonImg.bytes;

    for(int i = 0; i < button->buttonImg.width; i++) {
      for (int j = 0; j < button->buttonImg.height; j++) {
        if (*(map + i + j*button->buttonImg.width) != xpm_transparency_color(XPM_8_8_8_8))
          changePixelColor(button->x+i,button->y+j,*(map + i + j*button->buttonImg.width));
      }
    }
  }
  else {
    map = (uint32_t *)button->highlightedImg.bytes;

    for(int i = 0; i < button->highlightedImg.width; i++) {
      for (int j = 0; j < button->highlightedImg.height; j++) {
        if (*(map + i + j*button->highlightedImg.width) != xpm_transparency_color(XPM_8_8_8_8))
          changePixelColor(button->x+i,button->y+j,*(map + i + j*button->highlightedImg.width));
      }
    }
  }
}

void add_button_to_background(Button * button) {
  uint32_t * map, * buttonMap;

  map = (uint32_t *)background_menu.bytes;

  if (!button->mouseOver) {
    buttonMap = (uint32_t *)button->buttonImg.bytes;

    for(int i = 0; i < button->buttonImg.width; i++) {
      for (int j = 0; j < button->buttonImg.height; j++) {
        if (*(buttonMap + i + j*button->buttonImg.width) != xpm_transparency_color(XPM_8_8_8_8))
          *(map + (button->x + i) + (button->y + j) * hres) = *(buttonMap + i + j*button->buttonImg.width);
      }
    }
  }
  else {
    buttonMap = (uint32_t *)button->highlightedImg.bytes;

    for(int i = 0; i < button->highlightedImg.width; i++) {
      for (int j = 0; j < button->highlightedImg.height; j++) {
        if (*(buttonMap + i + j*button->highlightedImg.width) != xpm_transparency_color(XPM_8_8_8_8))
          *(map + (button->x + i) + (button->y + j) * hres) = *(buttonMap + i + j*button->buttonImg.width);
      }
    }
  }
}
