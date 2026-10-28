#include <stdio.h>
#include <stdlib.h>
#include <locale.h>
#include "interface.h"
#include "atendimento.c"


int main(void){
	setlocale(LC_ALL, "Portuguese");
	
	Fila_P *fila = criar();
	Atendimento atend;
	int opcao= -1;
	
	if (fila==NULL){
		printf("ERROR!\n");
		return 1;
	}
	
	while (opcao!=0){
		printf("\t=======================================\n");
		printf("\tMENU DE ATENDIMENTO\n");
		printf("\t=======================================\n");
		printf("1 - Inserir Atendimento.\n");
		printf("2 - Proximo Atendimento.\n");
		printf("3 - Exibir fila.\n");
		printf("4 - Tamanho da fila.\n");
		printf("5 - Verificar se esta¡ vazia.\n");
		printf("0 - Sair.\n");
		printf("Escolha a Opçao: ");
		scanf("%d", &opcao);
		
			switch (opcao){
				case 1:
					printf("\t === Preencha os seguintes dados ===\n");
					printf("\nID: ");
					scanf("%d", &atend.id);
					
					printf("\nNome: ");
					scanf(" %[^\n]", atend.nome);
					
					printf("1- Alta\n2- Media\n3- Baixa.");
					printf("Prioridade: ");
					scanf("%d", &atend.prioridade);
					
					if(inserir(fila, atend)){
						printf("O atendimento foi inserido com sucesso.");
					} else {
						printf("Erro ao abrir atendimento...");
					}
					break;
					
				case 2:
					if (remover(fila, &atend)){
						printf("\n Proximo atendimento a ser chamado:\n");
						printf("ID: %d\nNome: %s\nPrioridade: %d\n", atend.id, atend.nome, atend.prioridade);
					}
					else{
						printf("Fila Vazia...");
					}
					break;
					
				case 3:
					exibir(fila);
					break;
					
				case 4:
					printf("\nTamanho da fila: %d\n", tamanho(fila));
					break;
				
				case 5:
					if (vazia(fila)){
						printf("A fila esta¡ Vazia.\n");
					} else{
						printf("A fila possui pacientes.\n");
					}
					break;


                case 0:
                	destruir(fila);
                	printf("\nPrograma encerrado.\n");
                	break;
                	
                default:
                	printf("ERRO: DIGITE UMA OPCAO VALIDA.");
			}
	}
return 0;
}
