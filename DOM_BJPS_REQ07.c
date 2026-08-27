//DOM_BJPS_REQ07 - Projeto Dominó LP2026
//26/08/2026
//Bruna, João Pedro Freitas Vilar, Pedru Gama, Samira

#include <stdio.h>

#define QTD_MIN_JOGADORES 1
#define QTD_MAX_JOGADORES 2

// REQ07: O sistema deve permitir ao usuario determinar a quantidade de
// jogadores. No minimo 1 e maximo 2 jogadores.
int definir_qtd_jogadores(void) {
    int qtd;
    int valido = 0;

    do {
        printf("\n=============================================\n");
        printf("           QUANTIDADE DE JOGADORES            \n");
        printf("=============================================\n");
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

//Bloco de teste isolado do REQ07 (pode ser removido ao integrar com o menu principal)
int main(void) {
    int qtd_jogadores = definir_qtd_jogadores();

    if (qtd_jogadores == 1) {
        printf("\n[SISTEMA]: Modo definido: 1 jogador (voce x computador).\n");
    } else {
        printf("\n[SISTEMA]: Modo definido: 2 jogadores.\n");
    }

    return 0;
}
