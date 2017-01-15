#include <stdio.h>
#include <stdlib.h>
#include <curses.h>

#define LARGURA 50
#define ALTURA 20 

int x_inicial = 0;
int y_inicial = 0;

char *escolhas[] = { 
			"CRIAR NOVO ARQUIVO >>",
			"ABRIR NOVO ARQUIVO >>",
			"FECHAR APP >>",
		  };
int n_escolhas = sizeof(escolhas) / sizeof(char *);

void print_menu(WINDOW*, int);
void executar_acao(WINDOW*, int);

void fechar_janela(WINDOW*);
void abrir(WINDOW*);

int main(int argc, char const *argv[]) {
	WINDOW *w_menu;

	int selecionado = 1;
	int escolha = 0;
	int evento;

	initscr();

	noecho();
	curs_set(0);

	x_inicial = (80 - LARGURA) / 2;
	y_inicial = (24 - ALTURA) / 2;
		
	w_menu = newwin(ALTURA, LARGURA, y_inicial, x_inicial);

	start_color(); 

    init_pair(1, COLOR_BLUE, COLOR_BLACK);

    wbkgd(w_menu, COLOR_PAIR(1));

	keypad(w_menu, TRUE);

	print_menu(w_menu, selecionado);

	while(1){

		evento = wgetch(w_menu);

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

		print_menu(w_menu, selecionado);
	}	

	endwin();

	return 0;
}


void print_menu(WINDOW *w_menu, int selecionado)
{
	int x, y, i;	

	x = 15;
	y = 7;

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

void executar_acao(WINDOW* w_menu, int selecionado) {
	switch(selecionado) {
		case 1:
			/*Criar novo arquivo*/
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
 * @param janela represenata uma janela
 *
 */
void fechar_janela(WINDOW* janela) {
	delwin(janela);
	endwin();
	exit(0);
}

/*
 * Esta função abre uma tela para leitura de arquivo
 *
 */
void abrir(WINDOW* janela) {
	char comando[] = "gcc openfile.c -o openfile -lncurses && ./openfile";

	delwin(janela);
	endwin();

	system(comando);

}