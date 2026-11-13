#include <stdio.h>
#include "interface.h"

void atendimento_exibir(Atendimento a) {
    const char *prio_str = "Desconhecido";
    if (a.prioridade == 1) prio_str = "Normal";
    else if (a.prioridade == 2) prio_str = "Prioritario";
    else if (a.prioridade == 3) prio_str = "Urgente";

    printf("[ID: %03d] Nome: %-18s | Prioridade: %d (%-11s) | Ordem: %d | Espera: %d ciclos\n",
           a.id, a.nome, a.prioridade, prio_str, a.ordem_chegada, a.contador_espera);
}

