#include "demineur.h"

#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <stdio.h>

void swap(cell *a, cell *b) {
	cell temp = *a;
	*a = *b;
	*b = temp;
}

void shuffle_array(cell *array, size_t size) {
	srand(time(NULL));
	for (size_t i = size - 1; i > 0; --i) {
		size_t j = rand() % (i + 1);
		swap(&array[i], &array[j]);
	}
}

int is_valid_pos(board *b, pos p) {
	return 0 <= p.x &&
		p.x < b->width &&
		0 <= p.y &&
		p.y < b->height;
}

cell *get(board *b, pos p) {
	if(!is_valid_pos(b, p)) {
		return NULL;
	}
	return &b->grid[p.x + p.y * b->width];
}

int bomb_around(board *b, pos p) {
	if(!is_valid_pos(b, p)) {
		return -1;
	}
	int k = 0;
	for(int i = -1; i <= 1; i++) {
		for(int j = -1; j <= 1; j++) {
			pos curr = {p.x + i, p.y + j};
			if(is_valid_pos(b, curr)) {
				cell *curr_cell = get(b, curr);
				if(curr_cell->value == BOMB_VAL) {
					k++;
				}
			}
		}
	}
	return k;
};

board *init_board() {
	board *b = malloc(sizeof(board));
	b->width = WIDTH;
	b->height = HEIGHT;
	b->nb_bombs = NB_BOMBS;
	cell dfl_cell = { .value = 0, .state = HIDDEN };
	for(int i = 0; i < b->width * b->height; i++) {
		b->grid[i] = dfl_cell;
	}

	for(int i = 0; i < b->nb_bombs; i++) {
		b->grid[i].value = BOMB_VAL;
	}

	shuffle_array(b->grid, b->width * b->height);

	for(int i = 0; i < b->width * b->height; i++) {
		pos curr_pos = { i % b->width, i / b->width };
		if(b->grid[i].value != BOMB_VAL) {
			b->grid[i].value = bomb_around(b, curr_pos);
		}
	}

	return b;
}

/*
 * @return -1 if an error occured
 * @return 0 if no problem
 * @return 1 if you lose
 * @return 2 if nothing
 */
int perform_action(board *b, ACTION a, pos p) {
	if(!is_valid_pos(b, p)) {
		return -1;
	}

	cell *curr = &b->grid[p.x + p.y * b->width];

	switch(a) {
		case FLAG:

			curr->state = curr->state == FLAGGED ? HIDDEN : FLAGGED;
			break;
		case REVEAL:
			if(curr->state == REVEALED) {
				break;
			}
			if(curr->value == BOMB_VAL) {
				return 1;
			}
			if(curr->value == 0) {
				fprintf(stderr, "yo");
				for(int i = -1; i <= 1; i++) {
					for(int j = -1; j <= 1; j++) {
						if(i == 0 && j == 0) {
							continue;
						}
						pos curr_pos = {p.x + i, p.y + j};
						if(is_valid_pos(b, curr_pos)) {
							curr->state = REVEALED;
							perform_action(b, a, curr_pos);
						}
					}
				}
			}
			curr->state = REVEALED;
			break;
		default:
			return -1;
	}
	return 0;
}


/*
 * @return 0 if not winning
 * @return 1 if winning
 * @return 2 if lost
 * @return -1 if an error occured
 */
int is_winning(board *b) {
	for(int i = 0; i < b->width * b-> height; i++) {
		cell curr = b->grid[i];
		switch(curr.state) {
			case FLAGGED:
				if(curr.value != BOMB_VAL) {
					return 0;
				}
				break;
			case REVEALED:
				if(curr.value > 8) {
					return 2;
				}
			case HIDDEN:
				return 0;
			default:
				return -1;
		}
	}
	return 1;
}

wchar_t *char_cell(cell c) {
	switch(c.state) {
		case FLAGGED: return L"F";
		case HIDDEN: return L"#";
		case REVEALED:
			     {wchar_t *wc = malloc(2 * sizeof(wchar_t));
				     wc[0] = (c.value % 9) + L'0';
				     wc[1] = 0;
				     return wc;}
		default: return 0;
	}
}

