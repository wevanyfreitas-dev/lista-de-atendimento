#include <stdio.h>
#include <stdlib.h>
#include "interface.h"

struct fila_p {
	Node *inicio;
	int quantidade;
};

Fila_P* criar(void){
	Fila_P *f = (Fila_P*) malloc(sizeof(Fila_P));
	if (f == NULL) return NULL;
	f->inicio = NULL;
	f->quantidade = 0;
	return f;
};

void destruir(Fila_P *f){
	
};

int inserir(Fila_P *f, Atendimento a){
	
};

int chamar_proximo(Fila_P *f, Atendimento *atendido){
	
};

int cancelar(Fila_P *f, int id){
	
};

int vazia(const Fila_P *f){
	
};

int tamanho(const Fila_P *f){
	
};

void exibir(const Fila_P *f){
	
};

