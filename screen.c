#include <stdio.h>
#include <windows.h>

#include "screen.h"
#include "constants.h"
#include "map.h"
#include "sound.h"
#include "item.h"

const char* asciiArt[] = {
        "      ■■■■■■■     ■■■■■■   ■■■■■■■■■   ■■■■■■■ ■■■    ■■■",
        "     ■■■■■■■■  ■■■■■■■■ ■■■■■■■■■ ■■■■■■■■ ■■■    ■■■",
        "     ■■■            ■■■    ■■■       ■■■       ■■■           ■■■■■■■■",
        "     ■■■            ■■■■■■■■       ■■■       ■■■           ■■■■■■■■",
        "     ■■■■■■■■  ■■■    ■■■       ■■■       ■■■■■■■■ ■■■    ■■■",
        "      ■■■■■■■   ■■■    ■■■       ■■■         ■■■■■■■ ■■■    ■■■",
        "",
        "■■■■      ■■■■ ■■■      ■■■    ■■■■■■■■■   ■■■■■■   ■■■ ■■■     ",
        "■■■■■  ■■■■■ ■■■■  ■■■■    ■■■■■■■■■ ■■■■■■■■ ■■■ ■■■     ",
        "■■■■■■■■■■■   ■■■■■■■            ■■■       ■■■    ■■■ ■■■ ■■■     ",
        "■■■  ■■■  ■■■     ■■■■■              ■■■       ■■■■■■■■ ■■■ ■■■     ",
        "■■■    ■    ■■■       ■■■                ■■■       ■■■    ■■■ ■■■ ■■■■■■■",
        "■■■          ■■■       ■■■                ■■■       ■■■    ■■■ ■■■ ■■■■■■■"
};

const char* asciiArtStart[] = {
" ■■■ ■■■■■  ■■■   ■■■■  ■■■■■        ■■■ ",
"■          ■     ■    ■ ■      ■     ■           ■      ",
"■■■■    ■     ■■■■ ■■■■■     ■   ■■■   ■■■ ",
"       ■   ■     ■    ■ ■   ■        ■                 ■",
"■■■■    ■     ■    ■ ■     ■      ■            ■■■ "
};
const char* asciiArtBgm[] = {
"■■■■  ■■■■   ■      ■          ■■■■",
"■     ■ ■         ■■  ■■          ■    ■",
"■■■■  ■    ■■ ■  ■  ■  ■■■  ■    ■",
"■     ■ ■      ■ ■      ■          ■    ■",
"■■■■  ■■■■■ ■      ■          ■■■■"
};
const char* asciiArtQuit[] = {
    " ■■■  ■  ■ ■ ■■■■■       ■■■ ",
    "■    ■ ■  ■ ■     ■          ■    ■",
    "■    ■ ■  ■ ■     ■  ■■■  ■    ■",
    "■ ■ ■ ■  ■ ■     ■          ■ ■ ■",
    " ■■■   ■■  ■     ■           ■■■ "
};

const char* asciiArtRound1[] = {
    "■■■■■    ■■■■■   ■■   ■■   ■■    ■■   ■■■■■       ■■",
    "■■   ■■  ■■    ■■  ■■   ■■   ■■■  ■■   ■■   ■■    ■■■",
    "■■■■■   ■■    ■■  ■■   ■■   ■■ ■ ■■   ■■   ■■      ■■",
    "■■   ■■  ■■    ■■  ■■   ■■   ■■  ■■■   ■■   ■■      ■■",
    "■■    ■■  ■■■■■    ■■■■■   ■■    ■■   ■■■■■     ■■■■"
};

const char* asciiArtRound2[] = {
"■■■■■    ■■■■■   ■■   ■■   ■■    ■■   ■■■■■     ■■■■■",
"■■   ■■  ■■    ■■  ■■   ■■   ■■■  ■■   ■■   ■■   ■■   ■■",
"■■■■■   ■■    ■■  ■■   ■■   ■■ ■ ■■   ■■   ■■        ■■",
"■■   ■■  ■■    ■■  ■■   ■■   ■■  ■■■   ■■   ■■      ■■",
"■■    ■■  ■■■■■    ■■■■■   ■■    ■■   ■■■■■     ■■■■■"
};

const char* asciiArtRound3[] = {
"■■■■■    ■■■■■   ■■   ■■   ■■    ■■   ■■■■■     ■■■■■",
"■■   ■■  ■■    ■■  ■■   ■■   ■■■  ■■   ■■   ■■           ■■",
"■■■■■   ■■    ■■  ■■   ■■   ■■ ■ ■■   ■■   ■■     ■■■■■",
"■■   ■■  ■■    ■■  ■■   ■■   ■■  ■■■   ■■   ■■           ■■",
"■■    ■■  ■■■■■    ■■■■■   ■■    ■■   ■■■■■     ■■■■■"
};

const char* asciiArtP1Win[] = {
    "■■■■■ ■■       ■■■■■  ■■    ■■  ■■■■■   ■■■■■        ■■     ■■          ■■ ■■■■■ ■■    ■■",
    "■■  ■■ ■■       ■■  ■■  ■■    ■■  ■■         ■■   ■■   ■■■■     ■■          ■■    ■■    ■■■  ■■",
    "■■■■■ ■■       ■■■■■  ■■■■■■  ■■■■■   ■■■■■        ■■     ■■   ■■   ■■    ■■    ■■ ■ ■■",
    "■■       ■■       ■■  ■■      ■■      ■■         ■■  ■■        ■■     ■■   ■■   ■■    ■■    ■■  ■■■",
    "■■       ■■■■■ ■■  ■■      ■■      ■■■■■   ■■   ■■   ■■■■■■    ■■■  ■■■  ■■■■■ ■■    ■■"
};

const char* asciiArtP2Win[] = {
"■■■■■ ■■       ■■■■■  ■■    ■■  ■■■■■   ■■■■■    ■■■■■   ■■         ■■  ■■■■■  ■■    ■■",
"■■  ■■ ■■       ■■  ■■  ■■    ■■  ■■         ■■   ■■         ■■   ■■         ■■     ■■     ■■■  ■■",
"■■■■■ ■■       ■■■■■  ■■■■■■  ■■■■■   ■■■■■    ■■■■■   ■■  ■■   ■■     ■■     ■■ ■ ■■",
"■■       ■■       ■■  ■■      ■■      ■■         ■■  ■■    ■■         ■■  ■■   ■■     ■■     ■■  ■■■",
"■■       ■■■■■ ■■  ■■      ■■      ■■■■■   ■■   ■■   ■■■■■     ■■■  ■■■   ■■■■■  ■■    ■■"
};

const char* asciiArtDraw[] = {
"■■■■    ■■■■■     ■■■     ■■        ■■",
"■■  ■■  ■■   ■■  ■■  ■■   ■■        ■■",
"■■  ■■  ■■■■■   ■■■■■   ■■  ■■  ■■",
"■■  ■■  ■■  ■■   ■■  ■■   ■■  ■■  ■■",
"■■■■    ■■   ■■  ■■  ■■    ■■■  ■■■ "
};

const char* asciiArtFinalResult[] = {
    "■■■■■ ■■  ■■    ■■      ■■      ■■          ■■■■■   ■■■■■   ■■■■■  ■■  ■■  ■■ ■■■■■■■",
    "■■       ■■  ■■■  ■■    ■■■■    ■■          ■■   ■■  ■■         ■■        ■■  ■■  ■■      ■■",
    "■■■■   ■■  ■■ ■ ■■  ■■    ■■  ■■          ■■■■■   ■■■■■      ■■     ■■  ■■  ■■      ■■",
    "■■       ■■  ■■  ■■■  ■■■■■■  ■■          ■■  ■■   ■■              ■■   ■■  ■■  ■■      ■■",
    "■■       ■■  ■■    ■■  ■■    ■■  ■■■■■    ■■   ■■  ■■■■■   ■■■■■  ■■■■■  ■■■■  ■■"
};


// 게임 메인 페이지
void drawMainMenu() {
    playBgm(1);
    cls(WHITE, BLUE1);
    
    int titleLines = sizeof(asciiArt) / sizeof(asciiArt[0]);
    int menuLines = 5; 

    textcolor(WHITE, BLUE1);
    int titleY = 15;

    for (int i = 0; i < titleLines; i++) {

        gotoxy(40, titleY + i);
        printf("%s", asciiArt[i]);
    }

    int menuY = 40;
    int startX = 5; 
    int bgmX = 75;    
    int quitX = 130; 

    
    for (int i = 0; i < menuLines; i++) {

        
        gotoxy(startX, menuY + i);
        printf("%s", asciiArtStart[i]);

       
        gotoxy(bgmX, menuY + i);
        printf("%s", asciiArtBgm[i]);

       
        gotoxy(quitX, menuY + i);
        printf("%s", asciiArtQuit[i]);
    }
    
}

// 게임 상단바 
void showTime(int remain_time) {
    textcolor(BLACK, WHITE);
    gotoxy(85, 0);
    printf("남은시간 : %03d", remain_time);
    textcolor(BLACK, WHITE);
}

int showHeartScore(int player) {
    switch (player){
    case 0: // player 1
        textcolor(BLUE2, WHITE);
        gotoxy(15, 0);
        printf("Player1 : ♥%d", heart[player]); 
        break;
    case 1: // player 2
        textcolor(RED2, WHITE);
        gotoxy(150, 0);
        printf("Player2 : ♥%d", heart[player]);
        break;
    }
    textcolor(BLACK, WHITE);
}


// 라운드 출력
void drawRoundScreen(int round) {
    
    cls(BLACK, WHITE);
    
    const char** artToDraw = NULL;
    int lines = 5;

    switch (round) {
    case 1: artToDraw = asciiArtRound1; break;
    case 2: artToDraw = asciiArtRound2; break;
    case 3: artToDraw = asciiArtRound3; break;
    default: return;
    }

    textcolor(BLUE2, WHITE);

    int startY = 20; 
    int startX = 50; 

    for (int i = 0; i < lines; i++) {
        gotoxy(startX, startY + i);
        printf("%s", artToDraw[i]);
    }

}

// 각 라운드 승패 화면
void drawWinLostScreen(int round, int winner) {
   
    cls(BLACK, WHITE);
 
    const char** roundArt = NULL;
    switch (round) {
    case 1: roundArt = asciiArtRound1; break;
    case 2: roundArt = asciiArtRound2; break;
    case 3: roundArt = asciiArtRound3; break;
    default: roundArt = asciiArtRound1; break;
    }

    textcolor(BLACK, WHITE);
    int startY = 15; 
    int startX = 50; 

    if (roundArt) {
        for (int i = 0; i < 5; i++) {
            textcolor(BLUE2, WHITE);
            gotoxy(startX, startY + i);
            printf("%s", roundArt[i]);
        }
    }

    startY = 22;
    startX = 30;

    const char** winnerArt = NULL;
    if (winner == 1) {
        winnerArt = asciiArtP1Win;
        textcolor(BLUE2, WHITE);
    }
    else if (winner == 2) {
        winnerArt = asciiArtP2Win;
        textcolor(RED2, WHITE); 
    }
    else {
        winnerArt = asciiArtDraw;
        textcolor(BLACK, WHITE); 
        startX = 63;
    }


    if (winnerArt) {
        for (int i = 0; i < 5; i++) {
            gotoxy(startX, startY + i);
            printf("%s", winnerArt[i]);
        }
    }
}

// 최종 라운드 승패 출력
void drawFinalScreen(int winner) {
    
    cls(WHITE, BLUE1);
    playBgm(4);

    textcolor(WHITE, BLUE1);
    int startY = 15;
    int startX = 30; 

    for (int i = 0; i < 5; i++) {
        gotoxy(startX, startY + i);
        printf("%s", asciiArtFinalResult[i]);
    }

    const char** artToDraw = NULL;
    int winnerLines = 5;

    int resultStartY = 22;
    int resultStartX = 28;

    
    if (winner == 1) {
        artToDraw = asciiArtP1Win;
        textcolor(WHITE, BLUE1);
    }
    else if (winner == 2) {
        artToDraw = asciiArtP2Win;
        textcolor(WHITE, BLUE1);
    }
    else {
        artToDraw = asciiArtDraw;
        textcolor(WHITE, BLUE1);
        resultStartX = 63;
    }

    if (artToDraw) {
        for (int i = 0; i < winnerLines; i++) {
            gotoxy(resultStartX, resultStartY + i);
            printf("%s", artToDraw[i]);
        }
    }

    int menuLines = 5;

    int menuY = 40;
    int startX1 = 20;
    int quitX = 110;

    textcolor(WHITE, BLUE1);


    for (int i = 0; i < menuLines; i++) {

        gotoxy(startX1, menuY + i);
        printf("%s", asciiArtStart[i]);

        gotoxy(quitX, menuY + i);
        textcolor(WHITE, BLUE1);
        printf("%s", asciiArtQuit[i]);
    }
}