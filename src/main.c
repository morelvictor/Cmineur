#include <stdlib.h>
#include <stdio.h>
#include <ncurses.h>
#include <locale.h>

#include "demineur.h"
#include "graphic.h"

pos convert_pos_to_game(pos topleft, pos p) {
	pos tmp = p;
	tmp.x -= topleft.x;
	tmp.y -= topleft.y - 1;
	tmp.x /= 2;
	return tmp;
}

int main(int argc, char *argv[]) {

	setlocale(LC_CTYPE, "");

	board *b = init_board();
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

	pos topleft = (pos) { 0, 0 };
	int c;
	int result = 65;

	c = getch();
	switch(c) {
		case KEY_MOUSE:
			if(getmouse(&event) == OK) {
				topleft = (pos) { event.x, event.y };
			}
			affiche(b, topleft);
			break;
		case 'q': goto end;
		default: break;
	}

	uint8_t selection = 0;
	pos p = { 0, 0 };


	while((c = getch()) != 'q') {
		switch(c) {
			case KEY_MOUSE:
				if(getmouse(&event) == OK) {
					move(event.y, event.x);
					curs_set(2);
					selection = 1;
					p.x = event.x;
					p.y = event.y;
				}
				refresh();
				break;
			case ' ':
				if(selection) {
						pos real = convert_pos_to_game(topleft, p);
						curs_set(0);
						result = perform_action(b, REVEAL, real);
						affiche(b, topleft);
				}
				break;
			case 'f':
				if(selection) {
						pos real = convert_pos_to_game(topleft, p);
						curs_set(0);
						result = perform_action(b, FLAG, real);
						affiche(b, topleft);
				}
				break;
			case 'u': break;
		}

		if(result == 1) {
			break;
		}
	}

end:

	endwin();
	disable_mouse_tracking();
	free(b);

	if(result == 1) {
		printf("T'es trop nul\n");
	} else {
		printf("GGwp\n");
	}

	return EXIT_SUCCESS;
}


