#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <curses.h>

#include "../header/manipulatefile.h"

/*
 * Esta função compila um arquivo.
 * @param nome_do_arquivo representa o nome de um arquivo para ser compilado;
 *
 */

void compilar(const char* nome_do_arquivo) {
	char comando[] = "gcc compilefile.c -o compilefile && ./compilefile";

	endwin();

	system(comando);
	
	exit(0);	
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
 * Esta função lê um arquivo.
 * @param janela representa a janela
 * @param nome_do_arquivo representa o nome do arquivo aberto.
 *
*/

void ler(WINDOW* janela, const char* nome_do_arquivo) {
	FILE* file;
	char palavra[255];
	char caractere;

	file = abrir_arquivo(nome_do_arquivo, "r");

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

