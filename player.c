#include <stdio.h>
#include <Windows.h>

#include "constants.h"

#define ESC 0x1b

#define SPECIAL1 0xe0 
#define SPECIAL2 0x00 

#define UP  0x48
#define DOWN 0x50
#define LEFT 0x4b
#define RIGHT 0x4d

#define UP2    'w'
#define DOWN2  's'
#define LEFT2  'a'
#define RIGHT2 'd'

#define WIDTH 90
#define HEIGHT 50
#define SNAKE_LENGTH 7
#define SNAKE_LENGTH_MAX 20


extern int heart[2];

COORD snake1[SNAKE_LENGTH_MAX]; // player1
COORD snake2[SNAKE_LENGTH_MAX]; // player2

int snake_len1 = SNAKE_LENGTH;
int snake_len2 = SNAKE_LENGTH;

extern int map[HEIGHT][WIDTH]; 

int frame_count;
int p1_frame_sync = 10, p2_frame_sync = 10;
extern int called[2] = { 0, 0 };


void movesnake(COORD* currentSnake, int len, int x, int y, int isPlayer1)
{
    int i;
    gotoxy(currentSnake[len - 1].X * 2, currentSnake[len - 1].Y);
    printf("  ");
    // 꼬리지우기
    for (i = len - 1; i >= 1; i--) {
        currentSnake[i] = currentSnake[i - 1];
    }
    // 머리 이동
    currentSnake[0].X = x;
    currentSnake[0].Y = y;

    // 다시 그리기
    textcolor(isPlayer1 ? BLUE2 : RED2, WHITE);
    gotoxy(currentSnake[1].X * 2, currentSnake[1].Y); printf(isPlayer1 ? "□" : "■");
    gotoxy(currentSnake[0].X * 2, currentSnake[0].Y); printf(isPlayer1 ? "◈" : "▣");
}

void player1(unsigned char ch) {
    static unsigned char last_ch = RIGHT2; 
    static int oldx = 10, oldy = 10;       
    int newx = oldx, newy = oldy;
    int keep_moving = 1;
    int i;

    if (called[0] == 0) {
        oldx = 10; oldy = 25; // 시작 위치
        for (i = 0; i < snake_len1; i++) {
            snake1[i].X = oldx - i;
            snake1[i].Y = oldy;
            gotoxy(snake1[i].X * 2, snake1[i].Y);
            textcolor(BLUE2, WHITE);
            printf(i == 0 ? "◈" : "□");
        }
        called[0] = 1;
        last_ch = 0;
        ch = 0;
    }

    if (last_ch == ch && frame_count % p1_frame_sync != 0) return;

    if (ch == 0) ch = last_ch;

    if (ch == UP || ch == DOWN || ch == LEFT || ch == RIGHT) {
        ch = last_ch;
    }

    last_ch = ch;
    if (ch == 0) return;

    // 테두리 벽 반사
    switch (ch) {
    case UP2:
        if (oldy > 1) newy = oldy - 1;
        else { last_ch = DOWN2; newy = oldy + 1; } // 벽 반사
        break;
    case DOWN2:
        if (oldy < HEIGHT - 3) newy = oldy + 1;
        else { last_ch = UP2; newy = oldy - 1; }
        break;
    case LEFT2:
        if (oldx > 1) newx = oldx - 1;
        else { last_ch = RIGHT2; newx = oldx + 1; }
        break;
    case RIGHT2:
        if (oldx < WIDTH - 2) newx = oldx + 1;
        else { last_ch = LEFT2; newx = oldx - 1; }
        break;
    }

    // 하트 맵 벽 반사
    if (map[newy+1][newx] == 1) {
        switch (ch) {
        case UP2:
            last_ch = DOWN2;
            newy = oldy + 1; 
            break;
        case DOWN2:
            last_ch = UP2;
            newy = oldy - 1; 
            break;
        case LEFT2:
            last_ch = RIGHT2;
            newx = oldx + 1; 
            break;
        case RIGHT2:
            last_ch = LEFT2;
            newx = oldx - 1; 
            break;
        }

        if (map[newy+1][newx] == 1) {
            newx = oldx;
            newy = oldy;
        }
    }

    movesnake(snake1, snake_len1, newx, newy, 1);

    oldx = newx; 
    oldy = newy;


    // 아이템 충돌
    if (check_heart_hit(newx, newy, 0)) {
        if (p1_frame_sync > 3) p1_frame_sync--;
    }
    check_bomb_hit(newx, newy, 0);

    // 상대 꼬리 닿으면 사망
    for (i = 0; i < snake_len2; i++) {
        if (newx == snake2[i].X && newy == snake2[i].Y) {
            heart[1] = 0; // P2 사망
        }
    }
}


void player2(unsigned char ch) {
    static unsigned char last_ch = LEFT;
    static int oldx = 10, oldy = 10;
    int newx = oldx, newy = oldy;
    int i;

    if (called[1] == 0) {
        oldx = 80; oldy = 25; // P2 시작 위치
        for (i = 0; i < snake_len2; i++) {
            snake2[i].X = oldx + i;
            snake2[i].Y = oldy;
            gotoxy(snake2[i].X * 2, snake2[i].Y);
            textcolor(RED2, WHITE);
            printf(i == 0 ? "▣" : "■");
        }
        called[1] = 1;
        last_ch = 0;
        ch = 0;
    }

    if (last_ch == ch && frame_count % p2_frame_sync != 0) return;
    
    if (ch == 0) ch = last_ch;


    if (ch == UP2 || ch == DOWN2 || ch == LEFT2 || ch == RIGHT2) {
        ch = last_ch;
    }

    last_ch = ch;
    if (ch == 0) return;

    switch (ch) {
    case UP:
        if (oldy > 1) newy = oldy - 1;
        else { last_ch = DOWN; newy = oldy + 1; } // 벽 반사
        break;
    case DOWN:
        if (oldy < HEIGHT - 3) newy = oldy + 1;
        else { last_ch = UP; newy = oldy - 1; }
        break;
    case LEFT:
        if (oldx > 1) newx = oldx - 1;
        else { last_ch = RIGHT; newx = oldx + 1; }
        break;
    case RIGHT:
        if (oldx < WIDTH - 2) newx = oldx + 1;
        else { last_ch = LEFT; newx = oldx - 1; }
        break;
    }

    if (map[newy+1][newx] == 1) {
        switch (ch) {
        case UP:
            last_ch = DOWN;
            newy = oldy + 1;
            break;
        case DOWN:
            last_ch = UP;
            newy = oldy - 1;
            break;
        case LEFT:
            last_ch = RIGHT;
            newx = oldx + 1;
            break;
        case RIGHT:
            last_ch = LEFT;
            newx = oldx - 1;
            break;
        }

        if (map[newy+1][newx] == 1) {
            newx = oldx;
            newy = oldy;
        }
    }

    movesnake(snake2, snake_len2, newx, newy, 0);

    oldx = newx;
    oldy = newy;

    if (check_heart_hit(newx, newy, 1)) {
        if (p2_frame_sync > 3) p2_frame_sync--;
    }
    check_bomb_hit(newx, newy, 1);

    for (i = 0; i < snake_len1; i++) {
        if (newx == snake1[i].X && newy == snake1[i].Y) {
            heart[0] = 0;
        }
    }
}