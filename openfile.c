#include <stdlib.h> 
#include <curses.h>

#include "header/manipulatefile.h"

int main(void) {

    WINDOW *w_cabecalho;
    WINDOW *w_editor;

	int evento;

    char nome_do_arquivo[20];

    initscr(); 

    raw();

    w_cabecalho = newwin(1, 100, 0, 0);
    w_editor = newwin(20, 74, 2, 2);
    
    start_color(); 

    init_pair(1, COLOR_BLUE, COLOR_BLACK);

    wbkgd(stdscr, COLOR_PAIR(1));
    wbkgd(w_cabecalho, COLOR_PAIR(1));
    wbkgd(w_editor, COLOR_PAIR(1));

    mvwprintw(w_cabecalho, 0, 0, "NOME DO ARQUIVO: ");
    wgetstr(w_cabecalho, nome_do_arquivo);
    wrefresh(w_cabecalho);

    scrollok(w_editor, TRUE);

    ler(w_editor, nome_do_arquivo);

	keypad(w_editor, TRUE);

    while(1) {
		evento = wgetch(w_editor);

		switch(evento) {
			case KEY_F(5):
				compilar(nome_do_arquivo);
			break;
		}
	}

    return 0;	
}
