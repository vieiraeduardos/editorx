#include <stdlib.h> 
#include <curses.h>

#include "header/manipulatefile.h"

int main(void) {

    WINDOW *w_cabecalho;
    WINDOW *w_editor;

    char nome_do_arquivo[20];
    char conteudo[255];

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

    criar_arquivo(nome_do_arquivo);

    while(1) {
	wgetstr(w_editor, conteudo);
	wrefresh(w_editor);

	escrever_no_arquivo(nome_do_arquivo, conteudo);

    }
	
    delwin(w_cabecalho);
    delwin(w_editor);

    endwin();

    return 0;	
}
