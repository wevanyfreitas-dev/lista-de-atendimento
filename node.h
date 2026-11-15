#ifndef NODE_H
#define NODE_H

#include "atendimento.h"

// TAD Opaco para No
typedef struct No No;

// --- Interface Pública ---

No* node_criar(Atendimento* a);
void node_destruir(No* no);

// Funções para manipulação da lista encadeada
No* node_get_proximo(const No* no);
void node_set_proximo(No* no, No* proximo);
Atendimento* node_get_dado(const No* no); // Getter para o dado

// Retorna o ponteiro para o dado, transferindo a posse
Atendimento* node_liberar_dado(No* no);

#endif /* NODE_H */

