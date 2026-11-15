#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "interface.h"

void limpar_buffer(void) {
    int c;
    while ((c = getchar()) != '\n' && c != EOF);
}

void exibir_menu(void) {
    printf("\n=========================================\n");
    printf("    SISTEMA DE ATENDIMENTO PRIORITARIO   \n");
    printf("=========================================\n");
    printf("1. Inserir Pessoa na Fila\n");
    printf("2. Chamar Proximo Atendimento\n");
    printf("3. Visualizar Fila de Espera\n");
    printf("4. Cancelar Atendimento por ID\n");
    printf("5. Executar Mecanismo Anti-Starvation\n");
    printf("6. Consultar Historico e Estatisticas\n");
    printf("0. Salvar e Sair\n");
    printf("=========================================\n");
    printf("Escolha uma opcao: ");
}

int ler_opcao(void) {
    int opcao;
    if (scanf("%d", &opcao) != 1) {
        limpar_buffer();
        return -1;
    }
    limpar_buffer();
    return opcao;
}

Atendimento* ler_dados_atendimento(int *seq_id, int *seq_ordem) {
    char nome[50];
    int prioridade;
    int id_atual = (*seq_id)++;
    int ordem_atual = (*seq_ordem)++;

    printf("\n--- Novo Atendimento (ID Gerado: %d) ---\n", id_atual);
    printf("Digite o nome da pessoa: ");
    if (fgets(nome, sizeof(nome), stdin) != NULL) {
        nome[strcspn(nome, "\n")] = '\0';
    }

    do {
        printf("Selecione a Prioridade (1 = Normal, 2 = Prioritario, 3 = Urgente): ");
        if (scanf("%d", &prioridade) != 1) {
            prioridade = 0;
        }
        limpar_buffer();

        if (prioridade < 1 || prioridade > 3) {
            printf("[ERRO] Prioridade invalida! Digite um valor entre 1 e 3.\n");
        }
    } while (prioridade < 1 || prioridade > 3);

    return atendimento_criar(id_atual, nome, prioridade, ordem_atual);
}

void exibir_historico_e_estatisticas(Atendimento **historico, int qtd) {
    if (historico == NULL || qtd == 0) {
        printf("\n[HISTORICO] Nenhum atendimento foi realizado ainda.\n");
        return;
    }

    int normais = 0, prioritarios = 0, urgentes = 0;
    int i;

    printf("\n================ HISTORICO DE ATENDIMENTOS (%d) ================\n", qtd);
    for (i = 0; i < qtd; i++) {
        Atendimento *a = historico[i];
        if (a != NULL) {
            printf("%2d. ", i + 1);
            atendimento_exibir(a);

            int p = atendimento_get_prioridade(a);
            if (p == 1) normais++;
            else if (p == 2) prioritarios++;
            else if (p == 3) urgentes++;
        }
    }
    printf("===============================================================\n");
    printf("ESTATISTICAS DE ATENDIMENTO:\n");
    printf(" - Urgentes    : %d (%.1f%%)\n", urgentes, (urgentes * 100.0) / qtd);
    printf(" - Prioritarios: %d (%.1f%%)\n", prioritarios, (prioritarios * 100.0) / qtd);
    printf(" - Normais     : %d (%.1f%%)\n", normais, (normais * 100.0) / qtd);
    printf("===============================================================\n");
}

