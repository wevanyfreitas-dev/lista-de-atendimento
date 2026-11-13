#ifndef INTERFACE_H
#define INTERFACE_H


//1. MÓDULO ATENDIMENTO
typedef struct {
    int id;
    char nome[50];
    int prioridade;
    int ordem_chegada;
    int contador_espera;
} Atendimento;

void atendimento_exibir(Atendimento a);


// 2. MÓDULO NÓ
typedef struct no No;

struct no {
    Atendimento dado;
    struct no *proximo;
};

No* node_criar(Atendimento a);
void node_destruir(No *no);

// 3. MÓDULO FILA
typedef struct fila_prioridade FilaPrioridade;

FilaPrioridade* fila_criar(void);
void fila_destruir(FilaPrioridade *f);
int fila_inserir(FilaPrioridade *f, Atendimento a);
int fila_chamar_proximo(FilaPrioridade *f, Atendimento *atendido);
int fila_cancelar(FilaPrioridade *f, int id);
int fila_vazia(const FilaPrioridade *f);
int fila_tamanho(const FilaPrioridade *f);
void fila_exibir(const FilaPrioridade *f);
int fila_aplicar_antistarvation(FilaPrioridade *f, int limite_espera);
int fila_obter_elemento(const FilaPrioridade *f, int indice, Atendimento *saida);


// 4. MÓDULO PERSISTÊNCIA
int persistencia_salvar_fila(const FilaPrioridade *f, const char *nome_arquivo);
int persistencia_carregar_fila(FilaPrioridade *f, const char *nome_arquivo);
int persistencia_salvar_historico(Atendimento *historico, int qtd, const char *nome_arquivo);
int persistencia_carregar_historico(Atendimento **historico, int *qtd, const char *nome_arquivo);


// 5. MÓDULO INTERFACE
void exibir_menu(void);
int ler_opcao(void);
void limpar_buffer(void);
Atendimento ler_dados_atendimento(int *seq_id, int *seq_ordem);
void exibir_historico_e_estatisticas(Atendimento *historico, int qtd);

#endif // INTERFACE_H
