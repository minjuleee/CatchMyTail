#include <windows.h>
#include <stdlib.h>

#include "screen.h"
#include "map.h"
#include "constants.h"
#include "item.h"
#include "player.h"

#define TOTAL_ROUNDS 3
#define ROUND_TIME 60

int roundWinner[TOTAL_ROUNDS]; // 1 = p1승리, 2 = p2승리, 0 = 무승부
int player1Heart = 5;
int player2Heart = 5;


void playRound(int round) {
    // 라운드 시작 화면
    drawRoundScreen(round);
    Sleep(2000);

    //// 맵 초기화
    loadMap(round);
    /*scr_init();*/
    system("cls");
    drawMap();
    removeCursor();

    int start_time = time(NULL);
    int remain_time = ROUND_TIME;
    int last_remain_time = remain_time;
    int frame_count = 0;

    // 플레이어
    player1(0);
    player2(0);

    heart[0] = 5;
    heart[1] = 5;

    resetHeart(1);
    if (round == 1) resetBomb(10);
    else if (round == 2) resetBomb(20);
    else resetBomb(30);

   
    while(1) {

        if (_kbhit()) {
            unsigned char ch = _getch();

            if (ch == 0xE0) {
                ch = _getch();
            }
            player1(ch);
            player2(ch);
            if (ch == 'q' || ch == 27) break;
        }
        player1(0);
        player2(0);

        // 하트 생성 
        if (rand() % 100 < 5) showHeart();
        if (frame_count % heart_frame_sync == 0) moveHeart();

        // 장애물 생성 
        if (rand() % 100 < 5) showBomb();
        if (frame_count % bomb_frame_sync == 0) moveBomb();

        showHeartScore(0);
        showHeartScore(1);
        showTime(remain_time);

        remain_time = ROUND_TIME - (time(NULL) - start_time);
        if (remain_time < 0) break;
        if (remain_time == 0) break;
        if (heart[0] <= 0 || heart[1] <= 0) break;
 
    
        frame_count++;
        Sleep(50);
    }
    
    int winner = 0;
    if (heart[1] <= 0) winner = 1;      
    else if (heart[0] <= 0) winner = 2; 
    else if (heart[0] > heart[1]) winner = 1; 
    else if (heart[1] > heart[0]) winner = 2;
    
    roundWinner[round - 1] = winner;

    drawWinLostScreen(round, roundWinner[round - 1]);

    Sleep(3000);
}

// 게임 시작
void playGame() {

    cls(BLACK, WHITE);
    removeCursor();
    srand((unsigned int)time(NULL));

    for (int round = 1; round <= TOTAL_ROUNDS; round++) {
        playRound(round);
    }

    int winner = finalWinner();
}

// 최종 승자 계산
int finalWinner() {
    int p1Wins = 0, p2Wins = 0;
    for (int i = 0;i < TOTAL_ROUNDS; i++) {
        if (roundWinner[i] == 1) p1Wins++;
        else if (roundWinner[i] == 2) p2Wins++;
    }

    if (p1Wins > p2Wins) return 1;      // p1 win
    else if (p2Wins > p1Wins) return 2; // p2 win
    else return 0;                                  // 무승부
}

