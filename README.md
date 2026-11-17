# 🏥 Sistema de Fila de Atendimento Prioritário
> Projeto desenvolvido para a disciplina de *Programação Avançada* (FACAPE - 2026.2)  
> *Professor:* Thierry Araujo  
> *Etapa Atual:* Checkpoint Final

## 1. Objetivo do Projeto
O objetivo do sistema é gerenciar uma *Fila de Atendimento Prioritário* para triagem de pacientes/atendimentos. O programa organiza a ordem de atendimento de acordo com a prioridade cadastrada (Urgente, Prioriário, Normal) mantendo a estabilidade por ordem de chegada para pacientes com o mesmo nível de prioridade.
---

*Identificação da Equipe*:
1. Wévany de Andrade Freitas
2. Luciano Gomes dos Santos
3. Alexandre David de Souza Silva
4. Sauan Paranhos Sousa

## 3. Estrutura Principal dos Módulos
O projeto foi desenvolvido em Linguagem C com execução em modo texto (terminal), aplicando de forma rigorosa os conceitos de modularização, encapsulamento estrito e ocultação de informação através de múltiplos arquivos:

* *atendimento.h / atendimento.c: Define o tipo abstrato opaco *Atendimento*. A estrutura interna *struct Atendimento* está declarada exclusivamente no arquivo *.c**, impedindo o acesso direto aos seus campos. Disponibiliza construtores, destrutores e funções de acesso seguro ("getters") para leitura e modificação de atributos (como ID, prioridade e tempo de espera).
* *node.h / node.c: Abstrai e encapsula os nós da lista encadeada dinâmica (struct No). Gerencia as operações de alocação de memória na heap (malloc) e desalocação (free) de nós individuais, além de controlar de forma protegida o encadeamento dos ponteiros de navegação (proximo*).
* *fila.h / fila.c: Define o ponteiro incompleto *FilaPrioridade* e esconde os membros concretos da estrutura (struct fila_prioridade*). Implementa a inserção ordenada por prioridade mantendo a estabilidade FIFO, remoção do primeiro nó para atendimento, cancelamento de registros por ID e o algoritmo do mecanismo Anti-Starvation.
* *persistencia.h / persistencia.c: Módulo de armazenamento secundário. Responsável por gravar e restaurar o estado da fila e do histórico em arquivos de texto delimitados por ponto e vírgula (;*), consumindo e gerando ponteiros através das interfaces seguras dos TADs de Atendimento e Fila.
* *interface.h / interface.c: Módulo de interação com o usuário. Exibe o menu principal, efetua a leitura de entradas de teclado com tratamento de buffer (getchar()*) para evitar corrupção de dados e emite relatórios estatísticos e percentuais dos atendimentos realizados.
* *main.c*: Ponto de entrada do programa. Conecta todos os módulos , gerencia os geradores de sequenciais baseados na persistência e garante a desalocação completa de toda a memória dinâmica alocada antes de finalizar a aplicação.
---

## 4. TAD(s) e Estruturas de Dados
O projeto adota uma arquitetura avançada de *Tipo Abstrato de Dados (TAD)* Opaco Triplo para garantir o encapsulamento absoluto, onde o código cliente (main.c) não possui visibilidade física de nenhum membro das structs internas:

1. *Atendimento (TAD Opaco): Representa a entidade do paciente. O código cliente apenas manipula ponteiros do tipo *Atendimento***. Toda leitura de dados (ID, nome, prioridade) é feita obrigatoriamente por funções de leitura segura (getters), impedindo alterações acidentais de estado.
2. *No (TAD Opaco)* : Representa a célula de armazenamento da lista encadeada. Isola o encadeamento dos nós e protege o ponteiro para o dado **Atendimento***, garantindo que a estrutura física da lista seja manipulada apenas por funções homologadas.
3.  *FilaPrioridade (TAD Opaco - Lista Encadeada com Prioridade)*:
 * Inserção Ordenada Estável*: Garante que pacientes de maior urgência fiquem à frente. Em caso de empate de prioridade, a inserção respeita rigorosamente a ordem de chegada (estabilidade FIFO).
 * Gerenciamento Estrito de Memória: Toda alocação é dinâmica via *malloc*. As exclusões e a destruição final da fila percorrem os nós efetuando a desalocação em cascata com *free**, eliminando completamente os riscos de memory leaks (vazamento de memória).
---

## 5. Principais Regras do Problema e Gerenciamento
* *Níveis de Prioridade:*
  1. Urgente
  2. Prioritário
  3. Normal
* *Critério de Fila:* 
  * Pacientes com prioridades maiores têm preferência na chamada.
  * Para prioridades iguais, a ordem de chegada é estritamente mantida.

* *Memória Dinâmica (Heap):* A fila cresce dinamicamente conforme demandas por meio de malloc. O histórico de atendimentos utiliza realloc seguro. Todas as alocações contam com checagem contra retorno NULL. Na remoção ou destruição da fila, cada bloco é devidamente liberado via free.
* *Persistência em Arquivo:* Os dados são salvos em formato de texto delimitado por ponto e vírgula em fila_pendente.txt e historico.txt. Caso o arquivo não exista no primeiro arranque, o sistema trata o retorno de fopen e inicializa com estruturas vazias.

---

## 6. Funcionalidade Adicional da Equipe (Mecanismo Anti-Starvation)

Para evitar que atendimentos de prioridade normal fiquem aguardando indefinidamente na fila devido à chegada contínua de pessoas prioritárias (starvation), a equipe implementou um *mecanismo de envelhecimento*:

* Cada chamada de atendimento incrementa o contador de espera das pessoas restantes na fila.
* A função fila_aplicar_antistarvation() verifica se alguém atingiu o limite de ciclos (ex.: 3 ciclos de espera) e promove temporariamente seu nível de prioridade em +1, reordenando a fila de forma estável.

---

##  7. Declaração sobre o uso de Ferramentas de IA

Ferramentas de IA generativa foram consultadas pontualmente para auxílio na estruturação inicial dos cabeçalhos do TAD opaco, elaboração do Makefile e revisão sintática de código. Todo o código e arquitetura foram revisados, testados e validados pelos integrantes da equipe.
