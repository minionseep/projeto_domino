//DOM_BJPS_REQ11 - Projeto Dominó LP2026
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

// --- REQ11 ---

// REQ11: permite ao jogador comprar uma peca aleatoria dentre as disponiveis
// no monte. Retorna o indice da peca comprada (em pecas[]), ou -1 se nao
// houver mais pecas disponiveis para comprar.
int comprar_peca(PecaDomino pecas[], char jogador) {
    int indices_disponiveis[TOTAL_PECAS];
    int qtd_disponiveis = 0;
    int i;

    // Monta a lista de indices das pecas ainda disponiveis (status == 'D')
    for (i = 0; i < TOTAL_PECAS; i++) {
        if (pecas[i].status == 'D') {
            indices_disponiveis[qtd_disponiveis] = i;
            qtd_disponiveis++;
        }
    }

    if (qtd_disponiveis == 0) {
        return -1; // monte vazio, nao ha pecas para comprar
    }

    // Sorteia uma peca entre as disponiveis e entrega ao jogador
    int sorteado = rand() % qtd_disponiveis;
    int indice_escolhido = indices_disponiveis[sorteado];

    pecas[indice_escolhido].status = jogador;

    return indice_escolhido;
}

// Conta quantas pecas ainda estao disponiveis no monte (usada aqui so para teste)
int qtd_pecas_disponiveis(PecaDomino pecas[]) {
    int i, qtd = 0;
    for (i = 0; i < TOTAL_PECAS; i++) {
        if (pecas[i].status == 'D') {
            qtd++;
        }
    }
    return qtd;
}

// Exibe as pecas de um jogador (usada aqui so para conferencia/teste)
void exibir_pecas_jogador(PecaDomino pecas[], char jogador) {
    int i;
    printf("Pecas do jogador %c: ", jogador);
    for (i = 0; i < TOTAL_PECAS; i++) {
        if (pecas[i].status == jogador) {
            printf("[%d|%d] ", pecas[i].lado_a, pecas[i].lado_b);
        }
    }
    printf("\n");
}

//Bloco de teste isolado do REQ11 (pode ser removido ao integrar com o menu principal)
int main(void) {
    PecaDomino pecas[TOTAL_PECAS];
    int indice;

    srand((unsigned int)time(NULL));

    gerar_pecas(pecas);
    distribuir_pecas(pecas);

    printf("Antes de comprar:\n");
    exibir_pecas_jogador(pecas, '1');
    printf("Pecas disponiveis no monte: %d\n\n", qtd_pecas_disponiveis(pecas));

    // Jogador 1 compra uma peca
    indice = comprar_peca(pecas, '1');
    if (indice != -1) {
        printf("Jogador 1 comprou a peca [%d|%d]\n", pecas[indice].lado_a, pecas[indice].lado_b);
    } else {
        printf("Nao ha pecas disponiveis para comprar!\n");
    }

    printf("\nDepois de comprar:\n");
    exibir_pecas_jogador(pecas, '1');
    printf("Pecas disponiveis no monte: %d\n\n", qtd_pecas_disponiveis(pecas));

    // Testa o caso do monte ficar vazio: compra tudo que resta e tenta mais uma vez
    printf("Comprando todo o resto do monte...\n");
    while (comprar_peca(pecas, '1') != -1) {
        // continua comprando
    }
    printf("Pecas disponiveis no monte: %d\n", qtd_pecas_disponiveis(pecas));

    indice = comprar_peca(pecas, '1');
    if (indice == -1) {
        printf("[SISTEMA]: Monte vazio! Nao e possivel comprar mais pecas.\n");
    }

    return 0;
}
