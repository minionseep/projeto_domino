//DOM_BJPS_View - Projeto Dominó LP2026
//13/08/2026
//Bruna, João Pedro Freitas Vilar, Pedru Gama, Samira
#include "DOM_BJPS_View.h"
#include <stdio.h>

// Menu Principal: mantidas todas as opções originais (1 a 4) e acrescentadas as novas
void exibir_menu(void) {
    printf("\n=============================================\n");
    printf("         SISTEMA DE DOMINO - PUC-SP          \n");
    printf("=============================================\n");
    printf("1. Mostrar pecas ordenadas \n");
    printf("2. Mostrar pecas embaralhadas \n");
    printf("3. Embaralhar pecas \n");
    printf("4. Iniciar nova partida / Re-embaralhar \n");
    printf("5. Jogar Partida de Domino (REQ07 a REQ16)\n");
    printf("6. Visualizar regras do jogo (REQ17)\n");
    printf("0. Sair\n");
    printf("=============================================\n");
}

void exibir_menu_jogo(int jogador_atual) {
    printf("\n--- TURNO DO JOGADOR %d ---\n", jogador_atual + 1);
    printf("J - Jogar peca na mesa\n");
    printf("C - Comprar peca do monte\n");  // REQ11 / REQ16
    printf("P - Passar a vez\n");
    printf("F - Finalizar partida\n");       // REQ15
    printf("Opcao: ");
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

// REQ13: Exibe as peças da mão do jogador atual
void exibir_mao_jogador(int id_jogador, const PecaDomino pecas[], int quantidade) {
    int i;
    printf("\n>>> Sua Mao (Jogador %d) [%d pecas]:\n", id_jogador, quantidade);
    for (i = 0; i < quantidade; i++) {
        printf(" %d:[%d|%d] ", i + 1, pecas[i].lado_a, pecas[i].lado_b);
    }
    printf("\n");
}

// REQ14: Esconde as peças do adversário (mostra somente a quantidade)
void exibir_status_adversario_oculto(int id_adversario, int quantidade_pecas) {
    int i;
    printf("\n[Adversario - Jogador %d]: possui %d pecas -> ", id_adversario, quantidade_pecas);
    for (i = 0; i < quantidade_pecas; i++) {
        printf("[#|#] ");
    }
    printf("\n");
}

// Visualização do estado da mesa
void exibir_mesa(const MesaDomino *mesa) {
    int i;
    printf("\n==================== MESA ====================\n");
    if (mesa->quantidade == 0) {
        printf("[ Mesa Vazia ]\n");
    } else {
        printf("Extremidade Esquerda: (%d)  |  Extremidade Direita: (%d)\n\n", 
               mesa->extremidade_esquerda, mesa->extremidade_direita);
        for (i = 0; i < mesa->quantidade; i++) {
            printf("[%d|%d] ", mesa->pecas[i].lado_a, mesa->pecas[i].lado_b);
        }
        printf("\n");
    }
    printf("==============================================\n");
}

// REQ17: Visualizar regras do jogo
void exibir_regras_jogo(void) {
    printf("\n================ REGRAS DO JOGO ================\n");
    printf("1. O jogo eh disputado entre 1 ou 2 jogadores.\n");
    printf("2. Cada jogador recebe 7 pecas inicialmente.\n");
    printf("3. Comeca o jogador que possuir o maior duplo (bucha).\n");
    printf("4. A cada turno, coloque uma peca que encaixe em uma das extremidades.\n");
    printf("5. Se nao houver peca valida, compre do monte ate achar uma.\n");
    printf("6. Vence quem colocar todas as suas pecas na mesa primeiro (bater),\n");
    printf("   ou quem tiver menor contagem de pontos se fechar.\n");
    printf("================================================\n");
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

// REQ07: pergunta a quantidade de jogadores (validacao de formato aqui,
// validacao de faixa 1-2 fica no Controller, que decide se pede de novo)
int ler_quantidade_jogadores(void) {
    int qtd;
    printf("\nInforme a quantidade de jogadores (1 para contra CPU, 2 para P1 vs P2): ");
    if (scanf("%d", &qtd) != 1) {
        while (getchar() != '\n'); // Limpa buffer
        return -1;
    }
    return qtd;
}

// REQ10: exibe quem vai comecar a partida
void exibir_primeiro_jogador(int numero_jogador) {
    printf("\n[SISTEMA]: Jogador %d iniciara a partida!\n", numero_jogador);
}

// Le a acao escolhida no turno (J/C/P/F) - o menu ja foi mostrado por
// exibir_menu_jogo antes desta chamada
char ler_acao_turno(void) {
    char acao;
    scanf(" %c", &acao);
    return acao;
}

// REQ12 (apoio): pergunta qual peca da mao o jogador quer jogar
int ler_numero_peca(int qtd_mao) {
    int num_peca;
    printf("Escolha o numero da peca na sua mao (1 a %d): ", qtd_mao);
    scanf("%d", &num_peca);
    return num_peca;
}

// Pergunta em qual extremidade da mesa a peca vai ser jogada
int ler_lado_jogada(void) {
    int lado;
    printf("Jogar na Esquerda (1) ou Direita (2)? ");
    scanf("%d", &lado);
    return lado;
}

void exibir_vencedor(int numero_jogador) {
    printf("\n*** PARABENS! JOGADOR %d BATEU E VENCEU! ***\n", numero_jogador);
}
