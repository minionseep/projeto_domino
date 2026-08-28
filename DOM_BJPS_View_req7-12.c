//DOM_BJPS_View.c - Projeto Domino LP2026
//Bruna, Joao Pedro Freitas Vilar, Pedru Gama, Samira
//SOMENTE AQUI podemos ter printf/scanf

#include <stdio.h>
#include "DOM_BJPS_View.h"

// REQ07: pergunta e valida a quantidade de jogadores (1 ou 2)
int definir_qtd_jogadores(void) {
    int qtd;
    int valido = 0;

    do {
        printf("\n========================================\n");
        printf("            QUANTIDADE DE JOGADORES\n");
        printf("========================================\n");
        printf("1 - Um jogador (voce x computador)\n");
        printf("2 - Dois jogadores\n");
        printf("Digite a quantidade de jogadores: ");

        if (scanf("%d", &qtd) != 1) {
            while (getchar() != '\n'); // Limpa buffer
            printf("\n[SISTEMA]: Entrada invalida! Digite um numero.\n");
            valido = 0;
            continue;
        }

        if (qtd < QTD_MIN_JOGADORES || qtd > QTD_MAX_JOGADORES) {
            printf("\n[SISTEMA]: Quantidade invalida! Digite 1 (voce x computador) ou 2 (dois jogadores).\n");
            valido = 0;
        } else {
            valido = 1;
        }
    } while (!valido);

    return qtd;
}

// REQ08: exibe as pecas de um jogador
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

// REQ09: exibe o estado atual da mesa
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
