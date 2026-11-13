#include <stdio.h>
#include <stdlib.h>
#include "interface.h"

struct fila_prioridade {
    No *inicio;
    int quantidade;
};

FilaPrioridade* fila_criar(void) {
    FilaPrioridade f = (FilaPrioridade) malloc(sizeof(FilaPrioridade));
    if (f == NULL) return NULL;
    f->inicio = NULL;
    f->quantidade = 0;
    return f;
}

void fila_destruir(FilaPrioridade *f) {
    if (f == NULL) return;

    No *atual = f->inicio;
    while (atual != NULL) {
        No *temp = atual->proximo;
        node_destruir(atual);
        atual = temp;
    }
    free(f);
}

int fila_inserir(FilaPrioridade *f, Atendimento a) {
    if (f == NULL) return 0;

    No *novo = node_criar(a);
    if (novo == NULL) return 0;

    if (f->inicio == NULL || a.prioridade > f->inicio->dado.prioridade) {
        novo->proximo = f->inicio;
        f->inicio = novo;
    } else {
        No *atual = f->inicio;
        while (atual->proximo != NULL && atual->proximo->dado.prioridade >= a.prioridade) {
            atual = atual->proximo;
        }
        novo->proximo = atual->proximo;
        atual->proximo = novo;
    }

    f->quantidade++;
    return 1;
}

int fila_chamar_proximo(FilaPrioridade *f, Atendimento *atendido) {
    if (f == NULL || f->inicio == NULL) return 0;

    No *removido = f->inicio;
    if (atendido != NULL) {
        *atendido = removido->dado;
    }

    f->inicio = removido->proximo;
    node_destruir(removido);
    f->quantidade--;

    No *aux = f->inicio;
    while (aux != NULL) {
        aux->dado.contador_espera++;
        aux = aux->proximo;
    }

    return 1;
}

int fila_cancelar(FilaPrioridade *f, int id) {
    if (f == NULL || f->inicio == NULL) return 0;

    No *atual = f->inicio;
    No *anterior = NULL;

    while (atual != NULL && atual->dado.id != id) {
        anterior = atual;
        atual = atual->proximo;
    }

    if (atual == NULL) return 0;

    if (anterior == NULL) {
        f->inicio = atual->proximo;
    } else {
        anterior->proximo = atual->proximo;
    }

    node_destruir(atual);
    f->quantidade--;
    return 1;
}

int fila_vazia(const FilaPrioridade *f) {
    return (f == NULL || f->inicio == NULL);
}

int fila_tamanho(const FilaPrioridade *f) {
    return (f != NULL) ? f->quantidade : 0;
}

void fila_exibir(const FilaPrioridade *f) {
    if (f == NULL || f->inicio == NULL) {
        printf("\n[STATUS] A fila de espera esta vazia.\n");
        return;
    }

    printf("\n================ FILA DE ESPERA (%d PESSOAS) ================\n", f->quantidade);
    No *atual = f->inicio;
    int pos = 1;
    while (atual != NULL) {
        printf("%2d. ", pos++);
        atendimento_exibir(atual->dado);
        atual = atual->proximo;
    }
    printf("===========================================================\n");
}

int fila_aplicar_antistarvation(FilaPrioridade *f, int limite_espera) {
    if (f == NULL || f->inicio == NULL) return 0;

    int promovidos = 0;
    No *atual = f->inicio;

    while (atual != NULL) {
        if (atual->dado.contador_espera >= limite_espera && atual->dado.prioridade < 3) {
            atual->dado.prioridade++;
            atual->dado.contador_espera = 0;
            promovidos++;
        }
        atual = atual->proximo;
    }

    if (promovidos > 0) {
        No *antiga_lista = f->inicio;
        f->inicio = NULL;
        f->quantidade = 0;

        while (antiga_lista != NULL) {
            No *proximo_no = antiga_lista->proximo;
            fila_inserir(f, antiga_lista->dado);
            node_destruir(antiga_lista);
            antiga_lista = proximo_no;
        }
    }

    return promovidos;
}

int fila_obter_elemento(const FilaPrioridade *f, int indice, Atendimento *saida) {
    if (f == NULL || saida == NULL || indice < 0 || indice >= f->quantidade) return 0;

    No *atual = f->inicio;
    int i = 0;
    while (atual != NULL && i < indice) {
        atual = atual->proximo;
        i++;
    }

    if (atual != NULL) {
        *saida = atual->dado;
        return 1;
    }
    return 0;
}
