#include <stdio.h>
#include <stdlib.h>
#include "interface.h"

int persistencia_salvar_fila(const FilaPrioridade *f, const char *nome_arquivo) {
    if (f == NULL || nome_arquivo == NULL) return 0;

    FILE *fp = fopen(nome_arquivo, "w");
    if (fp == NULL) return 0;

    int total = fila_tamanho(f);
    int i;
    for (i = 0; i < total; i++) {
        Atendimento a;
        if (fila_obter_elemento(f, i, &a)) {
            fprintf(fp, "%d;%s;%d;%d;%d\n",
                    a.id, a.nome, a.prioridade, a.ordem_chegada, a.contador_espera);
        }
    }

    fclose(fp);
    return 1;
}

int persistencia_carregar_fila(FilaPrioridade *f, const char *nome_arquivo) {
    if (f == NULL || nome_arquivo == NULL) return 0;

    FILE *fp = fopen(nome_arquivo, "r");
    if (fp == NULL) return 1;

    Atendimento a;
    while (fscanf(fp, "%d;%49[^;];%d;%d;%d\n",
                  &a.id, a.nome, &a.prioridade, &a.ordem_chegada, &a.contador_espera) == 5) {
        fila_inserir(f, a);
    }

    fclose(fp);
    return 1;
}

int persistencia_salvar_historico(Atendimento *historico, int qtd, const char *nome_arquivo) {
    if (nome_arquivo == NULL) return 0;

    FILE *fp = fopen(nome_arquivo, "w");
    if (fp == NULL) return 0;
	
	int i;
    for (i = 0; i < qtd; i++) {
        fprintf(fp, "%d;%s;%d;%d;%d\n",
                historico[i].id, historico[i].nome, historico[i].prioridade,
                historico[i].ordem_chegada, historico[i].contador_espera);
    }

    fclose(fp);
    return 1;
}

int persistencia_carregar_historico(Atendimento **historico, int *qtd, const char *nome_arquivo) {
    if (historico == NULL || qtd == NULL || nome_arquivo == NULL) return 0;

    FILE *fp = fopen(nome_arquivo, "r");
    if (fp == NULL) {
        *historico = NULL;
        *qtd = 0;
        return 1;
    }

    int capacidade = 10;
    *qtd = 0;
    historico = (Atendimento) malloc(capacidade * sizeof(Atendimento));
    if (*historico == NULL) {
        fclose(fp);
        return 0;
    }

    Atendimento a;
    while (fscanf(fp, "%d;%49[^;];%d;%d;%d\n",
                  &a.id, a.nome, &a.prioridade, &a.ordem_chegada, &a.contador_espera) == 5) {
        if (*qtd >= capacidade) {
            capacidade *= 2;
            Atendimento temp = (Atendimento) realloc(*historico, capacidade * sizeof(Atendimento));
            if (temp == NULL) {
                fclose(fp);
                return 0;
            }
            *historico = temp;
        }
        (*historico)[*qtd] = a;
        (*qtd)++;
    }

    fclose(fp);
    return 1;
}
