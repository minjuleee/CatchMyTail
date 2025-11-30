#pragma once

#include <windows.h>
#include <mmsystem.h>
#pragma comment(lib,"winmm.lib")

// BGM 상태
extern int bgm_on;
extern int bgm_now;

// BGM 제어 함수
void playBgm(int bgm);
void bgmOnOff();
void stopBgm();

