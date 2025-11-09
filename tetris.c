#include <stdio.h>
#include <stdlib.h>
#include <time.h>

// 1. Definição da Estrutura de Peça 🧱
// Cada peça tem um tipo (nome: char) e um identificador único (id: int).
typedef struct {
    char nome; // Tipo da peça ('I', 'O', 'T', 'L')
    int id;    // Identificador único da peça
} Peca;

// Constante para o tamanho máximo da fila
#define MAX_FILA 5

// 2. Definição da Estrutura de Fila Circular 🔄
typedef struct {
    Peca pecas[MAX_FILA]; // Array que armazena as peças
    int frente;           // Índice do primeiro elemento (cabeça da fila)
    int tras;             // Índice da posição logo após o último elemento
    int contagem;         // Número atual de elementos na fila
    int proximo_id;       // Contador para gerar IDs únicos automaticamente
} Fila;

// --- Protótipos das Funções ---

// Inicializa a fila, definindo os valores iniciais.
void inicializarFila(Fila *f); 

// Adiciona uma nova peça ao final da fila (enqueue).
int inserirPeca(Fila *f, Peca nova_peca);

// Remove a peça da frente da fila (dequeue).
Peca jogarPeca(Fila *f);

// Exibe o estado atual da fila.
void exibirFila(Fila *f);

// Gera automaticamente uma nova peça com ID e tipo aleatório.
Peca gerarPeca(int *proximo_id);

// --- Implementação das Funções ---

/**
 * @brief Inicializa a fila de peças futuras.
 * * Define os ponteiros de frente e trás, a contagem e zera o ID inicial.
 * @param f Ponteiro para a estrutura da Fila a ser inicializada.
 */
void inicializarFila(Fila *f) {
    f->frente = 0;
    f->tras = 0;
    f->contagem = 0;
    f->proximo_id = 0; // O primeiro ID será 0
    // Inicializa o gerador de números aleatórios para gerar o tipo da peça
    srand(time(NULL)); 
}

/**
 * @brief Gera uma nova peça com tipo aleatório e um ID único.
 * * O ID é gerado sequencialmente. O tipo é escolhido aleatoriamente
 * entre 'I', 'O', 'T', 'L'.
 * @param proximo_id Ponteiro para o contador de ID global.
 * @return Uma nova estrutura Peca.
 */
Peca gerarPeca(int *proximo_id) {
    Peca nova;
    char tipos[] = {'I', 'O', 'T', 'L'};
    int indice_tipo = rand() % 4; // Gera um índice aleatório entre 0 e 3

    nova.nome = tipos[indice_tipo];
    nova.id = (*proximo_id)++; // Atribui o ID atual e incrementa para o próximo
    
    return nova;
}

/**
 * @brief Adiciona uma peça ao final da fila (Enqueue).
 * * Utiliza a lógica de fila circular para inserir no índice 'tras' e
 * avança 'tras' de forma circular.
 * @param f Ponteiro para a estrutura da Fila.
 * @param nova_peca A Peca a ser inserida.
 * @return 1 se a inserção foi bem-sucedida, 0 se a fila estiver cheia.
 */
int inserirPeca(Fila *f, Peca nova_peca) {
    if (f->contagem == MAX_FILA) {
        printf("\n🛑 Fila cheia! Nao eh possivel inserir mais pecas.\n");
        return 0; // Fila cheia
    }

    // Insere a peça na posição 'tras'
    f->pecas[f->tras] = nova_peca;
    
    // Avança 'tras' de forma circular: (indice + 1) % tamanho
    f->tras = (f->tras + 1) % MAX_FILA;
    
    // Incrementa o contador de elementos
    f->contagem++;
    
    printf("\n✅ PECA INSERIDA: Tipo '%c', ID %d. (Posicao %d)\n", 
           nova_peca.nome, nova_peca.id, (f->tras - 1 + MAX_FILA) % MAX_FILA);

    return 1; // Sucesso
}

/**
 * @brief Remove a peça da frente da fila (Dequeue).
 * * Implementa a lógica FIFO (First-In, First-Out). Remove o elemento na
 * posição 'frente' e avança 'frente' de forma circular.
 * @param f Ponteiro para a estrutura da Fila.
 * @return A Peca removida. Retorna uma peça vazia se a fila estiver vazia.
 */
Peca jogarPeca(Fila *f) {
    Peca peca_removida = {'\0', -1}; // Peça de erro/vazia

    if (f->contagem == 0) {
        printf("\n❌ Fila vazia! Nao ha pecas para jogar.\n");
        return peca_removida;
    }

    // Pega a peça na posição 'frente'
    peca_removida = f->pecas[f->frente];
    
    // Avança 'frente' de forma circular: (indice + 1) % tamanho
    f->frente = (f->frente + 1) % MAX_FILA;
    
    // Decrementa o contador de elementos
    f->contagem--;
    
    printf("\n🚀 PECA JOGADA (REMOVIDA): Tipo '%c', ID %d.\n", 
           peca_removida.nome, peca_removida.id);

    return peca_removida; // Sucesso
}

/**
 * @brief Exibe o estado atual da fila de forma clara.
 * * Mostra o conteúdo da fila, o índice da frente, o índice de trás e a contagem.
 * A visualizacao respeita a ordem logica da fila, comeca pela 'frente'.
 * @param f Ponteiro para a estrutura da Fila.
 */
void exibirFila(Fila *f) {
    printf("\n--- 🧩 FILA DE PECAS FUTURAS (Tamanho: %d/%d) 🧩 ---\n", 
           f->contagem, MAX_FILA);

    if (f->contagem == 0) {
        printf("Fila vazia.\n");
        printf("-------------------------------------------------------\n");
        return;
    }

    printf("Fila: ");
    
    int i;
    int indice_atual = f->frente; // Comeca a exibir do primeiro elemento (frente)

    // Percorre todos os elementos presentes na fila
    for (i = 0; i < f->contagem; i++) {
        Peca p = f->pecas[indice_atual];
        printf("[**%c** %d]", p.nome, p.id); // Exibe o tipo e o ID
        
        // Move para o proximo indice de forma circular
        indice_atual = (indice_atual + 1) % MAX_FILA;
        
        if (i < f->contagem - 1) {
            printf(" -> ");
        }
    }
    
    printf("\n");
    printf("Visualizacao do Array (Indices internos):\n");
    printf("   (Frente: %d, Tras: %d)\n", f->frente, f->tras);

    // Visualizacao interna do array para fins de depuracao/entendimento
    printf("   [");
    for (i = 0; i < MAX_FILA; i++) {
        if (f->pecas[i].id != -1 && f->contagem > 0) {
            printf("%c %d", f->pecas[i].nome, f->pecas[i].id);
        } else {
            printf("---");
        }
        if (i < MAX_FILA - 1) {
            printf(" | ");
        }
    }
    printf("]\n");

    printf("-------------------------------------------------------\n");
}

// --- Função Principal (main) ---

int main() {
    Fila fila_futuras;
    int opcao;

    // Inicialização da fila
    inicializarFila(&fila_futuras);

    // Preenchimento inicial da fila com 5 peças, conforme requisito
    printf("--- Inicializando a Fila de Pecas ---\n");
    while (fila_futuras.contagem < MAX_FILA) {
        Peca nova = gerarPeca(&fila_futuras.proximo_id);
        // Não checa o retorno aqui, pois sabemos que a fila está vazia/com espaço
        inserirPeca(&fila_futuras, nova); 
    }
    
    exibirFila(&fila_futuras);

    // Loop principal do menu
    do {
        printf("\n### OPCOES DE ACAO ###\n");
        printf("1. Jogar peca (Dequeue)\n");
        printf("2. Inserir nova peca (Enqueue)\n");
        printf("0. Sair\n");
        printf("Escolha uma opcao: ");
        
        // Leitura da opção
        if (scanf("%d", &opcao) != 1) {
            // Trata entrada inválida (não numérica)
            while (getchar() != '\n'); // Limpa o buffer de entrada
            opcao = -1; // Garante que caia no default
        }

        switch (opcao) {
            case 1:
                // JOGAR PEÇA (REMOVER)
                jogarPeca(&fila_futuras);
                break;
            case 2:
                // INSERIR NOVA PEÇA
                // Gera a peça, reutilizando o contador de ID global da fila
                Peca nova_peca = gerarPeca(&fila_futuras.proximo_id);
                inserirPeca(&fila_futuras, nova_peca);
                break;
            case 0:
                printf("\n👋 Saindo do Tetris Stack Simulator. Ate logo!\n");
                break;
            default:
                printf("\nOpcao invalida. Por favor, tente novamente.\n");
                break;
        }

        // Exibe o estado da fila após cada ação (exceto ao sair)
        if (opcao != 0) {
            exibirFila(&fila_futuras);
        }
        
    } while (opcao != 0);

    return 0;
}