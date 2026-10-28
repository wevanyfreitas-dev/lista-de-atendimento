


typedef struct node Node;
No* node_criar(Atendimento a);
void node_destruir(No *no);

void atendimento_exibir(Atendimento a);
typedef struct atendimento Atendimento;

typedef struct fila_p Fila_P;
Fila_P* criar(void);
void destruir(Fila_P *f);
int inserir(Fila_P *f, Atendimento a);
int chamar_proximo(Fila_P *f, Atendimento *atendido);
int cancelar(Fila_P *f, int id);
int vazia(const Fila_P *f);
int tamanho(const Fila_P *f);
void exibir(const Fila_P *f);

int fila_obter_elemento(const Fila_P *f, int indice, Atendimento *saida);
