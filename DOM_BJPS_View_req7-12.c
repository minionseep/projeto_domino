//DOM_BJPS_View.c - Projeto Domino LP2026
//Bruna, Joao Pedro Freitas Vilar, Pedru Gama, Samira
//SOMENTE AQUI podemos ter printf/scanf

#include <stdio.h>
#include "DOM_BJPS_View_req7-12.h"

// REQ07: pergunta e valida a quantidade de jogadores (1 ou 2)
// ATENCAO: cole aqui o corpo COMPLETO da funcao que ja esta em
// DOM_BJPS_REQ07.c (o print so mostrou ate a linha 35). Mantenha a
// assinatura abaixo (int definir_qtd_jogadores(void)) e o "return qtd;"
// no final, dentro do do...while ja validado.
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
        // TODO: cole aqui o restante real do REQ07.c, se for diferente disso
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

// Exibe o modo de jogo escolhido (usada pelo Projeto/Controller no lugar de
// um printf direto - so a View pode ter printf)
void exibir_modo_escolhido(int qtd_jogadores) {
    printf("\nModo escolhido: %d jogador(es)\n", qtd_jogadores);
}

// REQ10: exibe qual jogador fara a primeira jogada
void exibir_primeiro_jogador(char jogador) {
    printf("\nO jogador %c fara a primeira jogada!\n", jogador);
}

// REQ11: exibe o resultado de uma tentativa de compra de peca
void exibir_resultado_compra(PecaDomino pecas[], int indice_compra) {
    if (indice_compra != -1) {
        printf("Jogador 1 comprou [%d|%d]\n", pecas[indice_compra].lado_a, pecas[indice_compra].lado_b);
    } else {
        printf("Nao ha pecas disponiveis para comprar!\n");
    }
}

// REQ12: exibe o resultado de um teste de jogada valida
void exibir_teste_jogada_valida(PecaDomino peca, int valida) {
    printf("Peca [%d|%d] valida na jogada testada? %s\n",
           peca.lado_a, peca.lado_b, valida ? "SIM" : "NAO");
}
