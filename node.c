#include <stdio.h>
#include <stdlib.h>
#include "interface.h"


struct atendimento {
	int id;
	char nome[30];
	int prioridade;
};

struct node {
	Atendimento dado;
	struct node *proximo;
};

Node *criar_node(Atendimento dado) {
	Node *novo = malloc(sizeof(Node));
	if (novo == NULL) {
		return NULL;
	}

	novo->dado = dado;
	novo->proximo = NULL;
	return novo;
}

void destruir_node(Node *n) {
	if (n != NULL) {
		free(n);
	}
}
