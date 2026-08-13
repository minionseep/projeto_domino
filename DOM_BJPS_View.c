//DOM_BJPS_View - Projeto Dominó LP2026
//13/08/2026
//Bruna, João Pedro Freitas Vilar, Pedru Gama, Samira
#include "DOM_BJPS_View.h"
#include <stdio.h>

void exibir_menu(void) {
    printf("\n=============================================\n");
    printf("         SISTEMA DE DOMINO - PUC-SP          \n");
    printf("=============================================\n");
    printf("1. Mostrar pecas ordenadas (REQ04)\n");
    printf("2. Mostrar pecas embaralhadas (REQ04)\n");
    printf("3. Embaralhar pecas (REQ02)\n");
    printf("4. Iniciar nova partida / Re-embaralhar (REQ03)\n");
    printf("0. Sair\n");
    printf("=============================================\n");
}

void exibir_pecas(const char *titulo, const PecaDomino pecas[], int quantidade) {
    int i;
    printf("\n--- %s (%d pecas) ---\n", titulo, quantidade);
    
    // REQ04: Exibe em modo texto organizado em linhas
    for (i = 0; i < quantidade; i++) {
        printf("[%d|%d] ", pecas[i].lado_a, pecas[i].lado_b);
        if ((i + 1) % 7 == 0) {
            printf("\n");
        }
    }
    printf("---------------------------------------------\n");
}

void exibir_mensagem(const char *mensagem) {
    printf("\n[SISTEMA]: %s\n", mensagem);
}

int solicitar_opcao(void) {
    int opcao;
    printf("Escolha uma opcao: ");
    if (scanf("%d", &opcao) != 1) {
        while (getchar() != '\n'); // Limpa buffer
        return -1;
    }
    return opcao;
}
