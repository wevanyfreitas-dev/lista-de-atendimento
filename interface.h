typedef struct atendimento Atendimento;

typedef struct fila_p Fila_P;

typedef struct node Node;

Fila_P* criar(void);
void destruir(Fila_P *f);
int remover(Fila_P *f, Atendimento *removido);
int inserir(Fila_P *f, Atendimento *a);
int vazia(const Fila_P *f);
int tamanho(const Fila_P *f);
void exibir(const Fila_P *f);
Node *criar_node(Atendimento dado);
void destruir_node(Node *n);
int id(int a, int b);
