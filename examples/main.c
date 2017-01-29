#include <curses.h>
#include <stdlib.h>

struct cursor {
	int x;
	int y;
};

struct lista {
	char caractere;
	struct lista* anterior;
	struct lista* proximo;
};

void inserir(struct lista*, char, int);
void salvar(struct lista*);
int retirar(struct lista*, int);

int main(void) {
	/*Inicia estrutura lista*/
	struct lista* lista = NULL;

	lista = (struct lista*)malloc(sizeof(struct lista));

	lista->anterior = NULL;
	lista->proximo = NULL;
	
	tamanho++;	

	/*Inicia estrutura cursor*/
	struct cursor* cursor = NULL;

	cursor = malloc(sizeof(struct cursor));

	cursor->x = 0;
	cursor->y = 0;

	initscr();

	keypad(stdscr, TRUE);

	while (1) {
		wmove(stdscr, cursor->y, cursor->x);
		wrefresh(stdscr);
		int caractere = wgetch(stdscr);

			switch(caractere) {
				case KEY_UP:
					cursor->y--;
					wmove(stdscr, cursor->y, cursor->x);
					wrefresh(stdscr);
					break;
				case KEY_DOWN:
					cursor->y++;
					wmove(stdscr, cursor->y, cursor->x);
					wrefresh(stdscr);
					break;
				case KEY_RIGHT:
					cursor->x++;
					wmove(stdscr, cursor->y, cursor->x);
					wrefresh(stdscr);
					break;
				case KEY_LEFT:
					cursor->x--;
					wmove(stdscr, cursor->y, cursor->x);
					wrefresh(stdscr);
					break;
				case KEY_F(5):
					retirar(lista, (cursor->x + 1) * (cursor->y + 1));
					break;
				case KEY_F(2):
					salvar(lista);
					break;
				case KEY_F(3):
					endwin();
					exit(0);
					break;
				default:
					if((char)caractere == '\n') {
						cursor->y++;
						cursor->x = 0;
					} else {
						cursor->x++;
					}

					inserir(lista, (char)caractere, (cursor->y + 1) * (cursor->x + 1));
		   }
	  }

	return 0;
}


int retirar(struct lista* lista, int posicao) {
	
	if(posicao == 1) {
		if(lista->proximo == NULL) {
			return 0;	
		} else {
			struct lista* tmp = lista->proximo;
			lista->proximo = tmp->proximo;
			tmp->anterior = lista;
		}
		
	} else {
		struct lista* atual = lista->proximo;
		struct lista* anterior = lista;

		int count = 0;

		for(count = 1; count < posicao; count++) {
			anterior = atual;
			atual = atual->proximo;
		}	

		struct lista* aux = atual->proximo;

		anterior->proximo = aux;
		aux->anterior = anterior;
		
	}

	tamanho--;
}

void salvar(struct lista* lista) {
	FILE* file;

	file = fopen("teste.txt", "w");

	struct lista* tmp = NULL;

	for(tmp = lista->proximo; tmp != NULL; tmp = tmp->proximo) {
		putc(tmp->caractere, file);
	}

	fclose(file);
}


void inserir(struct lista* lista, char caractere, int posicao) {
	struct lista* tmp = NULL;

	tmp = (struct lista*)malloc(sizeof(struct lista));

	tmp->caractere = caractere;

	if(posicao == 1) {
		tmp->anterior = lista;
		tmp->proximo = lista->proximo;
		lista->proximo = tmp;
	} else {
		struct lista* atual = lista->proximo;
		struct lista* anterior = lista;

		int count = 0;

		for(count = 1; count < posicao; count++) {
			anterior = atual;
			atual = atual->proximo;
		}	

		anterior->proximo = tmp;
		tmp->proximo = atual;
		tmp->anterior = anterior;
	}

	tamanho++;
}

void imprimir(struct lista* lista) {
	struct lista* tmp = NULL;

	for(tmp = lista->proximo; tmp != NULL; tmp = tmp->proximo) {
		printw("%c", tmp->caractere);
	}
}
