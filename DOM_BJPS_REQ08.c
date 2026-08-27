//DOM_BJPS_REQ08 - Projeto Dominó LP2026
//26/08/2026
//Bruna, João Pedro Freitas Vilar, Pedru Gama, Samira

#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define TOTAL_PECAS 28
#define PECAS_POR_JOGADOR 7

typedef struct {
    int lado_a;
    int lado_b;
    char status; // 'D' = disponivel (monte), '1' = jogador 1, '2' = jogador 2
} PecaDomino;

// Monta as 28 pecas do domino (0-0 ate 6-6), todas comecando disponiveis
void gerar_pecas(PecaDomino pecas[]) {
    int idx = 0;
    int i, j;
    for (i = 0; i <= 6; i++) {
        for (j = i; j <= 6; j++) {
            pecas[idx].lado_a = i;
            pecas[idx].lado_b = j;
            pecas[idx].status = 'D';
            idx++;
        }
    }
}

// Embaralha as pecas (Fisher-Yates), usada para garantir sorteio aleatorio
void embaralhar_pecas(PecaDomino pecas[]) {
    int i, j;
    PecaDomino temp;
    for (i = TOTAL_PECAS - 1; i > 0; i--) {
        j = rand() % (i + 1);
        temp = pecas[i];
        pecas[i] = pecas[j];
        pecas[j] = temp;
    }
}

// REQ08: distribui aleatoriamente 7 pecas para cada jogador
void distribuir_pecas(PecaDomino pecas[]) {
    int i, distribuidas;

    embaralhar_pecas(pecas); // garante que o sorteio seja aleatorio

    distribuidas = 0;
    for (i = 0; i < TOTAL_PECAS && distribuidas < PECAS_POR_JOGADOR; i++) {
        if (pecas[i].status == 'D') {
            pecas[i].status = '1';
            distribuidas++;
        }
    }

    distribuidas = 0;
    for (i = 0; i < TOTAL_PECAS && distribuidas < PECAS_POR_JOGADOR; i++) {
        if (pecas[i].status == 'D') {
            pecas[i].status = '2';
            distribuidas++;
        }
    }
    // As pecas restantes (14) ficam com status 'D', formando o monte de compra
}

// Exibe as pecas de um jogador especifico (usada aqui so para conferencia/teste)
void exibir_pecas_jogador(PecaDomino pecas[], char jogador) {
    int i;
    printf("\nPecas do jogador %c:\n", jogador);
    for (i = 0; i < TOTAL_PECAS; i++) {
        if (pecas[i].status == jogador) {
            printf("[%d|%d] ", pecas[i].lado_a, pecas[i].lado_b);
        }
    }
    printf("\n");
}

//Bloco de teste isolado do REQ08 (pode ser removido ao integrar com o menu principal)
int main(void) {
    PecaDomino pecas[TOTAL_PECAS];
    int i, qtd_monte;

    srand((unsigned int)time(NULL));

    gerar_pecas(pecas);
    distribuir_pecas(pecas);

    exibir_pecas_jogador(pecas, '1');
    exibir_pecas_jogador(pecas, '2');

    printf("\nPecas ainda disponiveis no monte:\n");
    qtd_monte = 0;
    for (i = 0; i < TOTAL_PECAS; i++) {
        if (pecas[i].status == 'D') {
            printf("[%d|%d] ", pecas[i].lado_a, pecas[i].lado_b);
            qtd_monte++;
        }
    }
    printf("\nTotal no monte: %d\n", qtd_monte);

    return 0;
}
