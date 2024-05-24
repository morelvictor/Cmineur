#include "graphic.h"

#include <ncurses.h>

void enable_mouse_tracking() {
    printf("\033[?1003h\n");
    fflush(stdout);
}

void disable_mouse_tracking() {
    printf("\033[?1003l\n");
    fflush(stdout);
}

void affiche(board *b, pos topleft) {
	clear();
	move((int) topleft.y, (int) topleft.x);
	for(int y = 0; y < b->height; y++) {
		for(int x = 0; x < b->width; x++) {
			cchar_t cc;
			wchar_t *c = char_cell(b->grid[x+y*b->width]);
			setcchar(&cc, c, A_NORMAL, 0, NULL);
			add_wch(&cc);
			addch(' ');
		}
		move((int) topleft.y + y, (int) topleft.x);
	}
	refresh();
}

