#include <stdlib.h> 
#include <curses.h>

#include "header/manipulatefile.h"

#define ESC 27

int main(void) {

    WINDOW *w_cabecalho; /*Janela de cabeçalho.*/
    WINDOW *w_editor; /*Janela do editor.*/

    char nome_do_arquivo[20]; /*Guarda o nome do arquivo.*/
    char conteudo[255]; /*Guarda o conteúdo digitado pelo usuário.*/

	int evento; /*Representa o comando escolhido pelo usuário.*/

    initscr(); /*Inicia o ncurses.*/

    raw();

    int largura = 0; /*Guarda a largura da tela.*/
	int altura = 0; /*Guarda a altura da tela.*/
	
	getmaxyx(stdscr, altura, largura); /*Obtem o a largura e altura do terminal*/

    w_cabecalho = newwin(4, largura, 0, 0); /*Cria uma nova janela.*/
    w_editor = newwin(20, largura - 5, 5, 2); /*Cria uma nova janela.*/

    
    start_color(); /*Habilita o uso de cores.*/

	init_pair(1, COLOR_WHITE, COLOR_BLACK); /*Cria par de cor.*/

    wbkgd(stdscr, COLOR_PAIR(1)); /*Define STDSCR com fundo PRETO e texto AZUL.*/
    wbkgd(w_cabecalho, COLOR_PAIR(1)); /*Define W_CABECALHACO com fundo PRETO e texto AZUL.*/
    wbkgd(w_editor, COLOR_PAIR(1)); /*Define W_EDITOR com fundo PRETO e texto AZUL.*/

    mvwprintw(w_cabecalho, 2, 5, "(F5) COMPILAR");
	mvwprintw(w_cabecalho, 3, 5, "(ESC) VOLTAR");
    wrefresh(w_cabecalho);

    mvwprintw(w_cabecalho, 0, 5, "NOME DO ARQUIVO: ");
    wgetstr(w_cabecalho, nome_do_arquivo);
    wrefresh(w_cabecalho);

    criar_arquivo(nome_do_arquivo); /*Cria um novo arquivo.*/

    keypad(w_editor, TRUE); /*Habilita o uso de comandos do teclado.*/

	/*Mostra menu até que o usuário faça algo.*/
    while(1) {
		mvwprintw(w_cabecalho, 0, 5, "NOME DO ARQUIVO: %s", nome_do_arquivo);
	    wrefresh(w_cabecalho);

		mvwprintw(w_cabecalho, 2, 5, "(F5) COMPILAR");
		mvwprintw(w_cabecalho, 3, 5, "(ESC) VOLTAR");
		wrefresh(w_cabecalho);

		wgetstr(w_editor, conteudo);
		wrefresh(w_editor);

		escrever_no_arquivo(nome_do_arquivo, conteudo);
	
		noecho();
		evento = wgetch(w_editor); /*Captura evento no teclado.*/
		echo();

		switch(evento) {
			case KEY_F(5):
				compilar(nome_do_arquivo);
			break;

			case ESC:
				voltar_para_menu_principal(NULL);
			break;
		}

		wclear(w_cabecalho); /*Limpa tela.*/

		getmaxyx(stdscr, altura, largura);		
		wresize(w_cabecalho, 4, largura); /*Redemensiona a tela.*/
		wresize(w_editor, 20, largura - 5); /*Redemensiona a tela.*/
    }

    return 0;	
}
