//DOM_BJPS_REQ10 - Projeto Dominó LP2026
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

// --- Funcoes ja feitas em REQs anteriores (REQ01/REQ02/REQ08), reaproveitadas aqui ---

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

void distribuir_pecas(PecaDomino pecas[]) {
    int i, distribuidas;

    embaralhar_pecas(pecas);

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
}

// --- REQ10 ---

// Procura, entre as pecas de um jogador, a peca dobrada (lado_a == lado_b)
// de maior valor. Retorna o valor da maior dobrada encontrada, ou -1 se o
// jogador nao tiver nenhuma peca dobrada.
int maior_dobrada_do_jogador(PecaDomino pecas[], char jogador) {
    int i;
    int maior = -1;
    for (i = 0; i < TOTAL_PECAS; i++) {
        if (pecas[i].status == jogador && pecas[i].lado_a == pecas[i].lado_b) {
            if (pecas[i].lado_a > maior) {
                maior = pecas[i].lado_a;
            }
        }
    }
    return maior;
}

// Procura, entre as pecas de um jogador, a de maior soma (lado_a + lado_b).
// Usada como criterio de desempate quando nenhum dos jogadores tem dobrada.
int maior_soma_do_jogador(PecaDomino pecas[], char jogador) {
    int i;
    int maior = -1;
    for (i = 0; i < TOTAL_PECAS; i++) {
        if (pecas[i].status == jogador) {
            int soma = pecas[i].lado_a + pecas[i].lado_b;
            if (soma > maior) {
                maior = soma;
            }
        }
    }
    return maior;
}

// REQ10: define o jogador que fara a primeira jogada.
// Regra: comeca quem tiver a peca "seis-seis"; se ninguem tiver, comeca quem
// tiver a maior dobrada (cinco-cinco, quatro-quatro, etc). Se nenhum dos dois
// tiver nenhuma dobrada, comeca quem tiver a peca de maior soma de pontos.
char definir_primeiro_jogador(PecaDomino pecas[]) {
    int maior_j1 = maior_dobrada_do_jogador(pecas, '1');
    int maior_j2 = maior_dobrada_do_jogador(pecas, '2');

    if (maior_j1 > maior_j2) {
        return '1';
    }
    if (maior_j2 > maior_j1) {
        return '2';
    }

    // Nenhum dos dois tem peca dobrada (maior_j1 == maior_j2 == -1):
    // desempata pela peca de maior soma de pontos
    maior_j1 = maior_soma_do_jogador(pecas, '1');
    maior_j2 = maior_soma_do_jogador(pecas, '2');

    if (maior_j1 >= maior_j2) {
        return '1';
    }
    return '2';
}

// Exibe as pecas de um jogador (usada aqui so para conferencia/teste)
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

//Bloco de teste isolado do REQ10 (pode ser removido ao integrar com o menu principal)
int main(void) {
    PecaDomino pecas[TOTAL_PECAS];
    char primeiro_jogador;

    srand((unsigned int)time(NULL));

    gerar_pecas(pecas);
    distribuir_pecas(pecas);

    exibir_pecas_jogador(pecas, '1');
    exibir_pecas_jogador(pecas, '2');

    primeiro_jogador = definir_primeiro_jogador(pecas);
    printf("\nO jogador %c fara a primeira jogada!\n", primeiro_jogador);

    return 0;
}
