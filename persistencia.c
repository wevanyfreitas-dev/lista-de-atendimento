#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "persistencia.h"
#include "atendimento.h"

int persistencia_salvar_fila(const FilaPrioridade *f, const char *nome_arquivo) {
    if (f == NULL || nome_arquivo == NULL) return 0;

    FILE *fp = fopen(nome_arquivo, "w");
    if (fp == NULL) return 0;

    int total = fila_tamanho(f);
    int i;
    for (i = 0; i < total; i++) {
        // fila_obter_elemento agora retorna um ponteiro constante para o atendimento
        const Atendimento* a = fila_obter_elemento(f, i);
        if (a != NULL) {
            // Usamos os getters para acessar os dados
            fprintf(fp, "%d;%s;%d;%d;%d\n",
                    atendimento_get_id(a),
                    atendimento_get_nome(a),
                    atendimento_get_prioridade(a),
                    atendimento_get_ordem_chegada(a),
                    atendimento_get_contador_espera(a));
        }
    }

    fclose(fp);
    return 1;
}

int persistencia_carregar_fila(FilaPrioridade *f, const char *nome_arquivo) {
    if (f == NULL || nome_arquivo == NULL) return 0;

    FILE *fp = fopen(nome_arquivo, "r");
    if (fp == NULL) return 1;

    int id, prioridade, ordem, espera;
    char nome[50];

    while (fscanf(fp, "%d;%49[^;];%d;%d;%d\n", &id, nome, &prioridade, &ordem, &espera) == 5) {
        Atendimento* novo_atendimento = atendimento_criar(id, nome, prioridade, ordem);
        if (novo_atendimento != NULL) {
            int i;
            for(i = 0; i < espera; i++) {
                atendimento_incrementar_espera(novo_atendimento);
            }
            fila_inserir(f, novo_atendimento);
        }
    }

    fclose(fp);
    return 1;
}


int persistencia_salvar_historico(Atendimento** historico, int qtd, const char *nome_arquivo) {
    if (nome_arquivo == NULL) return 0;

    FILE *fp = fopen(nome_arquivo, "w");
    if (fp == NULL) return 0;

    int i;
    for (i = 0; i < qtd; i++) {
        Atendimento* a = historico[i]; // Pega o ponteiro do histórico
        if (a != NULL) {
            fprintf(fp, "%d;%s;%d;%d;%d\n",
                    atendimento_get_id(a),
                    atendimento_get_nome(a),
                    atendimento_get_prioridade(a),
                    atendimento_get_ordem_chegada(a),
                    atendimento_get_contador_espera(a));
        }
    }

    fclose(fp);
    return 1;
}

int persistencia_carregar_historico(Atendimento*** historico, int *qtd, const char *nome_arquivo) {
    if (historico == NULL || qtd == NULL || nome_arquivo == NULL) return 0;

    FILE *fp = fopen(nome_arquivo, "r");
    if (fp == NULL) {
        *historico = NULL;
        *qtd = 0;
        return 1; // Primeira execução
    }

    int capacidade = 10;
    *qtd = 0;
    // O histórico agora é um vetor de ponteiros para Atendimento
    *historico = (Atendimento**) malloc(capacidade * sizeof(Atendimento*));
    if (*historico == NULL) {
        fclose(fp);
        return 0;
    }

    int id, prioridade, ordem, espera;
    char nome[50];

    while (fscanf(fp, "%d;%49[^;];%d;%d;%d\n", &id, nome, &prioridade, &ordem, &espera) == 5) {
        if (*qtd >= capacidade) {
            capacidade *= 2;
            Atendimento** temp = (Atendimento**) realloc(*historico, capacidade * sizeof(Atendimento*));
            if (temp == NULL) {
                // Em caso de falha, liberar memória já alocada
                int i;
                for (i = 0; i < *qtd; i++) {
                    atendimento_destruir((*historico)[i]);
                }
                free(*historico);
                fclose(fp);
                return 0;
            }
            *historico = temp;
        }
        // Cria um novo atendimento e armazena seu ponteiro no vetor
        (*historico)[*qtd] = atendimento_criar(id, nome, prioridade, ordem);
        (*qtd)++;
    }

    fclose(fp);
    return 1;
}

