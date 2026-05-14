#include "..\library\window.h"

#define WINDOW_SIZE 500
#define MAP_SIZE 500
#define PLAYER_COUNT 3

#define AIR '\0'
#define RED '\1'
#define BLACK '\2'
#define GREEN '\3'

typedef struct {
	int x;
	int y;
	short streakLength;
	short leftToWalk;
	char dir;
} Player;

char map[MAP_SIZE][MAP_SIZE];
Player players[PLAYER_COUNT];

Color pallet[] = {white, {.color = 0xff000080}, red, magenta, cyan};

void mouseEvent(int button, int state, int x, int y) {
	return; // place holder
}

int cos[] = {1, 0, -1, 0};
int sin[] = {0, 1, 0, -1};

#define MOVEMENT_COUNT 8
int movements[MOVEMENT_COUNT][2] = {
	{1, 2}, {2, 1}, {-1, 2}, {-2, 1}, {1, -2}, {2, -1}, {-1, -2}, {-2, -1},
};

bool inline inBounds(int x, int y) {
	return x >= 0 && y >= 0 && x < MAP_SIZE && y < MAP_SIZE;
}

bool invalidPosition(char player, int x, int y) {
	if (inBounds(x, y) && map[x][y] != AIR)
		return true;
	for (int i = 0; i < MOVEMENT_COUNT; i++) {
		if (inBounds(x + movements[i][0], y + movements[i][1]) && map[x + movements[i][0]][y + movements[i][1]] != AIR && map[x + movements[i][0]][y + movements[i][1]] != player + 1) {
			return true;
		}
	}
	return false;
}

/*
int streakLength = 1;
for (int dir = 0; true; dir = (dir + 1) & 3) {
	for (int leftToWalk = streak; leftToWalk > 0; leftToWalk--) {
		walk(1, dir);
	}
	streakLength += dir & 1;
}
*/

void inline tickPlayer(int playerIdx) {
	Player *player = &players[playerIdx];
	while (invalidPosition(playerIdx, player->x, player->y)) {
		if (player->leftToWalk > 0) {
			player->x+=cos[player->dir];
			player->y+=sin[player->dir];
			player->leftToWalk--;
		} else {
			player->streakLength += player->dir & 1;
			player->leftToWalk = player->streakLength;
			player->dir = (player->dir + 1) & 3;
		}
	}
	printf("Done\n");
	fillRect(player->x * WINDOW_SIZE / MAP_SIZE, player->y * WINDOW_SIZE / MAP_SIZE, WINDOW_SIZE / MAP_SIZE, WINDOW_SIZE / MAP_SIZE, pallet[playerIdx + 1]);
	map[player->x][player->y] = playerIdx + 1;
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
	init(argc, argv, "Red and Black Knights", WINDOW_SIZE, WINDOW_SIZE);
}
