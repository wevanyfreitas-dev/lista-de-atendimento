#include <stdio.h>
#include <stdlib.h>
#include "fila.h"
#include "node.h"

struct fila_prioridade {
    No *inicio;
    int quantidade;
};

FilaPrioridade* fila_criar(void) {
    FilaPrioridade *f = (FilaPrioridade*) malloc(sizeof(FilaPrioridade));
    if (f == NULL) return NULL;
    f->inicio = NULL;
    f->quantidade = 0;
    return f;
}

void fila_destruir(FilaPrioridade *f) {
    if (f == NULL) return;
    No *atual = f->inicio;
    while (atual != NULL) {
        No *temp = node_get_proximo(atual);
        node_destruir(atual);
        atual = temp;
    }
    free(f);
}

int fila_inserir(FilaPrioridade *f, Atendimento *a) {
    if (f == NULL || a == NULL) return 0;
    No *novo = node_criar(a);
    if (novo == NULL) return 0;

    int prio_nova = atendimento_get_prioridade(a);

    if (f->inicio == NULL || prio_nova > atendimento_get_prioridade(node_get_dado(f->inicio))) {
        node_set_proximo(novo, f->inicio);
        f->inicio = novo;
    } else {
        No *atual = f->inicio;
        while (node_get_proximo(atual) != NULL &&
               atendimento_get_prioridade(node_get_dado(node_get_proximo(atual))) >= prio_nova) {
            atual = node_get_proximo(atual);
        }
        node_set_proximo(novo, node_get_proximo(atual));
        node_set_proximo(atual, novo);
    }
    f->quantidade++;
    return 1;
}

Atendimento* fila_chamar_proximo(FilaPrioridade *f) {
    if (fila_vazia(f)) return NULL;
    No* removido = f->inicio;
    f->inicio = node_get_proximo(removido);

    Atendimento* atendido = node_liberar_dado(removido);
    free(removido);
    f->quantidade--;

    No *aux = f->inicio;
    while (aux != NULL) {
        atendimento_incrementar_espera(node_get_dado(aux));
        aux = node_get_proximo(aux);
    }
    return atendido;
}

int fila_cancelar(FilaPrioridade *f, int id) {
    if (fila_vazia(f)) return 0;
    No *atual = f->inicio;
    No *anterior = NULL;

    while (atual != NULL && atendimento_get_id(node_get_dado(atual)) != id) {
        anterior = atual;
        atual = node_get_proximo(atual);
    }

    if (atual == NULL) return 0;

    if (anterior == NULL) f->inicio = node_get_proximo(atual);
    else node_set_proximo(anterior, node_get_proximo(atual));

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
    if (fila_vazia(f)) {
        printf("\n[STATUS] A fila de espera esta vazia.\n");
        return;
    }
    printf("\n================ FILA DE ESPERA (%d PESSOAS) ================\n", f->quantidade);
    No *atual = f->inicio;
    int pos = 1;
    while (atual != NULL) {
        printf("%2d. ", pos++);
        atendimento_exibir(node_get_dado(atual));
        atual = node_get_proximo(atual);
    }
    printf("===========================================================\n");
}

int fila_aplicar_antistarvation(FilaPrioridade *f, int limite_espera) {
    if (fila_vazia(f)) return 0;
    int promovidos = 0;
    No *atual = f->inicio;

    while (atual != NULL) {
        Atendimento* a = node_get_dado(atual);
        if (atendimento_get_contador_espera(a) >= limite_espera && atendimento_get_prioridade(a) < 3) {
            atendimento_promover_prioridade(a);
            atendimento_resetar_espera(a);
            promovidos++;
        }
        atual = node_get_proximo(atual);
    }

    if (promovidos > 0) {
        No *lista_antiga = f->inicio;
        f->inicio = NULL;
        f->quantidade = 0;

        while (lista_antiga != NULL) {
            No *proximo_no = node_get_proximo(lista_antiga);
            Atendimento* a = node_liberar_dado(lista_antiga);
            free(lista_antiga);
            fila_inserir(f, a);
            lista_antiga = proximo_no;
        }
    }
    return promovidos;
}

Atendimento* fila_obter_elemento(const FilaPrioridade *f, int indice) {
    if (f == NULL || indice < 0 || indice >= f->quantidade) return NULL;
    No *atual = f->inicio;
    int i;
    for (i = 0; i < indice && atual != NULL; i++) {
        atual = node_get_proximo(atual);
    }
    return (atual != NULL) ? node_get_dado(atual) : NULL;
}

