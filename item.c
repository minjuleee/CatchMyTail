#include "map.h"
#include "constants.h"
#include "item.h"

#define HEART	"♥"
int total_made = 0;	// 지금까지 만든 하트 개수
int limit_cnt = 3;	// 하트 제한
int hearts[WIDTH][HEIGHT] = { 0 }; // 1이면 하트있음
int hearts_count = 0;
int heartinterval = 3;
int heart_frame_sync = 50;
int heart[2] = { 5, 5 }; // 초기 체력

#define BOMB "■"
int bomb_total_made = 0;     
int bomb_limit_cnt = 3;       
int bombs[WIDTH][HEIGHT] = { 0 }; 
int bombs_count = 0;
int bomb_frame_sync = 50;

// 하트 보여줌
void showHeart() {
	if (total_made >= limit_cnt) return;
	int x, y;
	do {
		x = rand() % (WIDTH - 2) + 1;
		y = rand() % (HEIGHT - 2) + 1;
	} while (map[y][x] == 1 || hearts[x][y] == 1 || bombs[x][y] == 1);
	/*x = rand() % (WIDTH - 2) + 1;
	y = rand() % (HEIGHT - 2) + 1;*/
	textcolor(RED2, WHITE);
	gotoxy(x * 2, y);
	printf(HEART);
	hearts[x][y] = 1;
	hearts_count++;
	total_made++;
	textcolor(BLACK, WHITE);
}

void showBomb() {
	if (bomb_total_made >= bomb_limit_cnt) return;
	int x, y;
	do {
		x = rand() % (WIDTH - 2) + 1;
		y = rand() % (HEIGHT - 2) + 1;
	} while (map[y][x] == 1 || hearts[x][y] == 1 || bombs[x][y] == 1);
	/*x = rand() % (WIDTH - 2) + 1;
	y = rand() % (HEIGHT - 2) + 1;*/
	if (bombs[x][y] || hearts[x][y]) return;
	textcolor(BLACK, WHITE);
	gotoxy(x * 2, y);        
	printf(BOMB);
	bombs[x][y] = 1;
	bombs_count++;
	bomb_total_made++;
	textcolor(BLACK, WHITE);
}


// 하트 움직임
void moveHeart() {
	int x, y, dx, dy, newx, newy;
	int newHearts[WIDTH][HEIGHT] = { 0 };
	//static int call_count = 0;

	if (hearts_count == 0) return;
	for (x = 0; x < WIDTH; x++) {
		for (y = 0; y < HEIGHT; y++) {
			if (hearts[x][y]) {
				dx = rand() % 3 - 1;
				dy = rand() % 3 - 1;
				newx = x + dx;
				newy = y + dy;
				// 맵 접근 안됨
				if (newx >= WIDTH - 1) newx = WIDTH - 2;
				if (newx <= 0) newx = 1;
				if (newy >= HEIGHT - 1) newy = HEIGHT - 2;
				if (newy <= 0) newy = 1;

				if (map[newy][newx] == 1 || bombs[newx][newy] == 1) {
					newx = x;
					newy = y;
				}

				gotoxy(x * 2, y);
				textcolor(WHITE, WHITE);
				printf(" "); 
				textcolor(RED2, WHITE);
				gotoxy(newx * 2, newy);
				printf(HEART);
				newHearts[newx][newy] = 1;
				textcolor(BLACK, WHITE);
			}
		}
	}
	memcpy(hearts, newHearts, sizeof(newHearts));
}

void moveBomb() {
	int x, y, dx, dy, newx, newy;
	int newBombs[WIDTH][HEIGHT] = { 0 };
	if (bombs_count == 0) return;
	for (x = 0; x < WIDTH; x++) {
		for (y = 0; y < HEIGHT; y++) {
			if (bombs[x][y]) {
				dx = rand() % 3 - 1;
				dy = rand() % 3 - 1;
				newx = x + dx;
				newy = y + dy;
				if (newx >= WIDTH - 1) newx = WIDTH - 2;
				if (newx <= 0) newx = 1;
				if (newy >= HEIGHT - 2) newy = HEIGHT - 3;
				if (newy <= 0) newy = 1;

				if (map[newy][newx] == 1 || bombs[newx][newy] == 1) {
					newx = x;
					newy = y;
				}
				gotoxy(x * 2, y);
				textcolor(WHITE, WHITE);
				printf("  ");
				textcolor(BLACK, WHITE);
				gotoxy(newx * 2, newy);
				printf(BOMB);
				newBombs[newx][newy] = 1; 
				textcolor(BLACK, WHITE);
			}
		}
	}
	memcpy(bombs, newBombs, sizeof(newBombs));
}
// 하트 먹음 체크
int check_heart_hit(int x, int y, int player) {
	if (hearts[x][y]) {
		hearts[x][y] = 0;
		hearts_count--;
		// 점수/체력 증가 처리
		heart[player]++;
		showHeartScore(player);
		return 1;
	}
	return 0;
}

int check_bomb_hit(int x, int y, int player) {
	if (bombs[x][y]) {
		bombs[x][y] = 0;
		bombs_count--;
		heart[player]--;
		if (heart[player] < 0) heart[player] = 0;
		showHeartScore(player);
		return 1;
	}
	return 0;
}

// 초기화
void resetHeart(int limit) {
	limit_cnt = limit;
	total_made = 0;
	hearts_count = 0;
	memset(hearts, 0, sizeof(hearts));
}

void resetBomb(int limit) {
	bomb_limit_cnt = limit;
	bomb_total_made = 0;
	bombs_count = 0;
	memset(bombs, 0, sizeof(bombs));
}