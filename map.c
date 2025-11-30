#define _CRT_SECURE_NO_WARNINGS
#include <windows.h>
#include <stdio.h>
#include <string.h>

#include "constants.h"

#define TOTAL_ROUNDS 3

int map[HEIGHT][WIDTH];
extern int called[2];

void removeCursor(void) { // 커서를 안보이게 한다

    CONSOLE_CURSOR_INFO curInfo;
    GetConsoleCursorInfo(GetStdHandle(STD_OUTPUT_HANDLE), &curInfo);
    curInfo.bVisible = 0;
    SetConsoleCursorInfo(GetStdHandle(STD_OUTPUT_HANDLE), &curInfo);
}

// 콘솔 창 크기 조절
void ChangeScreenSize(HANDLE hnd, COORD NewSize)
{
    //HANDLE hOut = GetStdHandle(STD_OUTPUT_HANDLE);
    SMALL_RECT DisplayArea = { 0, 0, 0, 0 };
    CONSOLE_SCREEN_BUFFER_INFO SBInfo;
    GetConsoleScreenBufferInfo(hnd, &SBInfo);
    DisplayArea.Bottom = NewSize.Y;
    DisplayArea.Right = NewSize.X;
    SetConsoleWindowInfo(hnd, 1, &DisplayArea);
}

void ChangeBuffSize(HANDLE hnd, COORD NewSize)
{
    SetConsoleScreenBufferSize(hnd, NewSize);
}

void textcolor(int fg_color, int bg_color)
{
    // 현재 실행 중인 표준 콘솔창의 핸들을 가져와서 색상을 적용합니다.
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), fg_color | bg_color << 4);
}

// 화면 지우기고 원하는 배경색으로 설정한다.
void cls(int text_color, int bg_color)
{
    char cmd[100];
    system("cls");
    // 화면 크기 강제로 조정한다.
    sprintf(cmd, "mode con: cols=%d lines=%d", WIDTH * 2, HEIGHT);
    system(cmd);
    sprintf(cmd, "COLOR %x%x", bg_color, text_color);
    system(cmd);
}

void gotoxy(int x, int y) //내가 원하는 위치로 커서 이동
{
    COORD pos = { x, y };
    SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), pos);// WIN32API 함수입니다. 이건 알필요 없어요
}

char heartShape[15][20] = {
               "   XXXX     XXXX   ",
               "  XXXXXX   XXXXXX  ",
               " XXXXXXXX XXXXXXXX ",
               "XXXXXXXXXXXXXXXXXXX",
               "XXXXXXXXXXXXXXXXXXX",
               "XXXXXXXXXXXXXXXXXXX",
               " XXXXXXXXXXXXXXXXX ",
               "  XXXXXXXXXXXXXXX  ",
               "   XXXXXXXXXXXXX   ",
               "    XXXXXXXXXXX    ",
               "     XXXXXXXXX     ",
               "      XXXXXXX      ",
               "       XXXXX       ",
               "        XXX        ",
               "         X         "
};

// 맵 생성
void loadMap(int round) {
    srand((unsigned int)time(NULL));

    int speed_cnt = 3;

    for (int y = 0; y < HEIGHT; y++) {
        for (int x = 0; x < WIDTH; x++) {
            // 테두리는 벽
            if (y == 1 || y == HEIGHT - 1 || x == 0 || x == WIDTH - 1)
                map[y][x] = 1;
            else
                map[y][x] = 0;
        }
    }

    switch (round) {
    case 1:
        called[0] = 0;
        called[1] = 0;
        break;
    case 2:
        playBgm(2);
        called[0] = 0;
        called[1] = 0;

        {
            int cx = WIDTH / 2; 
            int cy = HEIGHT / 2; 
           
            int heartW = 19;
            int heartH = 15;

            // 중심 잡기
            int startX = cx - (heartW / 2);
            int startY = cy - (heartH / 2);

            for (int y = 0; y < heartH; y++) {
                for (int x = 0; x < heartW; x++) {
                    
                    if (heartShape[y][x] == 'X') {
                        int mapY = startY + y;
                        int mapX = startX + x;

                        if (mapY > 0 && mapY < HEIGHT - 1  && mapX > 0 && mapX < WIDTH - 1 ) {
                            map[mapY][mapX] = 1;
                        }
                    }
                }
            }
        }
        
        break;
    case 3:
        playBgm(3);
        called[0] = 0;
        called[1] = 0;
        {

            int heartW = 19;
            int heartH = 15;

            int cy = HEIGHT / 2;    
            int cx = WIDTH / 2;      

            int centerPoints[2] = { cx - 20, cx + 20 };

            for (int i = 0; i < 2; i++) {
                int currentCx = centerPoints[i];
                int startX = currentCx - (heartW / 2);
                int startY = cy - (heartH / 2);

                for (int y = 0; y < heartH; y++) {
                    for (int x = 0; x < heartW; x++) {
                        if (heartShape[y][x] == 'X') {
                            int mapY = startY + y;
                            int mapX = startX + x;

                            if (mapY > 0 && mapY < HEIGHT - 1 && mapX > 0 && mapX < WIDTH - 1) {
                                map[mapY][mapX] = 1;
                            }
                        }
                    }
                }
            }
        }
        break;
    }
}

// 맵
// DrawMap()은 Hidden screen에 그려준다.
void drawMap()
{
    static int i = 0;
    int x, y;
    //scr_clear();
    for (y = 0; y < HEIGHT; y++) {
        for (x = 0; x < WIDTH; x++) {
            if (map[y][x] != 0)
                gotoxy(x * 2, y);
            switch (map[y][x]) {
            case 1: textcolor(BLUE1, WHITE);
                printf("■");
                break;
            }
        }
    }
    //i = i ? 0 : 1; // 별이 깜빡거리게 해 준다.
}

