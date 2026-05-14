#include "window.h"

#define WINDOW_SIZE 500
#define MAP_SIZE 500
#define PLAYER_COUNT 2

#define AIR '\0'

typedef struct {
	int x;
	int y;
	short streakLength;
	short leftToWalk;
	char dir;
} Player;

char map[MAP_SIZE][MAP_SIZE];
Player players[PLAYER_COUNT];

Color pallet[] = {white, black, red};

void mouseEvent(int button, int state, int x, int y) {
	return; // place holder
}

int cossine[] = {1, 0, -1, 0};
int sine[] = {0, 1, 0, -1};

#define KNIGHT {{1, 2}, {2, 1}, {-1, 2}, {-2, 1}, {1, -2}, {2, -1}, {-1, -2}, {-2, -1}}
#define ZEBRA {{3, 2}, {2, 3}, {-3, 2}, {-2, 3}, {3, -2}, {2, -3}, {-3, -2}, {-2, -3}}
#define ANTELOPE {{3, 4}, {4, 3}, {-3, 4}, {-4, 3}, {3, -4}, {4, -3}, {-3, -4}, {-4, -3}}
#define WAZIR {{1, 0}, {0, 1}, {-1, 0}, {0, -1}, {0, 0}, {0, 0}, {0, 0}, {0, 0}}
#define FERZ {{1, 1}, {1, -1}, {-1, 1}, {-1, -1}, {0, 0}, {0, 0}, {0, 0}, {0, 0}}
#define PEACE {{0, 0}, {0, 0}, {0, 0}, {0, 0}, {0, 0}, {0, 0}, {0, 0}, {0, 0}}
#define MOVEMENT_COUNT 8
int movements[PLAYER_COUNT][MOVEMENT_COUNT][2] = {KNIGHT, KNIGHT};

bool inline inBounds(int x, int y) {
	return x >= 0 && y >= 0 && x < MAP_SIZE && y < MAP_SIZE;
}

void inline tickPlayer(int playerIdx) {
	Player *player = &players[playerIdx];
	while (inBounds(player->x, player->y) && (map[player->x][player->y] & ~(1 << playerIdx))) {
		if (player->leftToWalk > 0) {
			player->x+=cossine[player->dir];
			player->y+=sine[player->dir];
			player->leftToWalk--;
		} else {
			player->streakLength += player->dir & 1;
			player->leftToWalk = player->streakLength;
			player->dir = (player->dir + 1) & 3;
		}
	}
	fillRect(player->x * WINDOW_SIZE / MAP_SIZE, player->y * WINDOW_SIZE / MAP_SIZE, WINDOW_SIZE / MAP_SIZE, WINDOW_SIZE / MAP_SIZE, pallet[playerIdx + 1]);
	map[player->x][player->y] |= 1 << playerIdx;
	for (int i = 0; i < MOVEMENT_COUNT; i++) {
		if (!inBounds(player->x + movements[playerIdx][i][0],player->y + movements[playerIdx][i][1])) {
			return;
		}
		map[player->x + movements[playerIdx][i][0]][player->y + movements[playerIdx][i][1]] |= 1 << playerIdx;
	}
	if (player->leftToWalk <= 0) {
		player->streakLength += player->dir & 1;
		player->leftToWalk = player->streakLength;
		player->dir = (player->dir + 1) & 3;
	} 
	player->x+=cossine[player->dir];
	player->y+=sine[player->dir]; // you always walk after turning
	player->leftToWalk--;
}

int frame = 0;
void loop() {
	if(frame++ == 0) {
		fillRect(0, 0, WINDOW_SIZE, WINDOW_SIZE, pallet[0]);
	}
	//for (int repetition = 0; repetition < 10; repetition++)
	for (int i = 0; i < PLAYER_COUNT; i++) {
		tickPlayer(i);
	}
}

int main(int argc, char** argv) {
	for (int i = 0; i < PLAYER_COUNT; i++) {
		players[i].x = WINDOW_SIZE >> 1;
		players[i].y = WINDOW_SIZE >> 1;
		players[i].streakLength = 1;
		players[i].leftToWalk = 1;
		players[i].dir = '\0';
	}
	map[WINDOW_SIZE >> 1][WINDOW_SIZE >> 1] = 1;
	init(argc, argv, "Red and Black Knights", WINDOW_SIZE, WINDOW_SIZE);
}
