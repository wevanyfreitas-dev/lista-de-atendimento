#include <stdio.h>
#include <stdlib.h>
#include "interface.h"

struct node {
	Atendimento dado;
	struct node *proximo;
};

Node* node_criar(Atendimento a) {
	Node *novo = (Node*) malloc(sizeof(No));
	if (novo == NULL) {
		return NULL;
	}
	novo->dado = a;
	novo->proximo = NULL;
	return novo;
}

void node_destruir(Node *node) {
	if (node != NULL) {
		free(node);
	}
}
