#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void compilar(const char*);

int main(int argv, char* argc[]) {
	char nome_do_arquivo[255];

	strncpy(nome_do_arquivo, argc[1], 255);

	compilar(nome_do_arquivo); 

	getchar();

    return 0;	
}

/*
 * Esta função compila um arquivo.
 * @param nome_do_arquivo representa o nome do arquivo a ser aberto;
 *
 */
void compilar(const char* nome_do_arquivo) {
	char comando[255];
	
	system("clear");

	sprintf(comando, "gcc %s && ./a.out", nome_do_arquivo);

	system(comando);	

}
