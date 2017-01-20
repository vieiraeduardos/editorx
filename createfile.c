#include <stdlib.h> 
#include <curses.h>

#include "header/manipulatefile.h"

int main(void) {

    WINDOW *w_cabecalho; /*Janela de cabeçalho.*/
    WINDOW *w_editor; /*Janela do editor.*/

    char nome_do_arquivo[20]; /*Guarda o nome do arquivo.*/
    char conteudo[255]; /*Guarda o conteúdo digitado pelo usuário.*/

	int evento; /*Representa o comando escolhido pelo usuário.*/

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

    criar_arquivo(nome_do_arquivo); /*Cria um novo arquivo.*/

    keypad(w_editor, TRUE); /*Habilita o uso de comandos do teclado.*/

	/*Mostra menu até que o usuário faça algo.*/
    while(1) {
		wgetstr(w_editor, conteudo);
		wrefresh(w_editor);

		escrever_no_arquivo(nome_do_arquivo, conteudo);
	
		evento = wgetch(w_editor); /*Captura evento no teclado.*/

		switch(evento) {
			case KEY_F(5):
				compilar(nome_do_arquivo);
			break;
		}
    }

    return 0;	
}
