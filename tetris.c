#include <stdio.h>
#include <stdlib.h>
#include <time.h>

// --- Definições de Constantes ---
#define MAX_FILA 5   // Capacidade máxima da Fila de peças futuras
#define MAX_PILHA 3  // Capacidade máxima da Pilha de peças de reserva

// --- 1. Estrutura da Peça ---
typedef struct {
    char nome; // Tipo da peça ('I', 'O', 'T', 'L')
    int id;    // Identificador único da peça
} Peca;

// --- 2. Estrutura da Fila Circular ---
typedef struct {
    Peca pecas[MAX_FILA];
    int frente;   // Índice do primeiro elemento
    int tras;     // Índice da posição logo após o último elemento
    int contagem; // Número atual de elementos
    int proximo_id; // Contador para gerar IDs únicos (global para Fila e Pilha)
} Fila;

// --- 3. Estrutura da Pilha Linear ---
typedef struct {
    Peca pecas[MAX_PILHA];
    int topo; // Índice do topo (o último elemento inserido)
} Pilha;

// --- Protótipos das Funções ---

// Funções de Inicialização e Geração
void inicializarFila(Fila *f);
void inicializarPilha(Pilha *p);
Peca gerarPeca(int *proximo_id);

// Funções da Fila (FIFO)
int inserirFila(Fila *f, Peca nova_peca);
Peca removerFila(Fila *f);
void exibirFila(Fila *f);

// Funções da Pilha (LIFO)
int empilhar(Pilha *p, Peca peca);
Peca desempilhar(Pilha *p);
void exibirPilha(Pilha *p);

// Funções de Gerenciamento
void jogarPecaAcao(Fila *f, Pilha *p);
void reservarPecaAcao(Fila *f, Pilha *p);
void usarPecaReservadaAcao(Fila *f, Pilha *p);

// --- Implementação das Funções Auxiliares ---

/**
 * @brief Inicializa a fila.
 */
void inicializarFila(Fila *f) {
    f->frente = 0;
    f->tras = 0;
    f->contagem = 0;
    f->proximo_id = 0;
    srand(time(NULL)); 
}

/**
 * @brief Inicializa a pilha, definindo o topo como vazio (-1).
 */
void inicializarPilha(Pilha *p) {
    p->topo = -1; // -1 indica que a pilha está vazia
}

/**
 * @brief Gera uma nova peça com ID único e tipo aleatório.
 */
Peca gerarPeca(int *proximo_id) {
    Peca nova;
    char tipos[] = {'I', 'O', 'T', 'L'};
    int indice_tipo = rand() % 4;

    nova.nome = tipos[indice_tipo];
    nova.id = (*proximo_id)++;
    
    return nova;
}

// --- Implementação das Funções da Fila (FIFO) ---

/**
 * @brief Adiciona uma peça ao final da fila (Enqueue).
 * * Assumimos que esta função só será chamada se houver espaço (ou após uma remoção),
 * pois a regra do jogo é manter a fila sempre cheia.
 */
int inserirFila(Fila *f, Peca nova_peca) {
    if (f->contagem == MAX_FILA) {
        // Esta condição não deve ser atingida devido à regra do jogo, 
        // mas é mantida por segurança.
        return 0; 
    }

    f->pecas[f->tras] = nova_peca;
    f->tras = (f->tras + 1) % MAX_FILA;
    f->contagem++;
    
    printf("\n   > Nova peca gerada e adicionada a FILA: Tipo '%c', ID %d.\n", 
           nova_peca.nome, nova_peca.id);

    return 1;
}

/**
 * @brief Remove a peça da frente da fila (Dequeue).
 */
Peca removerFila(Fila *f) {
    Peca peca_removida = {'\0', -1}; 

    if (f->contagem == 0) {
        return peca_removida;
    }

    peca_removida = f->pecas[f->frente];
    f->frente = (f->frente + 1) % MAX_FILA;
    f->contagem--;
    
    return peca_removida;
}

/**
 * @brief Exibe o estado atual da fila, respeitando a ordem FIFO.
 */
void exibirFila(Fila *f) {
    printf("⭐ FILA de pecas (Frente -> Tras) [%d/%d]: ", f->contagem, MAX_FILA);

    if (f->contagem == 0) {
        printf("Vazia.\n");
        return;
    }

    int i;
    int indice_atual = f->frente; 

    for (i = 0; i < f->contagem; i++) {
        Peca p = f->pecas[indice_atual];
        printf("[**%c** %d]", p.nome, p.id);
        
        indice_atual = (indice_atual + 1) % MAX_FILA;
    }
    printf("\n");
}

// --- Implementação das Funções da Pilha (LIFO) ---

/**
 * @brief Adiciona uma peça ao topo da pilha (Push).
 */
int empilhar(Pilha *p, Peca peca) {
    if (p->topo == MAX_PILHA - 1) {
        return 0; // Pilha cheia
    }

    p->topo++;
    p->pecas[p->topo] = peca;
    
    return 1; // Sucesso
}

/**
 * @brief Remove a peça do topo da pilha (Pop).
 */
Peca desempilhar(Pilha *p) {
    Peca peca_removida = {'\0', -1};

    if (p->topo == -1) {
        return peca_removida; // Pilha vazia
    }

    peca_removida = p->pecas[p->topo];
    p->topo--;
    
    return peca_removida;
}

/**
 * @brief Exibe o estado atual da pilha, respeitando a ordem LIFO.
 */
void exibirPilha(Pilha *p) {
    int contagem_pilha = p->topo + 1;
    printf("📦 PILHA de reserva (Topo -> Base) [%d/%d]: ", contagem_pilha, MAX_PILHA);

    if (contagem_pilha == 0) {
        printf("Vazia.\n");
        return;
    }

    // A pilha é exibida do topo para a base
    for (int i = p->topo; i >= 0; i--) {
        Peca peca = p->pecas[i];
        printf("[**%c** %d]", peca.nome, peca.id);
        if (i > 0) {
             printf(" ");
        }
    }
    printf("\n");
}

// --- Implementação das Ações de Jogo ---

/**
 * @brief Simula a ação de "Jogar uma peça".
 * * Remove a peça da frente da fila.
 * * Gera e insere uma nova peça no final da fila.
 */
void jogarPecaAcao(Fila *f, Pilha *p) {
    if (f->contagem == 0) {
        printf("\n❌ A Fila esta vazia! Nao ha pecas para jogar.\n");
        return;
    }
    
    Peca peca_jogada = removerFila(f);
    printf("\n🚀 Acao 1: PECA JOGADA. Tipo '%c', ID %d.\n", 
           peca_jogada.nome, peca_jogada.id);

    // Requisito: A cada ação, uma nova peça é gerada e adicionada à fila.
    Peca nova = gerarPeca(&(f->proximo_id));
    inserirFila(f, nova);
}

/**
 * @brief Simula a ação de "Reservar uma peça".
 * * Move a peça da frente da fila para o topo da pilha.
 * * Gera e insere uma nova peça no final da fila.
 */
void reservarPecaAcao(Fila *f, Pilha *p) {
    if (f->contagem == 0) {
        printf("\n❌ A Fila esta vazia! Nao ha pecas para reservar.\n");
        return;
    }

    Peca peca_reservada = removerFila(f);
    
    if (empilhar(p, peca_reservada)) {
        printf("\n✅ Acao 2: PECA RESERVADA. Tipo '%c', ID %d (Movida da Fila para a Pilha).\n", 
               peca_reservada.nome, peca_reservada.id);
        
        // Requisito: A cada ação, uma nova peça é gerada e adicionada à fila.
        Peca nova = gerarPeca(&(f->proximo_id));
        inserirFila(f, nova);

    } else {
        // Se a pilha estiver cheia, a peça volta para a frente da fila
        // *Simulamos* o retorno, mas neste modelo, a remoção da fila é consumida
        // e uma nova peça é gerada para substituir.
        // Como simplificação, apenas reportamos o erro e geramos a nova peça.
        printf("\n🛑 Pilha de reserva cheia! Nao foi possivel reservar a peca.\n");
        // A peça removida da fila foi perdida e uma nova será inserida
        Peca nova = gerarPeca(&(f->proximo_id));
        inserirFila(f, nova);
    }
}

/**
 * @brief Simula a ação de "Usar uma peça reservada".
 * * Remove a peça do topo da pilha.
 * * Gera e insere uma nova peça no final da fila.
 */
void usarPecaReservadaAcao(Fila *f, Pilha *p) {
    Peca peca_usada = desempilhar(p);
    
    if (peca_usada.id != -1) {
        printf("\n⬇️ Acao 3: PECA RESERVADA UTILIZADA. Tipo '%c', ID %d (Removida da Pilha).\n", 
               peca_usada.nome, peca_usada.id);

        // Requisito: A cada ação, uma nova peça é gerada e adicionada à fila.
        Peca nova = gerarPeca(&(f->proximo_id));
        inserirFila(f, nova);

    } else {
        printf("\n❌ A Pilha de reserva esta vazia! Nao ha pecas para usar.\n");
    }
}

// --- Função Principal (main) ---

int main() {
    Fila fila_futuras;
    Pilha pilha_reserva;
    int opcao;

    // Inicialização das estruturas
    inicializarFila(&fila_futuras);
    inicializarPilha(&pilha_reserva);

    // Preenchimento inicial da fila com 5 peças
    printf("--- Inicializando o Gerenciador de Pecas ---\n");
    while (fila_futuras.contagem < MAX_FILA) {
        Peca nova = gerarPeca(&fila_futuras.proximo_id);
        inserirFila(&fila_futuras, nova); 
    }
    
    // Loop principal do menu
    do {
        printf("\n=======================================================\n");
        printf("         🎮 TETRIS STACK - ESTADO ATUAL\n");
        printf("=======================================================\n");
        exibirFila(&fila_futuras);
        exibirPilha(&pilha_reserva);
        printf("-------------------------------------------------------\n");
        
        printf("\n### OPCOES DE ACAO ###\n");
        printf("1. Jogar peca (Dequeue da Fila)\n");
        printf("2. Reservar peca (Fila -> Pilha)\n");
        printf("3. Usar peca reservada (Pop da Pilha)\n");
        printf("0. Sair\n");
        printf("Escolha uma opcao: ");
        
        if (scanf("%d", &opcao) != 1) {
            while (getchar() != '\n');
            opcao = -1;
        }

        switch (opcao) {
            case 1:
                jogarPecaAcao(&fila_futuras, &pilha_reserva);
                break;
            case 2:
                reservarPecaAcao(&fila_futuras, &pilha_reserva);
                break;
            case 3:
                usarPecaReservadaAcao(&fila_futuras, &pilha_reserva);
                break;
            case 0:
                printf("\n👋 Saindo do Tetris Stack Simulator. Ate logo!\n");
                break;
            default:
                printf("\nOpcao invalida. Por favor, tente novamente.\n");
                break;
        }
        
    } while (opcao != 0);

    return 0;
}