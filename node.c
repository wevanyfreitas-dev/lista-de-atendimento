#include <stdlib.h>
#include "interface.h"

No* node_criar(Atendimento a) {
    No *novo = (No*) malloc(sizeof(No));
    if (novo == NULL) {
        return NULL;
    }
    novo->dado = a;
    novo->proximo = NULL;
    return novo;
}

void node_destruir(No *no) {
    if (no != NULL) {
        free(no);
    }
}

