#pragma once
#include "map.h"
#define HEART	"¢¾"
extern int hearts[WIDTH][HEIGHT];
extern int hearts_count;
extern int heartinterval;
extern int heart_frame_sync;
extern int heart[2];
extern int bomb_frame_sync;


void showHeart();
void moveHeart();
int check_heart_hit(int x, int y, int player);
void resetHeart(int limit);

void showBomb();                               
void moveBomb();                               
int check_bomb_hit(int x, int y, int player);  
void resetBomb(int limit);
