#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "atendimento.h"

// Estrutura concreta protegida dentro deste arquivo
struct Atendimento {
    int id;
    char nome[50];
    int prioridade;
    int ordem_chegada;
    int contador_espera;
};

Atendimento* atendimento_criar(int id, const char* nome, int prioridade, int ordem_chegada) {
    Atendimento* a = (Atendimento*) malloc(sizeof(Atendimento));
    if (a != NULL) {
        a->id = id;
        strncpy(a->nome, nome, sizeof(a->nome) - 1);
        a->nome[sizeof(a->nome) - 1] = '\0';
        a->prioridade = prioridade;
        a->ordem_chegada = ordem_chegada;
        a->contador_espera = 0;
    }
    return a;
}

void atendimento_destruir(Atendimento* a) {
    if (a != NULL) {
        free(a);
    }
}

int atendimento_get_id(const Atendimento* a) { 
    return (a != NULL) ? a->id : 0; 
}

const char* atendimento_get_nome(const Atendimento* a) { 
    return (a != NULL) ? a->nome : ""; 
}

int atendimento_get_prioridade(const Atendimento* a) { 
    return (a != NULL) ? a->prioridade : 0; 
}

int atendimento_get_ordem_chegada(const Atendimento* a) { 
    return (a != NULL) ? a->ordem_chegada : 0; 
}

int atendimento_get_contador_espera(const Atendimento* a) { 
    return (a != NULL) ? a->contador_espera : 0; 
}

void atendimento_incrementar_espera(Atendimento* a) {
    if (a != NULL) a->contador_espera++;
}

void atendimento_promover_prioridade(Atendimento* a) {
    if (a != NULL && a->prioridade < 3) a->prioridade++;
}

void atendimento_resetar_espera(Atendimento* a) {
    if (a != NULL) a->contador_espera = 0;
}

void atendimento_exibir(const Atendimento* a) {
    if (a == NULL) return;
    const char *prio_str = "Desconhecido";
    if (a->prioridade == 1) prio_str = "Normal";
    else if (a->prioridade == 2) prio_str = "Prioritario";
    else if (a->prioridade == 3) prio_str = "Urgente";

    printf("[ID: %03d] Nome: %-18s | Prioridade: %d (%-11s) | Ordem: %d | Espera: %d ciclos\n",
           a->id, a->nome, a->prioridade, prio_str, a->ordem_chegada, a->contador_espera);
}

int atendimento_comparar_prioridade(const Atendimento* a1, const Atendimento* a2) {
    if (a1 == NULL || a2 == NULL) return 0;
    if (a1->prioridade > a2->prioridade) return 1;
    if (a1->prioridade < a2->prioridade) return -1;
    return 0;
}

int atendimento_possui_id(const Atendimento* a, int id) {
    return (a != NULL && a->id == id);
}

int atendimento_deve_promover(const Atendimento* a, int limite_espera) {
    return (a != NULL && a->contador_espera >= limite_espera && a->prioridade < 3);
}

void atendimento_promover_e_resetar(Atendimento* a) {
    if (a != NULL) {
        if (a->prioridade < 3) a->prioridade++;
        a->contador_espera = 0;
    }
}

