//DOM_BJPS_REQ09 - Projeto Dominó LP2026
//26/08/2026
//Bruna, João Pedro Freitas Vilar, Pedru Gama, Samira

#include <stdio.h>

#define TOTAL_PECAS 28

typedef struct {
    int lado_a;
    int lado_b;
} PecaDomino;

typedef struct {
    PecaDomino pecas[TOTAL_PECAS]; // pecas colocadas na mesa, na ordem em que foram jogadas
    int qtd_pecas;                 // quantidade de pecas atualmente na mesa
    int extremidade_esquerda;      // valor aberto na ponta esquerda da mesa
    int extremidade_direita;       // valor aberto na ponta direita da mesa
} Mesa;

// REQ09: cria/inicializa uma mesa vazia, pronta para receber as jogadas
void criar_mesa(Mesa *mesa) {
    mesa->qtd_pecas = 0;
    mesa->extremidade_esquerda = -1; // -1 indica que ainda nao ha peca na mesa
    mesa->extremidade_direita = -1;
}

// Exibe o estado atual da mesa (usada aqui so para conferencia/teste)
void exibir_mesa(Mesa *mesa) {
    int i;
    printf("\n=============================================\n");
    if (mesa->qtd_pecas == 0) {
        printf("Mesa vazia (nenhuma peca jogada ainda)\n");
    } else {
        for (i = 0; i < mesa->qtd_pecas; i++) {
            printf("[%d|%d] ", mesa->pecas[i].lado_a, mesa->pecas[i].lado_b);
        }
        printf("\n(extremidades: %d e %d)\n", mesa->extremidade_esquerda, mesa->extremidade_direita);
    }
    printf("=============================================\n");
}

//Bloco de teste isolado do REQ09 (pode ser removido ao integrar com o menu principal)
int main(void) {
    Mesa mesa;

    criar_mesa(&mesa);
    exibir_mesa(&mesa);

    printf("\nQtd de pecas na mesa: %d\n", mesa.qtd_pecas);
    printf("Extremidade esquerda: %d\n", mesa.extremidade_esquerda);
    printf("Extremidade direita: %d\n", mesa.extremidade_direita);

    return 0;
}
