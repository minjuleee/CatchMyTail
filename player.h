#pragma once
#include <Windows.h>

#define ESC 0x1b

#define SPECIAL1 0xe0 
#define SPECIAL2 0x00 

#define UP    0x48
#define DOWN  0x50
#define LEFT  0x4b
#define RIGHT 0x4d

#define UP2    'w'
#define DOWN2  's'
#define LEFT2  'a'
#define RIGHT2 'd'

#define WIDTH 90
#define HEIGHT 50
#define SNAKE_LENGTH 7
#define SNAKE_LENGTH_MAX 20

extern COORD snake1[SNAKE_LENGTH_MAX];
extern COORD snake2[SNAKE_LENGTH_MAX]; 

extern int snake_len1;
extern int snake_len2;

extern int frame_count;
extern int p1_frame_sync;
extern int p2_frame_sync;
extern int called[2];

void movesnake(COORD* currentSnake, int len, int x, int y, int isPlayer1);
void player1(unsigned char ch);
void player2(unsigned char ch);