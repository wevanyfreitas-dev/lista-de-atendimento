#ifndef ATENDIMENTO_H
#define ATENDIMENTO_H

// Tipo Abstrato de Dados Opaco
typedef struct Atendimento Atendimento;

// Ciclo de vida
Atendimento* atendimento_criar(int id, const char* nome, int prioridade, int ordem_chegada);
void atendimento_destruir(Atendimento* a);

// Getters (Acesso seguro aos dados internos)
int atendimento_get_id(const Atendimento* a);
const char* atendimento_get_nome(const Atendimento* a);
int atendimento_get_prioridade(const Atendimento* a);
int atendimento_get_ordem_chegada(const Atendimento* a);
int atendimento_get_contador_espera(const Atendimento* a);

// Modificadores de estado (Anti-Starvation)
void atendimento_incrementar_espera(Atendimento* a);
void atendimento_promover_prioridade(Atendimento* a);
void atendimento_resetar_espera(Atendimento* a);

// Funções utilitárias
void atendimento_exibir(const Atendimento* a);
int atendimento_comparar_prioridade(const Atendimento* a1, const Atendimento* a2);
int atendimento_possui_id(const Atendimento* a, int id);
int atendimento_deve_promover(const Atendimento* a, int limite_espera);
void atendimento_promover_e_resetar(Atendimento* a);

#endif /* ATENDIMENTO_H */

