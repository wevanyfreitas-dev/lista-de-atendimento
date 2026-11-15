#ifndef PERSISTENCIA_H
#define PERSISTENCIA_H

#include "fila.h"
#include "atendimento.h"

int persistencia_salvar_fila(const FilaPrioridade *f, const char *nome_arquivo);
int persistencia_carregar_fila(FilaPrioridade *f, const char *nome_arquivo);

int persistencia_salvar_historico(Atendimento **historico, int qtd, const char *nome_arquivo);
int persistencia_carregar_historico(Atendimento ***historico, int *qtd, const char *nome_arquivo);

#endif /* PERSISTENCIA_H */

