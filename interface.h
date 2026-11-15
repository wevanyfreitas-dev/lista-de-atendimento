#ifndef INTERFACE_H
#define INTERFACE_H

#include "atendimento.h"

void exibir_menu(void);
int ler_opcao(void);
void limpar_buffer(void);
Atendimento* ler_dados_atendimento(int *seq_id, int *seq_ordem);
void exibir_historico_e_estatisticas(Atendimento **historico, int qtd);

#endif /* INTERFACE_H */

