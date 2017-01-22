#include <stdlib.h> 
#include <curses.h>

#include "header/manipulatefile.h"

char *escolhas[] = { 
			"CRIAR NOVO ARQUIVO >>",
			"ABRIR NOVO ARQUIVO >>",
			"FECHAR APP >>",
		  };
int n_escolhas = sizeof(escolhas) / sizeof(char *);

void imprimir_menu(WINDOW*, int);
void executar_acao(WINDOW*, int);
void fechar_janela(WINDOW*);
void abrir(WINDOW*);
void criar(WINDOW*);

int main(int argc, char const *argv[]) {
	WINDOW *w_menu;

	int selecionado = 1; /*Representa a opção selecionada atual do usuário.*/
	int evento; /*Representa o comando escolhido pelo usuário (criar, abrir, fechar, etc).*/

	initscr(); /*Inicia o modo ncurses.*/

	noecho(); /*Desabilita a visualização de caracteres na tela.*/
	curs_set(0); /*Desabilita a visualização do cursor na tela.*/

	int largura = 0; /*Guarda a largura da tela.*/
	int altura = 0; /*Guarda a altura da tela.*/
	
	getmaxyx(stdscr, altura, largura); /*Obtem o a largura e altura do terminal*/

	w_menu = newwin(altura, largura, 0, 0); /*Cria nova janela*/

	start_color(); /*Habilita o uso de cores*/

	init_pair(1, COLOR_WHITE, COLOR_BLACK); /*Cria par de cor.*/

	wbkgd(w_menu, COLOR_PAIR(1)); /*Define o background da janela com texto BRANCO e fundo PRETO.*/

	keypad(w_menu, TRUE); /*Habilita o uso de comandos do teclado.*/
	
	/*Mostra uma mensagem para o usuário*/
	if(argv[1] != NULL) {
		mvwprintw(w_menu, 2, 7, "%s", argv[1]);
		wrefresh(w_menu);
	}

	imprimir_menu(w_menu, selecionado);
	
	/*Mostra menu até que o usuário faça algo.*/
	while(1){
		evento = wgetch(w_menu); /*Captura evento no teclado.*/

		switch(evento) {
			case KEY_UP:
				if(selecionado == 1)
					selecionado = n_escolhas;
				else
					--selecionado;
				break;
			case KEY_DOWN:
				if(selecionado == n_escolhas)
					selecionado = 1;
				else 
					++selecionado;
				break;
			case KEY_RIGHT:
				executar_acao(w_menu, selecionado);
				break;
		}

		wclear(w_menu); /*Limpa a tela.*/
		getmaxyx(stdscr, altura, largura);		
		wresize(w_menu, altura, largura); /*Redemensiona a tela.*/

		imprimir_menu(w_menu, selecionado);
	}	

	return 0;
}

/*
 * Esta função imprime um menu de opções.
 * @param w_menu representa uma janela com as opções para o usuário;
 * @param selecionado representa a opção selecionado do menu;
 *
 */
void imprimir_menu(WINDOW *w_menu, int selecionado)
{
	int x, y, i;	

	getmaxyx(w_menu, y, x);

	x = x * 0.4;
	y = y * 0.4;

	box(w_menu, 0, 0);
	
	for(i = 0; i < n_escolhas; ++i) {
		if(selecionado == i + 1) {
			wattron(w_menu, A_REVERSE); 
			mvwprintw(w_menu, y, x, "%s", escolhas[i]);
			wattroff(w_menu, A_REVERSE);
		} else {
			mvwprintw(w_menu, y, x, "%s", escolhas[i]);
		}
		y += 2;
	}

	wrefresh(w_menu);
}

/*
 * Esta função executar uma ação dependendo da escolha do usuário.
 * @param janela representa a janela principal;
 * @param selecionado representa a opção selecionada do menu;
 *
 */

void executar_acao(WINDOW* w_menu, int selecionado) {
	switch(selecionado) {
		case 1:
			criar(w_menu);
		break;
		case 2:
			abrir(w_menu);
		break;
		case 3:
			fechar_janela(w_menu);
		break;
	}
}

/*
 * Esta função fechar uma janela.
 * @param janela representa a janela principal;
 *
 */
void fechar_janela(WINDOW* janela) {
	delwin(janela);
	endwin();

	system("make clean");

	exit(0);
}

/*
 * Esta função abre uma tela para leitura de arquivo.
 * @param janela representa a janela principal;
 *
 */
void abrir(WINDOW* janela) {
	char comando[] = "make openfile && ./openfile";

	delwin(janela);
	endwin();

	system(comando);
	
	exit(0);
}

/*
 * Esta função cria uma tela para escrita de arquivo.
 * @param janela representa a janela principal;
 *
 */

void criar(WINDOW* janela) {
	char comando[] = "make createfile && ./createfile";

	delwin(janela);
	endwin();

	system(comando);

	exit(0);
}
