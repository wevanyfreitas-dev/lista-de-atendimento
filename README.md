# 🏥 Sistema de Fila de Atendimento Prioritário (S1)
> Projeto desenvolvido para a disciplina de **Programação Avançada** (FACAPE - 2026.2)  
> **Professor:** Thierry Araujo  
> **Etapa Atual:** Checkpoint 2 — Núcleo Funcional (27/10/2026)

## 📌 1. Objetivo do Projeto
O objetivo do sistema é gerenciar uma **Fila de Atendimento Prioritário** para triagem de pacientes/atendimentos. O programa organiza a ordem de atendimento de acordo com a prioridade cadastrada (Alta, Média, Baixa) mantendo a estabilidade por ordem de chegada para pacientes com o mesmo nível de prioridade.
---

**Identificação da Equipe**:
1. Wévany de Andrade Freitas
2. Luciano Gomes dos Santos
3. Alexandre David de Souza Silva
4. Sauan Paranhos Sousa

## 🛠️ 3. Estrutura Principal dos Módulos
O projeto foi desenvolvido em **Linguagem C** com execução em modo texto (terminal), aplicando os conceitos de modularização e encapsulamento:

* **`interface.h`**: Contém as declarações dos tipos abstratos de dados e os protótipos de todas as funções públicas acessíveis pelo sistema.
* **`atendimento.c`**: Define a estrutura dos dados do paciente (`struct atendimento`), contendo `id`, `nome` e `prioridade`.
* **`node.c`**: Define a estrutura do nó da lista encadeada (`struct node`), responsável por armazenar o atendimento e o ponteiro para o próximo nó.
* **`fila.c`**: Implementação das operações e regras de negócio sobre a Fila Prioritária (criar, inserir ordenadamente, remover, exibir, tamanho, etc.).
* **`main.c`**: Ponto de entrada da aplicação, contendo o menu interativo via terminal que coordena as operações do sistema.

---

## 🧩 4. TAD(s) e Estruturas de Dados
O projeto utiliza um **Tipo Abstrato de Dados (TAD) Opaco** para garantir o encapsulamento dos dados:

1. **`Atendimento`**: Representa os dados básicos do paciente (ID, Nome e Nível de Prioridade).
2. **`Fila_P` (Lista Encadeada com Prioridade)**:
   * **Inserção Ordenada:** A inserção garante que pacientes de prioridade mais alta fiquem à frente.
   * **Alocação Dinâmica:** Memória alocada sob demanda via `malloc` e liberada com `free` para evitar *memory leaks*.

---

## ⚙️ 5. Principais Regras do Problema
* **Níveis de Prioridade:**
  1. Alta
  2. Média
  3. Baixa
* **Critério de Fila:** 
  * Pacientes com prioridades maiores têm preferência na chamada.
  * Para prioridades iguais, a ordem de chegada é estritamente mantida.

---

## 💾 6. Estratégia de Persistência (Em Desenvolvimento)
* A persistência em arquivos (`.txt`) está sendo iniciada para permitir a recuperação de histórico de chamadas e a gravação do estado atual da fila ao encerrar a aplicação.

---

## 🚀 7. Como Compilar e Executar

### Pré-requisitos
* Compilador C (ex: `gcc` ou `clang`).

### Compilação via Terminal
No terminal do seu sistema operacional, navegue até a pasta do projeto e rode o comando:

```bash
gcc -std=c99 -Wall main.c fila.c -o atendimento
