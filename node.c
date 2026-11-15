#include <stdlib.h>
#include "node.h"

struct No {
    Atendimento* dado;
    No* proximo;
};

No* node_criar(Atendimento* a) {
    No *novo = (No*) malloc(sizeof(No));
    if (novo != NULL) {
        novo->dado = a;
        novo->proximo = NULL;
    }
    return novo;
}

void node_destruir(No* no) {
    if (no != NULL) {
        atendimento_destruir(no->dado); // O nó é dono e destrói o atendimento
        free(no);
    }
}

No* node_get_proximo(const No* no) {
    return (no != NULL) ? no->proximo : NULL;
}

void node_set_proximo(No* no, No* proximo) {
    if (no != NULL) no->proximo = proximo;
}

Atendimento* node_get_dado(const No* no) {
    return (no != NULL) ? no->dado : NULL;
}

// Transfere a posse do dado para quem chamou a função
Atendimento* node_liberar_dado(No* no) {
    if (no == NULL) return NULL;
    Atendimento* dado = no->dado;
    no->dado = NULL; // O nó não é mais dono do atendimento
    return dado;
}

