#include <stdlib.h>
#include <stdio.h>
#include <ncurses.h>
#include <locale.h>

#include "demineur.h"
#include "graphic.h"

int main(int argc, char *argv[]) {

	setlocale(LC_CTYPE, "");

	board *board = init_board();
	MEVENT event;

	/* 0) click en haut a gauche de la ou on veut le tableau
	 * 1) selection de la case (souris)
	 * 2) selection de l'action
	 * 	f->flag
	 * 	espace->reveal
	 * 3) execution de l'action
	 * 4) mise a jour de la case modifie
	 */

	initscr(); cbreak(); noecho(); curs_set(0);
	keypad(stdscr, TRUE);

	enable_mouse_tracking();
	mousemask(ALL_MOUSE_EVENTS | REPORT_MOUSE_POSITION, NULL);

	pos topleft;
	int c;
	while((c = getch()) != 'q') {
		switch(c) {
			case KEY_MOUSE:
				if(getmouse(&event) == OK) {
					topleft = (pos) { event.x, event.y };
				}
				affiche(board, topleft);
				break;
			default: break;


		}
	}

	endwin();
	disable_mouse_tracking();
	free(board);

	return EXIT_SUCCESS;
}


