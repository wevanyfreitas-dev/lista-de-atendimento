#include <stdio.h>
#include <stdlib.h>
#include "interface.h"

struct atendimento{
	int id;
	char nome [30];
	int prioridade;
	int ordem_chegada;
};

void atendimento_exibir(Atendimento a) {
	const char *prio_str = "Desconhecido";
	if (a.prioridade == 1) prio_str = "Normal";
	else if (a.prioridade == 2) prio_str = "Prioritario";
	else if (a.prioridade == 3) prio_str = "Urgente";
	
	printf("[ID: %d] Nome: %-18s | Prioridade: %d (%s) | Ordem: %d\\n",
	a.id, a.nome, a.prioridade, prio_str, a.ordem_chegada);
}
