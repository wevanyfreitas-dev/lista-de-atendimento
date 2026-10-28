#include <stdio.h>
#include <stdlib.h>
#include "interface.h"

struct fila_p {
	Node *inicio;
	int tam;
};

Fila_P* criar(void){
	Fila_P *f = malloc(sizeof(Fila_P));
	if (f == NULL) return NULL;
	f->inicio = NULL;
	f->tam = 0;
	return f;
}
void destruir(Fila_P *f){
	
};

int remover(Fila_P *f, Atendimento *removido) {
	
};

int inserir(Fila_P *f, Atendimento *a){
	
};

int vazia(const Fila_P *f){
	
};

int tamanho(const Fila_P *f){
	
};

void exibir(const Fila_P *f){
	
};

