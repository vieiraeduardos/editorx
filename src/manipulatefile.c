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
	char comando[255];

	sprintf(comando, "gcc compilefile.c -o compilefile && ./compilefile '%s'", nome_do_arquivo);

	endwin();

	system(comando);
		
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
		char mensagem[255];
		
     	sprintf(mensagem, "O arquivo \"%s\" nao foi encontrado!", nome_do_arquivo);
		voltar_para_menu_principal(mensagem);
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
	char caminho[255];

	sprintf(caminho, "%s", nome_do_arquivo);

	file = abrir_arquivo(caminho, "w");
	
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

	fprintf(file, "%s\n", conteudo);

	fclose(file);

}

/*
 * Esta função faz retornarmos para o menu principal.
 * @param mensagem representa uma mensagem para ser mostrada;
 *
 */

void voltar_para_menu_principal(const char* mensagem) {
		char comando[255];

		sprintf(comando, "make main && ./main '%s'", mensagem);

		endwin();

		system(comando);
	
		exit(0);
}

/**
  * Esta função insere um caractere na lista.
  * @param lista representa uma lista de caracteres;
  * @param caractere representa o caractere;
  * 
  **/


void inserir(struct lista* lista, char caractere) {
	struct lista* tmp = NULL;

	tmp = (struct lista*)malloc(sizeof(struct lista));

	tmp->caractere = caractere;
	tmp->proximo = NULL;

	if(lista->proximo == NULL) {
		tmp->anterior = lista;
		lista->proximo = tmp;
	} else {
		struct lista* aux = lista->proximo;

		while(aux->proximo != NULL) {
			aux = aux->proximo;
		}

		tmp->anterior = aux;
		aux->proximo = tmp;

	}
}

