#include <curses.h>
#include <stdlib.h>

FILE* abrir_arquivo(const char*, const char*);
void criar_arquivo(const char*);
void escrever_no_arquivo(const char*, char*);

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

/*
 * Esta função abre um arquivo.
 * @param nome_do_arquivo representa o nome do arquivo;
 * @param modo representa o modo de acesso ao arquivo;
 *
 */

FILE *abrir_arquivo(const char* nome_do_arquivo, const char* modo) {
	FILE* file;

	file = fopen(nome_do_arquivo, modo);

	if(file == NULL) {
		/*Mostra mensagem de error*/
	}

	return file;
}

/*
 * Esta função cria um novo arquivo.
 * @param nome_do_arquivo representa o nome do arquivo;
 *
 */

void criar_arquivo(const char* nome_do_arquivo) {
	FILE* file;

	file = abrir_arquivo(nome_do_arquivo, "w");
	
        fclose(file);
}

/*
 * Esta função escreve em um arquivo.
 * @param nome_do_arquivo representa o nome do arquivo;
 * @param conteudo representa o conjunto de caracteres digitados;
 *
 */

void escrever_no_arquivo(const char* nome_do_arquivo, char* conteudo) {
	FILE* file;

	file = abrir_arquivo(nome_do_arquivo, "a");

	fputs(conteudo, file);

	fclose(file);

}
