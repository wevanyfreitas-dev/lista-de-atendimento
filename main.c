#include <stdio.h>
#include <stdlib.h>
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

    Atendimento *historico = NULL;
    int qtd_historico = 0;
    int seq_id = 101;
    int seq_ordem = 1;

    persistencia_carregar_fila(fila, ARQUIVO_FILA);
    persistencia_carregar_historico(&historico, &qtd_historico, ARQUIVO_HISTORICO);

    int i;
    for (i = 0; i < fila_tamanho(fila); i++) {
        Atendimento a;
        if (fila_obter_elemento(fila, i, &a)) {
            if (a.id >= seq_id) seq_id = a.id + 1;
            if (a.ordem_chegada >= seq_ordem) seq_ordem = a.ordem_chegada + 1;
        }
    }
    for (i = 0; i < qtd_historico; i++) {
        if (historico[i].id >= seq_id) seq_id = historico[i].id + 1;
        if (historico[i].ordem_chegada >= seq_ordem) seq_ordem = historico[i].ordem_chegada + 1;
    }

    int opcao;
    do {
        exibir_menu();
        opcao = ler_opcao();

        switch (opcao) {
            case 1: {
                Atendimento novo = ler_dados_atendimento(&seq_id, &seq_ordem);
                if (fila_inserir(fila, novo)) {
                    printf("[SUCESSO] %s inserido(a) na fila com prioridade %d!\n", novo.nome, novo.prioridade);
                } else {
                    printf("[ERRO] Falha ao alocar memoria para o atendimento.\n");
                }
                break;
            }
            case 2: {
                Atendimento chamado;
                if (fila_chamar_proximo(fila, &chamado)) {
                    printf("\n>>> CHAMANDO PARA ATENDIMENTO: %s (ID: %d | Prioridade: %d) <<<\n",
                           chamado.nome, chamado.id, chamado.prioridade);

                    Atendimento *temp = (Atendimento*) realloc(historico, (qtd_historico + 1) * sizeof(Atendimento));
                    if (temp != NULL) {
                        historico = temp;
                        historico[qtd_historico++] = chamado;
                    }
                } else {
                    printf("[AVISO] Nao ha pessoas na fila de espera.\n");
                }
                break;
            }
            case 3: {
                fila_exibir(fila);
                break;
            }
            case 4: {
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
            case 5: {
                int promovidos = fila_aplicar_antistarvation(fila, LIMITE_ANTISTARVATION);
                printf("[ANTI-STARVATION] %d pessoa(s) foram promovidas de prioridade por tempo de espera.\n", promovidos);
                break;
            }
            case 6: {
                exibir_historico_e_estatisticas(historico, qtd_historico);
                break;
            }
            case 0: {
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

    fila_destruir(fila);
    if (historico != NULL) {
        free(historico);
    }

    return 0;
}

