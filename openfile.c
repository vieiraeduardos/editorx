#include <stdlib.h> 
#include <curses.h>

#include "header/manipulatefile.h"

int main(void) {

    WINDOW *w_cabecalho; /*Janela de cabeçalho.*/
    WINDOW *w_editor; /*Janela do editor.*/

	int evento; /*Representa o comando escolhido pelo usuário.*/

    char nome_do_arquivo[20]; /*Guarda o nome do arquivo.*/

    initscr(); /*Inicia o ncurses.*/

    raw();

    w_cabecalho = newwin(1, 100, 0, 0); /*Cria uma nova janela.*/
    w_editor = newwin(20, 74, 2, 2); /*Cria uma nova janela.*/
    
    start_color(); /*Habilita o uso de cores.*/

    init_pair(1, COLOR_BLUE, COLOR_BLACK); /*Cria par de cor*/

    wbkgd(stdscr, COLOR_PAIR(1)); /*Define STDSCR com fundo PRETO e texto AZUL.*/
    wbkgd(w_cabecalho, COLOR_PAIR(1)); /*Define W_CABECALHACO com fundo PRETO e texto AZUL.*/
    wbkgd(w_editor, COLOR_PAIR(1)); /*Define W_EDITOR com fundo PRETO e texto AZUL.*/

    mvwprintw(w_cabecalho, 0, 0, "NOME DO ARQUIVO: ");
    wgetstr(w_cabecalho, nome_do_arquivo);
    wrefresh(w_cabecalho);

    scrollok(w_editor, TRUE);

    ler(w_editor, nome_do_arquivo);

	keypad(w_editor, TRUE); /*Habilita o uso de comandos do teclado.*/

	/*Mostra menu até que o usuário faça algo.*/
    while(1) {
		evento = wgetch(w_editor); /*Captura evento no teclado.*/

		switch(evento) {
			case KEY_F(5):
				compilar(nome_do_arquivo);
			break;
		}
	}

    return 0;	
}
