#include "DateTime.h"

DateTime * dateTime;

extern uint8_t rtc_date[3];
extern uint8_t rtc_time[3];

extern unsigned int hres, vres;

extern xpm_image_t background_menu;

extern xpm_image_t clean_background_menu;

DateTime * LoadDateTime() {

  dateTime = (DateTime*) malloc(sizeof(DateTime));

  dateTime->day = 0;
  dateTime->month = 0;
  dateTime->year = 0;
  dateTime->second = 0;
  dateTime->minute = 0;
  dateTime->hour = 0;

  xpm_image_t img;

  xpm_load(zero_xpm, XPM_8_8_8_8, &img);
  dateTime->img[0] = img;
  xpm_load(one_xpm, XPM_8_8_8_8, &img);
  dateTime->img[1] = img;
  xpm_load(two_xpm, XPM_8_8_8_8, &img);
  dateTime->img[2] = img;
  xpm_load(three_xpm, XPM_8_8_8_8, &img);
  dateTime->img[3] = img;
  xpm_load(four_xpm, XPM_8_8_8_8, &img);
  dateTime->img[4] = img;
  xpm_load(five_xpm, XPM_8_8_8_8, &img);
  dateTime->img[5] = img;
  xpm_load(six_xpm, XPM_8_8_8_8, &img);
  dateTime->img[6] = img;
  xpm_load(seven_xpm, XPM_8_8_8_8, &img);
  dateTime->img[7] = img;
  xpm_load(eight_xpm, XPM_8_8_8_8, &img);
  dateTime->img[8] = img;
  xpm_load(nine_xpm, XPM_8_8_8_8, &img);
  dateTime->img[9] = img;
  xpm_load(colon_xpm, XPM_8_8_8_8, &img);
  dateTime->img[10] = img;
  xpm_load(barra_xpm, XPM_8_8_8_8, &img);
  dateTime->img[11] = img;

  return dateTime;
}


xpm_image_t * decide_digit_xpm(unsigned int digit) {
  switch(digit) {
    case 0:
      return &dateTime->img[0];
      break;
    case 1:
      return &dateTime->img[1];
      break;
    case 2:
      return &dateTime->img[2];
      break;
    case 3:
      return &dateTime->img[3];
      break;
    case 4:
      return &dateTime->img[4];
      break;
    case 5:
      return &dateTime->img[5];
      break;
    case 6:
      return &dateTime->img[6];
      break;
    case 7:
      return &dateTime->img[7];
      break;
    case 8:
      return &dateTime->img[8];
      break;
    case 9:
      return &dateTime->img[9];
      break;
    default:
      return &dateTime->img[0];
      break;
  }
}

void draw_digit(xpm_image_t * img, int x, int y) {
  uint32_t * map = (uint32_t *)img->bytes;

  for(int i = 0; i < img->width; i++) {
    for (int j = 0; j < img->height; j++) {
      if (*(map + i + j*img->width) != xpm_transparency_color(XPM_8_8_8_8))
        changePixelColor(x+i,y+j,*(map + i + j*img->width));
    }
  }
}

void add_date_to_background() {
  add_to_background(decide_digit_xpm((uint32_t)dateTime->day/10),50,48);
  add_to_background(decide_digit_xpm((uint32_t)dateTime->day%10),105,48);
  add_to_background(&dateTime->img[11],125,20);
  add_to_background(decide_digit_xpm((uint32_t)dateTime->month/10),175,48);
  add_to_background(decide_digit_xpm((uint32_t)dateTime->month%10),220,48);
  add_to_background(&dateTime->img[11],240,20);
  add_to_background(decide_digit_xpm(2),290,48);
  add_to_background(decide_digit_xpm(0),340,48);
  add_to_background(decide_digit_xpm((uint32_t)dateTime->year/10),390,48);
  add_to_background(decide_digit_xpm((uint32_t)dateTime->year%10),440,48);
}

void add_time_to_background() {
  add_to_background(decide_digit_xpm((uint32_t)dateTime->hour/10),600,48);
  add_to_background(decide_digit_xpm((uint32_t)dateTime->hour%10),650,48);
  add_to_background(&dateTime->img[10],680,24);
  add_to_background(decide_digit_xpm((uint32_t)dateTime->minute/10),730,48);
  add_to_background(decide_digit_xpm((uint32_t)dateTime->minute%10),780,48);
  add_to_background(&dateTime->img[10],810,24);
  add_to_background(decide_digit_xpm((uint32_t)dateTime->second/10),870,48);
  add_to_background(decide_digit_xpm((uint32_t)dateTime->second%10),920,48);
}

void draw_date() {
  
  draw_digit(decide_digit_xpm((uint32_t)dateTime->day/10),50,48);
  draw_digit(decide_digit_xpm((uint32_t)dateTime->day%10),105,48);
  draw_digit(&dateTime->img[11],125,20);
  draw_digit(decide_digit_xpm((uint32_t)dateTime->month/10),175,48);
  draw_digit(decide_digit_xpm((uint32_t)dateTime->month%10),220,48);
  draw_digit(&dateTime->img[11],240,20);
  draw_digit(decide_digit_xpm(2),290,48);
  draw_digit(decide_digit_xpm(0),340,48);
  draw_digit(decide_digit_xpm((uint32_t)dateTime->year/10),390,48);
  draw_digit(decide_digit_xpm((uint32_t)dateTime->year%10),440,48);
  
}

void draw_time() {
  
  draw_digit(decide_digit_xpm((uint32_t)dateTime->hour/10),600,48);
  draw_digit(decide_digit_xpm((uint32_t)dateTime->hour%10),650,48);
  draw_digit(&dateTime->img[10],680,24);
  draw_digit(decide_digit_xpm((uint32_t)dateTime->minute/10),730,48);
  draw_digit(decide_digit_xpm((uint32_t)dateTime->minute%10),780,48);
  draw_digit(&dateTime->img[10],810,24);
  draw_digit(decide_digit_xpm((uint32_t)dateTime->second/10),870,48);
  draw_digit(decide_digit_xpm((uint32_t)dateTime->second%10),920,48);
  
}


void clean_time() {
  clean_digit(decide_digit_xpm((uint32_t)dateTime->hour/10),600,48);
  clean_digit(decide_digit_xpm((uint32_t)dateTime->hour%10),650,48);
  clean_digit(&dateTime->img[10],680,24);
  clean_digit(decide_digit_xpm((uint32_t)dateTime->minute/10),730,48);
  clean_digit(decide_digit_xpm((uint32_t)dateTime->minute%10),780,48);
  clean_digit(&dateTime->img[10],810,24);
  clean_digit(decide_digit_xpm((uint32_t)dateTime->second/10),870,48);
  clean_digit(decide_digit_xpm((uint32_t)dateTime->second%10),920,48);
}

void clean_digit(xpm_image_t * img, int x, int y) {
  uint32_t * map = (uint32_t *)background_menu.bytes;
  uint32_t *cleanMap = (uint32_t *)clean_background_menu.bytes;
  uint32_t *imgMap = (uint32_t *)img->bytes;

  for(int i = 0; i < img->width; i++) {
    for (int j = 0; j < img->height; j++) {
      if (*(imgMap + i + j*img->width) != xpm_transparency_color(XPM_8_8_8_8))
        changePixelColor(x+i,y+j,*(cleanMap + (x + i) + (y + j) * clean_background_menu.width));
    }
  }

  for(int i = 0; i < img->width; i++) {
    for (int j = 0; j < img->height; j++) {
      if (*(imgMap + i + j*img->width) != xpm_transparency_color(XPM_8_8_8_8))
        *(map + (x + i) + (y + j) * hres) = *(cleanMap + x + i + (y + j)*hres);
    }
  }
}


//--------------------------------------------------------------------------------------------------
//--------------------------------------------------------------------------------------------------
//--------------------------------------------------------------------------------------------------

void draw_clock() {
  add_date_to_background();
  draw_date();
  add_time_to_background();
  draw_time();
}

void print_clock() {
  printf("%d:%d:%d\n",rtc_time[2], rtc_time[1], rtc_time[0]);
  printf("%d/%d/20%d\n\n",rtc_date[0], rtc_date[1], rtc_date[2]);
}

void clean_clock() {
  clean_time();
}

void updateDateTime() {
  dateTime->day = rtc_date[0];
  dateTime->month = rtc_date[1];
  dateTime->year = rtc_date[2];
  dateTime->second = rtc_time[0];
  dateTime->minute = rtc_time[1];
  dateTime->hour = rtc_time[2];
}
