## 🎮 Tetris Stack Manager - EM C

Este é um programa em C que simula o sistema de gerenciamento de peças do jogo fictício **Tetris Stack**, utilizando as estruturas de dados fundamentais de **Fila Circular** e **Pilha Linear** em conjunto para oferecer um gerenciamento de recursos estratégico.

---

## ⚙️ Conceitos Trabalhados

O projeto implementa e integra duas estruturas de dados essenciais:

1.  **Fila Circular de Peças Futuras (FIFO):**
    * **Capacidade:** 5 peças.
    * **Princípio:** First-In, First-Out (O primeiro a entrar é o primeiro a sair).
    * **Implementação:** Utiliza ponteiros frente e tras para manipulação eficiente em um *array*, com lógica circular ( % ).
    * **Regra do Jogo:** A fila é mantida **sempre cheia** através da geração automática de uma nova peça após qualquer remoção ou envio para a Pilha.

2.  **Pilha Linear de Reserva (LIFO):**
    * **Capacidade:** 3 peças.
    * **Princípio:** Last-In, First-Out (O último a entrar é o primeiro a sair).
    * **Implementação:** Utiliza o ponteiro topo para gerenciamento LIFO.

---

## 🧩 Funcionalidades Implementadas

O programa oferece um menu interativo com as seguintes ações estratégicas:

| Código | Ação | Descrição |
| :----: | :--- | :--- |
| **1** | **Jogar Peça** | Remove a peça da **frente** da Fila (Dequeue) e gera uma nova peça para repor o espaço. |
| **2** | **Reservar Peça** | Move a peça da **frente** da Fila para o **topo** da Pilha (Push), se houver espaço. Repõe a Fila. |
| **3** | **Usar Peça Reservada** | Remove a peça do **topo** da Pilha (Pop), simulando seu uso. Repõe a Fila. |
| **4** | **Trocar Peça Única** | Realiza um *swap* direto entre a peça da **frente** da Fila e a peça do **topo** da Pilha. |
| **5** | **Troca Múltipla** | Realiza um *swap* em bloco das **3 primeiras peças** da Fila com as **3 peças** da Pilha, exigindo que ambas estruturas tenham capacidade total. |
| **0** | **Sair** | Encerra o programa. |

---

## 🛠️ Como Compilar e Executar

Para rodar este programa em seu ambiente:

1.  **Salve** o código-fonte C em um arquivo (ex: tetris_manager.c).
2.  **Compile** usando um compilador C (como GCC) no terminal:
    ```bash
    gcc tetris_manager.c -o tetris_manager
    ```
3.  **Execute** o programa:
    ```bash
    ./tetris_manager
    ```

---

## 🧱 Estruturas de Dados (structs)

O código utiliza duas structs principais:

### Peca

Define o objeto base do sistema.

| Atributo | Tipo | Descrição |
| :------: | :--: | :--- |
| **nome** | `char` | Tipo da peça ('I', 'O', 'T', 'L'), gerado aleatoriamente. |
| **id** | `int` | Número sequencial único para identificar a ordem de criação. |

### Fila e Pilha

Gerenciam as coleções de peças.

| Estrutura | Ponteiros de Controle | Aritmética Chave |
| :-------: | :-------------------: | :---------------: |
| **Fila** | frente, tras, contagem | Módulo (% MAX_FILA) |
| **Pilha** | topo | Incremento/Decremento |


++++++++++++++++++++++++++++++++++
---
# Desafio Tetris Stack - Controle de Peças com Estruturas de Dados
---
Bem-vindo ao desafio **"Tetris Stack"**! Neste jogo inspirado nas mecânicas clássicas de montagem de peças, o jogador deve organizar, reservar e manipular peças em tempo real. Para isso, você, como programador, será responsável por implementar as estruturas de controle que regem a lógica das peças.

A empresa **ByteBros**, especializada em jogos educacionais de lógica e programação, contratou você para desenvolver o sistema de gerenciamento de peças, utilizando estruturas como **fila circular** e **pilha**.

O desafio está dividido em três níveis: **Novato**, **Aventureiro** e **Mestre**, com cada nível adicionando mais complexidade ao anterior.  
**Você deve escolher qual desafio deseja realizar.**

🚨 **Atenção:** O nível Novato foca apenas na fila de peças, usando conceitos básicos de structs, arrays e modularização.

## 🎮 Nível Novato: Fila de Peças Futuras

No nível Novato, você criará o sistema inicial de controle das peças futuras do jogo Tetris Stack. As peças possuem um **nome** (representando o tipo, como 'I', 'O', 'T', 'L') e um **id** exclusivo (identificador numérico).

🚩 **Objetivo:** Criar um programa em C que simula uma **fila circular** de 5 peças com as seguintes funcionalidades:

*   Visualizar a fila atual
*   Jogar (remover) a peça da frente
*   Inserir automaticamente uma nova peça no final da fila

⚙️ **Funcionalidades do Sistema:**

*   Inicializar a fila com 5 peças geradas automaticamente.
*   Permitir que o usuário:
    *   Jogue uma peça (dequeue)
    *   Insira uma nova peça (enqueue)
    *   Visualize o estado atual da fila
*   Manter a fila circular, reaproveitando o espaço.

📥 **Entrada** e 📤 **Saída de Dados:**

*   O programa utiliza menus via terminal.
*   A cada ação, o estado atualizado da fila é exibido com `printf`.

**Simplificações para o Nível Novato:**

*   Trabalhe **apenas com a fila**.
*   A fila deve conter **exatamente 5 elementos**.
*   Use uma função `gerarPeca()` para criar automaticamente novas peças.
*   Utilize structs e arrays. Não implemente pilha.

## 🛡️ Nível Aventureiro: Reserva de Peças com Pilha

No nível Aventureiro, você irá expandir o sistema com uma **pilha de reserva de peças**, que permite ao jogador guardar peças para uso posterior.

🆕 **Diferença em relação ao Nível Novato:**

*   Introdução da **pilha linear** para reservar peças.
*   A fila permanece sempre cheia com 5 peças.

⚙️ **Funcionalidades do Sistema:**

*   Além das opções anteriores, o usuário pode:
    *   Reservar a peça da frente da fila (push)
    *   Usar uma peça reservada (pop)
*   A fila continua funcionando com inserção automática.
*   A pilha tem **capacidade máxima de 3 peças**.

📥 **Entrada** e 📤 **Saída de Dados:**

*   Menu com 4 opções:
    * `1` - Jogar peça
    * `2` - Reservar peça
    * `3` - Usar peça reservada
    * `0` - Sair
*   O estado da fila e da pilha é exibido após cada ação.

**Simplificações para o Nível Intermediário:**

*   A pilha não permite escolha da posição.
*   O jogador **não escolhe o tipo da peça** — todas são geradas automaticamente.
*   Não há comparação nem troca direta entre as estruturas.

## 🏆 Nível Mestre: Integração Total com Estratégia

No nível Mestre, você implementará uma **integração complexa** entre a fila e a pilha, simulando funcionalidades avançadas como **troca**, **desfazer** e **inversão de peças**.

🆕 **Diferença em relação ao Nível Aventureiro:**

*   Operações mais complexas e estratégicas entre as estruturas.
*   Manipulação reversível do estado das peças.

⚙️ **Funcionalidades do Sistema:**

*   Menu com múltiplas ações:
    * `1` - Jogar peça
    * `2` - Reservar peça
    * `3` - Usar peça reservada
    * `4` - Trocar peça do topo da pilha com a da frente da fila
    * `5` - Desfazer última jogada
    * `6` - Inverter fila com pilha
    * `0` - Sair
*   Controle de fila circular e pilha de reserva com atualização a cada ação.

📥 **Entrada** e 📤 **Saída de Dados:**

*   Mesmo estilo dos níveis anteriores.
*   Agora exige controle total do fluxo e da memória entre as estruturas.

**Observações:**

*   Cada operação deve ser segura e manter a integridade dos dados.
*   A complexidade exige modularização clara e funções bem separadas.

## 🏁 Conclusão

Ao concluir qualquer um dos níveis, você terá exercitado conceitos fundamentais de estrutura de dados, como **fila circular** e **pilha**, em um contexto prático de desenvolvimento de jogos.

Boa sorte e divirta-se programando!

Equipe de Ensino - ByteBros

