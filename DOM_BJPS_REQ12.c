//DOM_BJPS_REQ12 - Projeto Dominó LP2026
//26/08/2026
//Bruna, Joâo Pedro Freitas Vilar, Pedru Gama, Samira

#include <stdio.h>

#define TOTAL_PECAS 28

typedef struct {
    int lado_a;
    int lado_b;
    char status; // 'D' = disponivel (monte), '1' = jogador 1, '2' = jogador 2
} PecaDomino;

typedef struct {
    PecaDomino pecas[TOTAL_PECAS]; // pecas colocadas na mesa, na ordem em que foram jogadas
    int qtd_pecas;                 // quantidade de pecas atualmente na mesa
    int extremidade_esquerda;      // valor aberto na ponta esquerda da mesa (-1 = mesa vazia)
    int extremidade_direita;       // valor aberto na ponta direita da mesa (-1 = mesa vazia)
} Mesa;

// --- Funcao ja feita no REQ09, reaproveitada aqui ---
void criar_mesa(Mesa *mesa) {
    mesa->qtd_pecas = 0;
    mesa->extremidade_esquerda = -1;
    mesa->extremidade_direita = -1;
}

// --- REQ12 ---

// REQ12: verifica se uma peca pode ser colocada em determinada extremidade da
// mesa, ou seja, se algum dos lados da peca tem a mesma pontuacao da
// extremidade escolhida. Se a mesa ainda estiver vazia (extremidade == -1),
// qualquer peca e valida, pois sera a primeira jogada da partida.
int jogada_valida(PecaDomino peca, int extremidade) {
    if (extremidade == -1) {
        return 1; // mesa vazia: qualquer peca pode ser a primeira jogada
    }

    return (peca.lado_a == extremidade || peca.lado_b == extremidade);
}

// Verifica se a peca e valida para a extremidade esquerda da mesa
int jogada_valida_esquerda(PecaDomino peca, Mesa *mesa) {
    return jogada_valida(peca, mesa->extremidade_esquerda);
}

// Verifica se a peca e valida para a extremidade direita da mesa
int jogada_valida_direita(PecaDomino peca, Mesa *mesa) {
    return jogada_valida(peca, mesa->extremidade_direita);
}

//Bloco de teste isolado do REQ12 (pode ser removido ao integrar com o menu principal)
int main(void) {
    Mesa mesa;
    PecaDomino peca1 = {3, 5, '1'}; // tem o 3 e o 5
    PecaDomino peca2 = {2, 4, '1'}; // nao tem nem 3 nem 6

    // Caso 1: mesa vazia -> qualquer peca deve ser valida
    criar_mesa(&mesa);
    printf("Mesa vazia:\n");
    printf("Peca [%d|%d] na esquerda? %s\n", peca1.lado_a, peca1.lado_b,
           jogada_valida_esquerda(peca1, &mesa) ? "VALIDA" : "INVALIDA");

    // Caso 2: mesa com extremidades definidas (esquerda = 3, direita = 6)
    mesa.extremidade_esquerda = 3;
    mesa.extremidade_direita = 6;
    printf("\nMesa com extremidades 3 (esq) e 6 (dir):\n");

    printf("Peca [%d|%d] na esquerda (precisa ter o 3)? %s\n", peca1.lado_a, peca1.lado_b,
           jogada_valida_esquerda(peca1, &mesa) ? "VALIDA" : "INVALIDA");

    printf("Peca [%d|%d] na direita (precisa ter o 6)? %s\n", peca1.lado_a, peca1.lado_b,
           jogada_valida_direita(peca1, &mesa) ? "VALIDA" : "INVALIDA");

    printf("Peca [%d|%d] na esquerda (precisa ter o 3)? %s\n", peca2.lado_a, peca2.lado_b,
           jogada_valida_esquerda(peca2, &mesa) ? "VALIDA" : "INVALIDA");

    return 0;
}
