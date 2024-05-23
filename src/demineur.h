#ifndef DEMINEUR_H
#define DEMINEUR_H

#include <stdint.h>
#include <sys/time.h> // gettimeofday

#include "constants.h"

#define BOMB_VAL 0xff

typedef enum ACTION { FLAG, REVEAL } ACTION;
typedef enum STATE { HIDDEN, FLAGGED, REVEALED } STATE;

typedef struct cell {
	/*
	 * BOMB_VAL if it's a bomb, 0<=n<9 if there are n bombs around
	 */
	uint8_t value;
	STATE state;
} cell;

typedef struct board {
	cell grid[WIDTH * HEIGHT];
	struct timeval last_update;
	int width;
	int height;
	int nb_bombs;
} board;

typedef struct pos {
	uint8_t x;
	uint8_t y;
} pos;

board *init_board();
int perform_action(board *board, ACTION action, pos pos);
int ended(board *);

#endif
