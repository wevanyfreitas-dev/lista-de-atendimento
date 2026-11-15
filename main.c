#include <stdio.h>
#include <stdlib.h>
#include "atendimento.h"
#include "fila.h"
#include "persistencia.h"
#include "interface.h"

#define ARQUIVO_FILA "fila_pendente.txt"
#define ARQUIVO_HISTORICO "historico.txt"
#define LIMITE_ANTISTARVATION 3

int main(void) {
    FilaPrioridade *fila = fila_criar();
    if (fila == NULL) {
        fprintf(stderr, "[ERRO CRITICO] Falha ao alocar memoria para a fila.\n");
        return 1;
    }

    Atendimento **historico = NULL;
    int qtd_historico = 0;
    int seq_id = 101;
    int seq_ordem = 1;
    int i;

    // Carrega dados persistidos
    persistencia_carregar_fila(fila, ARQUIVO_FILA);
    persistencia_carregar_historico(&historico, &qtd_historico, ARQUIVO_HISTORICO);

    // Atualiza contadores para evitar IDs repetidos
    for (i = 0; i < fila_tamanho(fila); i++) {
        Atendimento *a = fila_obter_elemento(fila, i);
        if (a != NULL) {
            if (atendimento_get_id(a) >= seq_id) seq_id = atendimento_get_id(a) + 1;
            if (atendimento_get_ordem_chegada(a) >= seq_ordem) seq_ordem = atendimento_get_ordem_chegada(a) + 1;
        }
    }
    for (i = 0; i < qtd_historico; i++) {
        Atendimento *a = historico[i];
        if (a != NULL) {
            if (atendimento_get_id(a) >= seq_id) seq_id = atendimento_get_id(a) + 1;
            if (atendimento_get_ordem_chegada(a) >= seq_ordem) seq_ordem = atendimento_get_ordem_chegada(a) + 1;
        }
    }

    int opcao;
    do {
        exibir_menu();
        opcao = ler_opcao();

        switch (opcao) {
            case 1: { // Inserir
                Atendimento *novo = ler_dados_atendimento(&seq_id, &seq_ordem);
                if (novo != NULL) {
                    if (fila_inserir(fila, novo)) {
                        printf("[SUCESSO] %s inserido(a) na fila com prioridade %d!\n",
                               atendimento_get_nome(novo), atendimento_get_prioridade(novo));
                    } else {
                        printf("[ERRO] Falha ao inserir na fila.\n");
                        atendimento_destruir(novo);
                    }
                } else {
                    printf("[ERRO] Falha ao alocar memoria para o atendimento.\n");
                }
                break;
            }
            case 2: { // Chamar Próximo
                Atendimento *chamado = fila_chamar_proximo(fila);
                if (chamado != NULL) {
                    printf("\n>>> CHAMANDO PARA ATENDIMENTO <<<\n");
                    atendimento_exibir(chamado);

                    Atendimento **temp = (Atendimento**) realloc(historico, (qtd_historico + 1) * sizeof(Atendimento*));
                    if (temp != NULL) {
                        historico = temp;
                        historico[qtd_historico++] = chamado;
                    } else {
                        atendimento_destruir(chamado);
                    }
                } else {
                    printf("[AVISO] Nao ha pessoas na fila de espera.\n");
                }
                break;
            }
            case 3: { // Visualizar Fila
                fila_exibir(fila);
                break;
            }
            case 4: { // Cancelar por ID
                int id_cancelar;
                printf("Digite o ID do atendimento a cancelar: ");
                if (scanf("%d", &id_cancelar) == 1) {
                    limpar_buffer();
                    if (fila_cancelar(fila, id_cancelar)) {
                        printf("[SUCESSO] Atendimento ID %d cancelado.\n", id_cancelar);
                    } else {
                        printf("[ERRO] Atendimento ID %d nao encontrado na fila.\n", id_cancelar);
                    }
                } else {
                    limpar_buffer();
                    printf("[ERRO] Entrada invalida.\n");
                }
                break;
            }
            case 5: { // Anti-Starvation
                int promovidos = fila_aplicar_antistarvation(fila, LIMITE_ANTISTARVATION);
                printf("[ANTI-STARVATION] %d pessoa(s) foram promovidas de prioridade por tempo de espera.\n", promovidos);
                break;
            }
            case 6: { // Histórico e Estatísticas
                exibir_historico_e_estatisticas(historico, qtd_historico);
                break;
            }
            case 0: { // Salvar e Sair
                printf("\nSalvando dados da fila e do historico...\n");
                persistencia_salvar_fila(fila, ARQUIVO_FILA);
                persistencia_salvar_historico(historico, qtd_historico, ARQUIVO_HISTORICO);
                printf("Dados salvos com sucesso! Encerrando o sistema.\n");
                break;
            }
            default:
                printf("[ERRO] Opcao invalida! Tente novamente.\n");
                break;
        }
    } while (opcao != 0);

    // Liberação de memória
    fila_destruir(fila);
    if (historico != NULL) {
        for (i = 0; i < qtd_historico; i++) {
            atendimento_destruir(historico[i]);
        }
        free(historico);
    }

    return 0;
}

