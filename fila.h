#ifndef FILA_H
#define FILA_H

#include "atendimento.h"

typedef struct fila_prioridade FilaPrioridade;

FilaPrioridade* fila_criar(void);
void fila_destruir(FilaPrioridade *f);

int fila_inserir(FilaPrioridade *f, Atendimento *a);
Atendimento* fila_chamar_proximo(FilaPrioridade *f);
int fila_cancelar(FilaPrioridade *f, int id);
int fila_vazia(const FilaPrioridade *f);
int fila_tamanho(const FilaPrioridade *f);
void fila_exibir(const FilaPrioridade *f);

int fila_aplicar_antistarvation(FilaPrioridade *f, int limite_espera);
Atendimento* fila_obter_elemento(const FilaPrioridade *f, int indice);

#endif /* FILA_H */

