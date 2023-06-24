#pragma once
#include <cmath>
#include <string>
#include <random>

#define SETCOLOR(d, r, g, b) { d[0] = r; d[1] = g; d[2] = b;}
#define RAND0TO1() (rand()/(float)RAND_MAX)

#define ASSET_PATH ".\\Assets\\"
#define WINDOW_WIDTH 1600
#define WINDOW_LEGTH 800
#define CANVAS_WIDTH 1500
#define CANVAS_LEGHT 750

//movies
#define TOTAL_MOVIES 9
#define MOVIES_INIT_POSX 350
#define MOVIES_INIT_POSY CANVAS_LEGHT / 2 - 40
#define MOVIES_ROW_DIFFERENCE 275

#define MOVIES_WIDTH_PERC 21 //percents
#define MOVIES_HEIGHT_PERC 23
#define MOVIES_SPACE_WIDTH_PERC 6.5f
#define MOVIES_SPACE_HEIGHT_PERC 6.5f

#define MOVIES_SPACE_WIDTH (CANVAS_WIDTH *  MOVIES_SPACE_WIDTH_PERC) / 100 //dimensions
#define MOVIES_SPACE_HEIGHT (CANVAS_LEGHT *  MOVIES_SPACE_HEIGHT_PERC) / 100
#define MOVIES_WIDTH (CANVAS_WIDTH * MOVIES_WIDTH_PERC) / 100
#define MOVIES_HEIGHT (CANVAS_LEGHT * MOVIES_HEIGHT_PERC) / 100

//menu items
#define MENU_ITEM_RADIOUS 17.0f
#define MENU_ITEM_TOP_PADDING 90
#define MENU_ITEM_LEFT_MARGIN 30
#define MENU_ITEM_TOP_MARGIN  (CANVAS_LEGHT / 2 + 50)

//Search Genres
#define GENRE_CAT_INT 7

//slider 
#define SLIDER_TOP_MARGIN (CANVAS_LEGHT / 2 + MENU_ITEM_TOP_PADDING) + MENU_ITEM_RADIOUS - 20


inline float distance(float x_center, float y_center, float x_radious, float y_radious) {
	float dx = x_center - x_radious;
	float dy = y_center - y_radious;
	return sqrtf(dx * dx + dy * dy);
};
