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
    int proximo_id; // Contador para gerar IDs únicos (global)
} Fila;

// --- 3. Estrutura da Pilha Linear ---
typedef struct {
    Peca pecas[MAX_PILHA];
    int topo; // Índice do topo (o último elemento inserido)
} Pilha;

// --- Protótipos das Funções ---

// Funções Auxiliares e de Inicialização
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
int getContagemPilha(Pilha *p); // Novo auxiliar para Pilha

// Funções de Ações Estratégicas
void jogarPecaAcao(Fila *f);
void reservarPecaAcao(Fila *f, Pilha *p);
void usarPecaReservadaAcao(Fila *f, Pilha *p);
void trocarPecaUnica(Fila *f, Pilha *p); // Novo
void trocarMultipla(Fila *f, Pilha *p);  // Novo

// --- Implementação das Funções Auxiliares ---

void inicializarFila(Fila *f) {
    f->frente = 0;
    f->tras = 0;
    f->contagem = 0;
    f->proximo_id = 0;
    srand(time(NULL)); 
}

void inicializarPilha(Pilha *p) {
    p->topo = -1;
}

Peca gerarPeca(int *proximo_id) {
    Peca nova;
    char tipos[] = {'I', 'O', 'T', 'L'};
    int indice_tipo = rand() % 4;

    nova.nome = tipos[indice_tipo];
    nova.id = (*proximo_id)++;
    
    return nova;
}

// --- Implementação das Funções da Fila (FIFO) ---

int inserirFila(Fila *f, Peca nova_peca) {
    if (f->contagem == MAX_FILA) {
        return 0; 
    }

    f->pecas[f->tras] = nova_peca;
    f->tras = (f->tras + 1) % MAX_FILA;
    f->contagem++;
    
    printf("   > Nova peca gerada e adicionada a FILA: Tipo '%c', ID %d.\n", 
           nova_peca.nome, nova_peca.id);

    return 1;
}

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

void exibirFila(Fila *f) {
    printf("⭐ FILA de pecas (Frente -> Tras) [%d/%d]: ", f->contagem, MAX_FILA);

    if (f->contagem == 0) {
        printf("Vazia.\n");
        return;
    }

    int indice_atual = f->frente; 
    for (int i = 0; i < f->contagem; i++) {
        Peca p = f->pecas[indice_atual];
        printf("[**%c** %d]", p.nome, p.id);
        
        indice_atual = (indice_atual + 1) % MAX_FILA;
    }
    printf("\n");
}

// --- Implementação das Funções da Pilha (LIFO) ---

int empilhar(Pilha *p, Peca peca) {
    if (p->topo == MAX_PILHA - 1) {
        return 0; // Pilha cheia
    }

    p->topo++;
    p->pecas[p->topo] = peca;
    
    return 1; // Sucesso
}

Peca desempilhar(Pilha *p) {
    Peca peca_removida = {'\0', -1};

    if (p->topo == -1) {
        return peca_removida; // Pilha vazia
    }

    peca_removida = p->pecas[p->topo];
    p->topo--;
    
    return peca_removida;
}

int getContagemPilha(Pilha *p) {
    return p->topo + 1;
}

void exibirPilha(Pilha *p) {
    int contagem_pilha = getContagemPilha(p);
    printf("📦 PILHA de reserva (Topo -> Base) [%d/%d]: ", contagem_pilha, MAX_PILHA);

    if (contagem_pilha == 0) {
        printf("Vazia.\n");
        return;
    }

    for (int i = p->topo; i >= 0; i--) {
        Peca peca = p->pecas[i];
        printf("[**%c** %d]", peca.nome, peca.id);
        if (i > 0) {
             printf(" ");
        }
    }
    printf("\n");
}

// --- Implementação das Ações de Jogo (incluindo as de Mestre) ---

void reporFila(Fila *f) {
    // Repõe uma peça para manter a fila cheia após uma remoção
    if (f->contagem < MAX_FILA) {
        Peca nova = gerarPeca(&(f->proximo_id));
        inserirFila(f, nova);
    }
}

void jogarPecaAcao(Fila *f) {
    if (f->contagem == 0) {
        printf("\n❌ A Fila esta vazia! Nao ha pecas para jogar.\n");
        return;
    }
    
    Peca peca_jogada = removerFila(f);
    printf("\n🚀 Acao 1: PECA JOGADA. Tipo '%c', ID %d.\n", 
           peca_jogada.nome, peca_jogada.id);

    reporFila(f);
}

void reservarPecaAcao(Fila *f, Pilha *p) {
    if (f->contagem == 0) {
        printf("\n❌ A Fila esta vazia! Nao ha pecas para reservar.\n");
        return;
    }
    if (getContagemPilha(p) == MAX_PILHA) {
        printf("\n🛑 Pilha de reserva cheia! Nao foi possivel reservar a peca.\n");
        return;
    }

    Peca peca_reservada = removerFila(f);
    
    if (empilhar(p, peca_reservada)) {
        printf("\n✅ Acao 2: PECA RESERVADA. Tipo '%c', ID %d (Movida da Fila para a Pilha).\n", 
               peca_reservada.nome, peca_reservada.id);
        reporFila(f);
    } 
    // Se a peça não empilhou, não era para ter removido, mas o fluxo do jogo é:
    // 1. Tentar mover. 2. Se a pilha está cheia, avisar e não mover. 
    // Como a checagem é feita antes, garantimos que se chegou aqui, a pilha tinha espaço.
}

void usarPecaReservadaAcao(Fila *f, Pilha *p) {
    Peca peca_usada = desempilhar(p);
    
    if (peca_usada.id != -1) {
        printf("\n⬇️ Acao 3: PECA RESERVADA UTILIZADA. Tipo '%c', ID %d (Removida da Pilha).\n", 
               peca_usada.nome, peca_usada.id);
        reporFila(f);
    } else {
        printf("\n❌ A Pilha de reserva esta vazia! Nao ha pecas para usar.\n");
    }
}

/**
 * @brief Troca a peça da frente da fila com a peça do topo da pilha.
 */
void trocarPecaUnica(Fila *f, Pilha *p) {
    if (f->contagem == 0) {
        printf("\n❌ Fila vazia! Nao eh possivel realizar a troca.\n");
        return;
    }
    if (getContagemPilha(p) == 0) {
        printf("\n❌ Pilha vazia! Nao eh possivel realizar a troca.\n");
        return;
    }
    
    // 1. Pega a peça da frente da fila (sem remover)
    Peca peca_fila = f->pecas[f->frente];
    
    // 2. Pega a peça do topo da pilha (sem remover)
    Peca peca_pilha = p->pecas[p->topo];
    
    // 3. Realiza a troca: move Pilha -> Fila
    f->pecas[f->frente] = peca_pilha;
    
    // 4. Realiza a troca: move Fila -> Pilha
    p->pecas[p->topo] = peca_fila;

    printf("\n🔄 Acao 4: TROCA UNICA realizada.\n");
    printf("   > Fila agora com: Tipo '%c', ID %d.\n", peca_pilha.nome, peca_pilha.id);
    printf("   > Pilha agora com: Tipo '%c', ID %d.\n", peca_fila.nome, peca_fila.id);
}

/**
 * @brief Troca as 3 primeiras peças da fila com as 3 peças da pilha.
 * * Requer que ambas as estruturas tenham pelo menos 3 elementos.
 */
void trocarMultipla(Fila *f, Pilha *p) {
    const int NUM_TROCA = 3;

    if (f->contagem < NUM_TROCA || getContagemPilha(p) < NUM_TROCA) {
        printf("\n🛑 Troca multipla FALHOU! Ambas as estruturas devem ter pelo menos %d pecas (Fila: %d, Pilha: %d).\n", 
               NUM_TROCA, f->contagem, getContagemPilha(p));
        return;
    }

    Peca temp;
    printf("\n🔀 Acao 5: TROCA MULTIPLA (3 pecas) realizada.\n");

    for (int i = 0; i < NUM_TROCA; i++) {
        // Índice na fila, começando da frente
        int idx_fila = (f->frente + i) % MAX_FILA;
        
        // Índice na pilha, do topo para baixo (LIFO)
        int idx_pilha = p->topo - i; 

        // 1. Salva a peça da Fila
        temp = f->pecas[idx_fila];
        
        // 2. Move a peça da Pilha para a Fila
        f->pecas[idx_fila] = p->pecas[idx_pilha];
        
        // 3. Move a peça da Fila para a Pilha
        p->pecas[idx_pilha] = temp;

        printf("   > Troca %d: Fila[%d] <-> Pilha[%d]\n", i + 1, idx_fila, idx_pilha);
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
    printf("--- Inicializando o Gerenciador de Pecas (Nivel Mestre) ---\n");
    while (fila_futuras.contagem < MAX_FILA) {
        Peca nova = gerarPeca(&fila_futuras.proximo_id);
        // insercao sem o feedback de repor fila
        fila_futuras.pecas[fila_futuras.tras] = nova;
        fila_futuras.tras = (fila_futuras.tras + 1) % MAX_FILA;
        fila_futuras.contagem++;
        printf("   [Inicial] Peça Tipo '%c', ID %d adicionada.\n", nova.nome, nova.id);
    }
    
    // Loop principal do menu
    do {
        printf("\n=======================================================\n");
        printf("         🎮 TETRIS STACK - ESTADO ATUAL\n");
        printf("=======================================================\n");
        exibirFila(&fila_futuras);
        exibirPilha(&pilha_reserva);
        printf("-------------------------------------------------------\n");
        
        printf("\n### OPCOES DE ACAO (NIVEL MESTRE) ###\n");
        printf("1. Jogar peca (Dequeue da Fila)\n");
        printf("2. Reservar peca (Fila -> Pilha)\n");
        printf("3. Usar peca reservada (Pop da Pilha)\n");
        printf("4. Trocar peca da frente da fila com o topo da pilha\n");
        printf("5. Trocar os 3 primeiros da fila com as 3 da pilha\n");
        printf("0. Sair\n");
        printf("Escolha uma opcao: ");
        
        if (scanf("%d", &opcao) != 1) {
            while (getchar() != '\n');
            opcao = -1;
        }

        switch (opcao) {
            case 1:
                jogarPecaAcao(&fila_futuras);
                break;
            case 2:
                reservarPecaAcao(&fila_futuras, &pilha_reserva);
                break;
            case 3:
                usarPecaReservadaAcao(&fila_futuras, &pilha_reserva);
                break;
            case 4:
                trocarPecaUnica(&fila_futuras, &pilha_reserva);
                break;
            case 5:
                trocarMultipla(&fila_futuras, &pilha_reserva);
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