#include <stdlib.h>
#include <stdio.h>
#include <ncurses.h>
#include <locale.h>

#include "demineur.h"

void enable_mouse_tracking() {
    printf("\033[?1003h\n");
    fflush(stdout);
}

void disable_mouse_tracking() {
    printf("\033[?1003l\n");
    fflush(stdout);
}

void affiche(board *b, pos topleft) {
	
}

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

	initscr(); cbreak(); noecho();

	enable_mouse_tracking();
	mousemask(ALL_MOUSE_EVENTS | REPORT_MOUSE_POSITION, NULL);
	
	getch();

	endwin();
	disable_mouse_tracking();
	free(board);

	return EXIT_SUCCESS;
}


