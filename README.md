# 🏥 Sistema de Fila de Atendimento Prioritário
> Projeto desenvolvido para a disciplina de **Programação Avançada** (FACAPE - 2026.2)  
> **Professor:** Thierry Araujo  
> **Etapa Atual:** Checkpoint Final

## 1. Objetivo do Projeto
O objetivo do sistema é gerenciar uma **Fila de Atendimento Prioritário** para triagem de pacientes/atendimentos. O programa organiza a ordem de atendimento de acordo com a prioridade cadastrada (Urgente, Prioriário, Normal) mantendo a estabilidade por ordem de chegada para pacientes com o mesmo nível de prioridade.
---

**Identificação da Equipe**:
1. Wévany de Andrade Freitas
2. Luciano Gomes dos Santos
3. Alexandre David de Souza Silva
4. Sauan Paranhos Sousa

## 3. Estrutura Principal dos Módulos
O projeto foi desenvolvido em **Linguagem C** com execução em modo texto (terminal), aplicando os conceitos de modularização e encapsulamento:

* **`interface.h`**: Contém as declarações dos tipos abstratos de dados e os protótipos de todas as funções públicas acessíveis pelo sistema.
* **`interface.c`**: Módulo de interação com o usuário. Exibe o menu principal, efetua a leitura de entradas numéricas e strings com limpeza de buffer (`getchar()`) e calcula estatísticas relativas dos atendimentos.
* **`atendimento.c`**: Define o registro do paciente/cliente (`struct Atendimento`) e funções utilitárias de formatação visual para exibição do registro no terminal.
* **`node.c`**: Abstrai os nós da lista encadeada dinâmica. Gerencia as operações de alocação de memória na *heap* (`malloc`) e desalocação (`free`) de nós individuais.
* **`fila.c`**: Define o ponteiro incompleto `FilaPrioridade` e esconde os membros concretos da estrutura. Implementa a inserção ordenada por prioridade mantendo a estabilidade FIFO, remoção do primeiro nó, cancelamento por ID e o mecanismo Anti-Starvation.
* **`persistencia.c`**: Módulo de armazenamento secundário. Grava e lê os dados da fila pendente e do histórico em arquivos de texto delimitados por ponto e vírgula, tratando graciosamente situações de primeira execução onde os arquivos ainda não existem.
* **`main.c`**: Ponto de entrada do programa. Conecta todos os módulos[3], gerencia os geradores de sequenciais e executa o laço de navegação e desalocação final de recursos.
---

## 4. TAD(s) e Estruturas de Dados
O projeto utiliza um **Tipo Abstrato de Dados (TAD) Opaco** para garantir o encapsulamento dos dados:

1. **`Atendimento`**: Representa os dados básicos do paciente (id, nome, prioridade, ordem_chegada, contador_espera).
2. **`FilaPrioridade` (Lista Encadeada com Prioridade)**:
   * **Inserção Ordenada:** A inserção garante que pacientes de prioridade mais alta fiquem à frente.
   * **Alocação Dinâmica:** Memória alocada sob demanda via `malloc` e liberada com `free` para evitar *memory leaks*.

---

## 5. Principais Regras do Problema e Gerenciamento
* **Níveis de Prioridade:**
  1. Urgente
  2. Prioritário
  3. Normal
* **Critério de Fila:** 
  * Pacientes com prioridades maiores têm preferência na chamada.
  * Para prioridades iguais, a ordem de chegada é estritamente mantida.

* **Memória Dinâmica (Heap):** A fila cresce dinamicamente conforme demandas por meio de `malloc`. O histórico de atendimentos utiliza `realloc` seguro. Todas as alocações contam com checagem contra retorno `NULL`. Na remoção ou destruição da fila, cada bloco é devidamente liberado via `free`.
* **Persistência em Arquivo:** Os dados são salvos em formato de texto delimitado por ponto e vírgula em `fila_pendente.txt` e `historico.txt`. Caso o arquivo não exista no primeiro arranque, o sistema trata o retorno de `fopen` e inicializa com estruturas vazias.

---

## 6. Funcionalidade Adicional da Equipe (Mecanismo Anti-Starvation)

Para evitar que atendimentos de prioridade normal fiquem aguardando indefinidamente na fila devido à chegada contínua de pessoas prioritárias (*starvation*), a equipe implementou um **mecanismo de envelhecimento**:

* Cada chamada de atendimento incrementa o contador de espera das pessoas restantes na fila.
* A função `fila_aplicar_antistarvation()` verifica se alguém atingiu o limite de ciclos (ex.: 3 ciclos de espera) e promove temporariamente seu nível de prioridade em +1, reordenando a fila de forma estável.

---

##  7. Declaração sobre o uso de Ferramentas de IA

Ferramentas de IA generativa foram consultadas pontualmente para auxílio na estruturação inicial dos cabeçalhos do TAD opaco, elaboração do Makefile e revisão sintática de código. Todo o código e arquitetura foram revisados, testados e validados pelos integrantes da equipe.
