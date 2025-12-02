#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Define o tamanho máximo do nome da sala
#define MAX_NOME 50

// Estrutura para representar um cômodo (nó da árvore binária)
typedef struct Comodo {
    char nome[MAX_NOME];
    struct Comodo *esquerda; // Caminho para a esquerda
    struct Comodo *direita;  // Caminho para a direita
} Comodo;

/**
 * @brief Cria dinamicamente um novo cômodo (nó) com o nome especificado.
 * 
 * @param nome O nome da sala.
 * @return Um ponteiro para o novo cômodo criado.
 */
Comodo* criarSala(const char* nome) {
    Comodo* novoComodo = (Comodo*)malloc(sizeof(Comodo));
    if (novoComodo == NULL) {
        printf("Erro de alocação de memória!\n");
        exit(1);
    }
    strncpy(novoComodo->nome, nome, MAX_NOME - 1);
    novoComodo->nome[MAX_NOME - 1] = '\0'; // Garante terminação nula
    novoComodo->esquerda = NULL;
    novoComodo->direita = NULL;
    return novoComodo;
}

/**
 * @brief Permite a navegação do jogador pela árvore (mapa da mansão).
 * A exploração continua até o jogador alcançar um nó-folha.
 */
void explorarSalas(Comodo* atual) {
    char escolha;

    while (atual != NULL) {
        printf("\n--- Você está no cômodo %s ---\n", atual->nome);

        // Verifica se é um nó-folha (sem caminhos adicionais)
        if (atual->esquerda == NULL && atual->direita == NULL) {
            printf("\nVocê chegou a um beco sem saída! A exploração terminou.\n\n");
            break;
        }

        // Oferece opções de navegação com base nos caminhos disponíveis
        printf("Opções de caminho:\n");
        if (atual->esquerda != NULL) {
            printf("  [e] Esquerda\n");
        }
        if (atual->direita != NULL) {
            printf("  [d] Direita\n");
        }
        printf("  [s] Sair\n");
        printf("\nEscolha seu caminho: ");
        scanf(" %c", &escolha); // O espaço antes de %c consome newlines pendentes

        // Processa a escolha do usuário
        
        if (escolha == 'e' || escolha == 'E') { // parametrizando para o código aceitar letra minúscula ou maiúscula
            if (atual->esquerda != NULL) {
                atual = atual->esquerda;
            } else {
                printf("\nCaminho inválido. Tente novamente.\n");
            }
        } else if (escolha == 'd' || escolha == 'D') {
            if (atual->direita != NULL) {
                atual = atual->direita;
            } else {
                printf("\nCaminho inválido. Tente novamente.\n");
            }
        } else if (escolha == 's' || escolha == 'S') {
            printf("\nSaindo da Mansão. Até mais!\n\n");
            break;
        } else {
            printf("\nOpção inválida. Tente novamente.\n");
        }
    }
}

/**
 * @brief Libera a memória alocada para toda a árvore de cômodos.
 * 
 * @param raiz O nó raiz da árvore a ser liberada.
 */
void liberarMemoria(Comodo* raiz) {
    if (raiz == NULL) {
        return;
    }
    liberarMemoria(raiz->esquerda);
    liberarMemoria(raiz->direita);
    free(raiz);
}

/**
 * @brief Função principal que monta o mapa inicial da mansão e dá início à exploração.
 */
int main() {
    // Montagem manual da árvore binária (o mapa da mansão)
    
    // Nível 0 (Raiz)
    Comodo* hallEntrada = criarSala("Hall de Entrada");

    // Nível 1
    Comodo* salaEstar = criarSala("Sala de Estar");
    Comodo* cozinha = criarSala("Cozinha");
    hallEntrada->esquerda = salaEstar;
    hallEntrada->direita = cozinha;

    // Nível 2
    Comodo* escritorio = criarSala("Escritório");
    Comodo* jardimInverno = criarSala("Jardim de Inverno");
    salaEstar->esquerda = escritorio;
    salaEstar->direita = jardimInverno;

    Comodo* dispensa = criarSala("Dispensa");
    Comodo* salaJantar = criarSala("Sala de Jantar");
    cozinha->esquerda = dispensa;
    cozinha->direita = salaJantar;
    
    // Nível 3 (Nós-folha)
    // Escritorio -> Folha
    // JardimInverno -> Folha
    // Dispensa -> Folha
    Comodo* garagem = criarSala("Garagem (Saída)");
    salaJantar->direita = garagem; // Caminho apenas para a direita

    printf("----Bem-vindo à Mansão!---\n");
    printf("Explore os cômodos escolhendo esquerda (e) ou direita (d).\n");

    // Inicia a exploração a partir do Hall de Entrada
    explorarSalas(hallEntrada);

    // Limpeza da memória alocada
    liberarMemoria(hallEntrada);

    return 0;
}

