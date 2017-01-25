
struct cursor {
	int x;
	int y;
};

struct lista {
	char caractere;
	struct lista* anterior;
	struct lista* proximo;
};


FILE *abrir_arquivo(const char*, const char*);
void compilar(const char*);
void ler(WINDOW*, const char*);
void criar_arquivo(const char*);
void escrever_no_arquivo(const char*, char*);
void voltar_para_menu_principal(const char*);
void inserir(struct lista*, char);
