#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define TAM 5 // tamanho fixo da fila

// ------------------- STRUCT -------------------
typedef struct {
    char nome;  // tipo da peça ('I', 'O', 'T', 'L')
    int id;     // identificador único
} Peca;

typedef struct {
    Peca fila[TAM];
    int inicio;
    int fim;
    int qtd;
} Fila;

// ------------------- FUNÇÕES DA FILA -------------------

// Inicializa a fila vazia
void inicializarFila(Fila *f) {
    f->inicio = 0;
    f->fim = -1;
    f->qtd = 0;
}

// Verifica se a fila está cheia
int filaCheia(Fila *f) {
    return (f->qtd == TAM);
}

// Verifica se a fila está vazia
int filaVazia(Fila *f) {
    return (f->qtd == 0);
}

// Gera uma peça aleatória (com tipo e id)
Peca gerarPeca(int id) {
    Peca nova;
    char tipos[] = {'I', 'O', 'T', 'L'};
    nova.nome = tipos[rand() % 4];
    nova.id = id;
    return nova;
}

// Insere nova peça ao final da fila (enqueue)
void enqueue(Fila *f, Peca nova) {
    if (filaCheia(f)) {
        printf("\n Fila cheia! Não é possível adicionar nova peça.\n");
        return;
    }
    f->fim = (f->fim + 1) % TAM;
    f->fila[f->fim] = nova;
    f->qtd++;
    printf("\n Peça [%c %d] adicionada à fila!\n", nova.nome, nova.id);
}

// Remove uma peça do início da fila (dequeue)
void dequeue(Fila *f) {
    if (filaVazia(f)) {
        printf("\n Fila vazia! Nenhuma peça para jogar.\n");
        return;
    }
    Peca removida = f->fila[f->inicio];
    f->inicio = (f->inicio + 1) % TAM;
    f->qtd--;
    printf("\n Jogando peça [%c %d]...\n", removida.nome, removida.id);
}

// Exibe o estado atual da fila
void exibirFila(Fila *f) {
    if (filaVazia(f)) {
        printf("\n(Fila vazia)\n");
        return;
    }

    printf("\n=== Fila de Peças ===\n");
    int i, pos;
    for (i = 0; i < f->qtd; i++) {
        pos = (f->inicio + i) % TAM;
        printf("[%c %d] ", f->fila[pos].nome, f->fila[pos].id);
    }
    printf("\n");
}

// ------------------- FUNÇÃO PRINCIPAL -------------------
int main() {
    srand(time(NULL));
    Fila fila;
    inicializarFila(&fila);

    int opcao;
    int contadorIDs = 0;

    // Inicializa a fila com 5 peças
    for (int i = 0; i < TAM; i++) {
        enqueue(&fila, gerarPeca(contadorIDs++));
    }

    // Menu principal
    do {
        exibirFila(&fila);
        printf("\nOpções:\n");
        printf("1 - Jogar peça (dequeue)\n");
        printf("2 - Inserir nova peça (enqueue)\n");
        printf("0 - Sair\n");
        printf("Escolha: ");
        scanf("%d", &opcao);

        switch (opcao) {
            case 1:
                dequeue(&fila);
                break;
            case 2:
                enqueue(&fila, gerarPeca(contadorIDs++));
                break;
            case 0:
                printf("\nEncerrando o programa\n");
                break;
            default:
                printf("\nOpção inválida!\n");
        }
    } while (opcao != 0);

    return 0;
}
