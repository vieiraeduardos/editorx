#include <stdlib.h> 
#include <curses.h>

#include "header/manipulatefile.h"

#define ESC 27

int main(void) {

    WINDOW *w_cabecalho; /*Janela de cabeçalho.*/
    WINDOW *w_editor; /*Janela do editor.*/

	int evento; /*Representa o comando escolhido pelo usuário.*/

    char nome_do_arquivo[20]; /*Guarda o nome do arquivo.*/

    initscr(); /*Inicia o ncurses.*/

    raw();

	int largura = 0; /*Guarda a largura da tela.*/
	int altura = 0; /*Guarda a altura da tela.*/
	
	getmaxyx(stdscr, altura, largura); /*Obtem o a largura e altura do terminal*/

    w_cabecalho = newwin(4, largura, 0, 0); /*Cria uma nova janela.*/
    w_editor = newwin(altura - 5, largura - 5, 5, 2); /*Cria uma nova janela.*/

    start_color(); /*Habilita o uso de cores.*/

    init_pair(1, COLOR_WHITE, COLOR_BLACK); /*Cria par de cor*/

    wbkgd(stdscr, COLOR_PAIR(1)); /*Define STDSCR com fundo PRETO e texto AZUL.*/
    wbkgd(w_cabecalho, COLOR_PAIR(1)); /*Define W_CABECALHACO com fundo PRETO e texto AZUL.*/
    wbkgd(w_editor, COLOR_PAIR(1)); /*Define W_EDITOR com fundo PRETO e texto AZUL.*/

	mvwprintw(w_cabecalho, 2, 5, "(F5) COMPILAR");
	mvwprintw(w_cabecalho, 3, 5, "(ESC) VOLTAR");
    wrefresh(w_cabecalho);

    mvwprintw(w_cabecalho, 0, 5, "NOME DO ARQUIVO: ");
    wgetstr(w_cabecalho, nome_do_arquivo);
    wrefresh(w_cabecalho);

    scrollok(w_editor, TRUE);

	keypad(w_editor, TRUE); /*Habilita o uso de comandos do teclado.*/

	/*Mostra menu até que o usuário faça algo.*/
    while(1) {
		mvwprintw(w_cabecalho, 0, 5, "NOME DO ARQUIVO: %s", nome_do_arquivo);
	    wrefresh(w_cabecalho);

		mvwprintw(w_cabecalho, 2, 5, "(F5) COMPILAR");
		mvwprintw(w_cabecalho, 3, 5, "(ESC) VOLTAR");
		wrefresh(w_cabecalho);

		ler(w_editor, nome_do_arquivo);

		noecho();
		evento = wgetch(w_editor); /*Captura evento no teclado.*/
		echo();
		switch(evento) {
			case KEY_F(5):
				compilar(nome_do_arquivo);
			break;

			case ESC:
				voltar_para_menu_principal("");
			break;
		}

		wclear(w_cabecalho); /*Limpa tela.*/
		wclear(w_editor); /*Limpa tela.*/

		getmaxyx(stdscr, altura, largura);		
		wresize(w_cabecalho, 4, largura); /*Redemensiona a tela.*/
		wresize(w_editor, altura - 5, largura - 5); /*Redemensiona a tela.*/		
	}

    return 0;	
}
