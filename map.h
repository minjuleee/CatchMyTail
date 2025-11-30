#pragma once
#include <windows.h>
  
#define TOTAL_ROUNDS 3 

#define WIDTH 90
#define HEIGHT 50

#define BLOCK_EMPTY 0
#define BLOCK_SPEED 2
#define BLOCK_HEART 3
#define BLOCK_OBSTACLE 4
#define BLOCK_SPECIAL 99

//extern int maps[TOTAL_ROUNDS][HEIGHT][WIDTH]; 
extern int map[HEIGHT][WIDTH];             

void initMaps();   
void cls();
void scr_init();
void cls(int text_color, int bg_color);
void loadMap(int round);
void drawMap(void);

