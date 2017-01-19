#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void compilar(char*);

int main(int argv, char* argc[]) {
	char nome_do_arquivo[255];

	strncpy(nome_do_arquivo, argc[1], 255);

	compilar(nome_do_arquivo); 

    	return 0;	
}

void compilar(char* nome_do_arquivo) {
	char comando[255];

	sprintf(comando, "gcc %s && ./a.out", nome_do_arquivo);

	system(comando);	
}
