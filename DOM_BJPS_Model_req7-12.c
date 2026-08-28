//DOM_BJPS_Model.c - Projeto Domino LP2026
//Bruna, Joao Pedro Freitas Vilar, Pedru Gama, Samira
//NAO deve conter printf/scanf - so dados e regras do jogo, PORTANTO NAO DEVE E NAO SERA COMPILADO

#include <stdlib.h>
#include "DOM_BJPS_Model.h"

// REQ01/REQ02: monta as 28 pecas do domino (0-0 ate 6-6), todas disponiveis
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

// Embaralha as pecas (Fisher-Yates)
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
    // As pecas restantes (14) ficam com status 'D', formando o monte de compra
}

// REQ09: cria/inicializa uma mesa vazia
void criar_mesa(Mesa *mesa) {
    mesa->qtd_pecas = 0;
    mesa->extremidade_esquerda = -1;
    mesa->extremidade_direita = -1;
}

// REQ10: procura a peca dobrada de maior valor entre as pecas de um jogador
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

// REQ10: procura a peca de maior soma entre as pecas de um jogador (desempate)
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

// REQ10: define o jogador que fara a primeira jogada
char definir_primeiro_jogador(PecaDomino pecas[]) {
    int maior_j1 = maior_dobrada_do_jogador(pecas, '1');
    int maior_j2 = maior_dobrada_do_jogador(pecas, '2');

    if (maior_j1 > maior_j2) {
        return '1';
    }
    if (maior_j2 > maior_j1) {
        return '2';
    }

    // Nenhum dos dois tem peca dobrada: desempata pela peca de maior soma
    maior_j1 = maior_soma_do_jogador(pecas, '1');
    maior_j2 = maior_soma_do_jogador(pecas, '2');

    if (maior_j1 >= maior_j2) {
        return '1';
    }
    return '2';
}

// REQ11: compra uma peca aleatoria do monte para o jogador; -1 se monte vazio
int comprar_peca(PecaDomino pecas[], char jogador) {
    int indices_disponiveis[TOTAL_PECAS];
    int qtd_disponiveis = 0;
    int i, sorteado, indice_escolhido;

    for (i = 0; i < TOTAL_PECAS; i++) {
        if (pecas[i].status == 'D') {
            indices_disponiveis[qtd_disponiveis] = i;
            qtd_disponiveis++;
        }
    }

    if (qtd_disponiveis == 0) {
        return -1;
    }

    sorteado = rand() % qtd_disponiveis;
    indice_escolhido = indices_disponiveis[sorteado];
    pecas[indice_escolhido].status = jogador;

    return indice_escolhido;
}

// REQ11: conta quantas pecas ainda estao disponiveis no monte
int qtd_pecas_disponiveis(PecaDomino pecas[]) {
    int i, qtd = 0;
    for (i = 0; i < TOTAL_PECAS; i++) {
        if (pecas[i].status == 'D') {
            qtd++;
        }
    }
    return qtd;
}

// REQ12: verifica se uma peca pode ser colocada em determinada extremidade
int jogada_valida(PecaDomino peca, int extremidade) {
    if (extremidade == -1) {
        return 1; // mesa vazia: qualquer peca pode ser a primeira jogada
    }
    return (peca.lado_a == extremidade || peca.lado_b == extremidade);
}

int jogada_valida_esquerda(PecaDomino peca, Mesa *mesa) {
    return jogada_valida(peca, mesa->extremidade_esquerda);
}

int jogada_valida_direita(PecaDomino peca, Mesa *mesa) {
    return jogada_valida(peca, mesa->extremidade_direita);
}
