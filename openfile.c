#include <curses.h>
#include <stdlib.h>

FILE *abrir_arquivo(WINDOW*, const char*, const char*);
void ler(WINDOW*, const char*);

int main(void) {

    WINDOW *w_cabecalho;
    WINDOW *w_editor;

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

    wgetch(w_editor);
	
    delwin(w_cabecalho);
    delwin(w_editor);

    endwin();

    return 0;	
}

/*
 * Esta função lê um arquivo.
 * @param janela representa a janela
 * @param nome_do_arquivo representa o nome do arquivo aberto.
 *
*/

void ler(WINDOW* janela, const char* nome_do_arquivo) {
	FILE* file;
	char palavra[255];
	char caractere;

	file = abrir_arquivo(janela, nome_do_arquivo, "r");

	if(file != NULL) {
		caractere = fgetc(file);

		while(!feof(file)) {
			wprintw(janela, "%c", caractere);
			wrefresh(janela);
			caractere = fgetc(file);
		}
	}
}

/*
 * Esta função abre um arquivo.
 * @param janela representa uma janela;
 * @param nome_do_arquivo representa o nome do arquivo;
 * @param modo representa o modo de acesso ao arquivo;
 */

FILE *abrir_arquivo(WINDOW* janela, const char* nome_do_arquivo, const char* modo) {
	FILE* file;

	file = fopen(nome_do_arquivo, modo);

	if(file == NULL) {
		/*
		wprintw(janela, "Desculpe, não foi possível acessar o arquivo '%s'!\n", nome_do_arquivo);
		wrefresh(janela);
		*/
		delwin(janela);
		endwin();
		exit(EXIT_FAILURE);
	}

	return file;
}
