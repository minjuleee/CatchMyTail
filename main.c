#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <windows.h>
#include <conio.h>

#include "sound.h"
#include "screen.h"
#include "constants.h"

void main() {
    int gameState = STATE_MENU;

    while (1) {
        if (gameState == STATE_MENU) {
            // 메인화면
            drawMainMenu();

            char key = 0;
            while (!_kbhit()) {
                Sleep(10);
            }
            key = _getch();

            // 브금 on/off
            if (key == '0') {
                bgmOnOff();
                continue;
            }

            // 게임 시작
            if (key == 's' || key == 'S') {

                playGame();

                int winner = finalWinner();

                // 최종 화면 그리기
                drawFinalScreen(winner);

                char endKey = 0;
                while (!_kbhit()) Sleep(10);
                endKey = _getch();

                if (endKey == 's' || endKey == 'S') {
                    gameState = STATE_MENU;
                }
                else if (endKey == 'q' || endKey == 'Q') {
                    stopBgm();
                    exit(0);
                }
            }
            else if (key == 'q' || key == 'Q') {
                stopBgm();
                exit(0);
            }
        }
    }
}