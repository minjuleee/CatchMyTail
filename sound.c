#include "sound.h"

int bgm_on = 1;
int bgm_now = 1;

void stopBgm() {
    PlaySound(NULL, 0, 0);
}

void playBgm(int bgm) {
    if (!bgm_on) {
        stopBgm();
        return;
    }

    bgm_now = bgm;

    switch (bgm) {
    case 1:
        PlaySound(TEXT("bgm1.wav"), NULL, SND_FILENAME | SND_LOOP | SND_ASYNC);
        break;
    case 2:
        PlaySound(TEXT("bgm2.wav"), NULL, SND_FILENAME | SND_LOOP | SND_ASYNC);
        break;
    case 3:
        PlaySound(TEXT("bgm3.wav"), NULL, SND_FILENAME | SND_LOOP | SND_ASYNC);
        break;
    case 4:
        PlaySound(TEXT("bgm4.wav"), NULL, SND_FILENAME | SND_LOOP | SND_ASYNC);
        break;
    default:
        stopBgm();
        break;
    }
}


void bgmOnOff() {
    bgm_on = !bgm_on;
    if (bgm_on)
        playBgm(bgm_now);
    else
        stopBgm();
}
