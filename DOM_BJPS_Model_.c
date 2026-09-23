//DOM_BJPS_Model - Projeto Dominó LP2026
//13/08/2026
//Bruna, João Pedro Freitas Vilar, Pedru Gama, Samira

#include "DOM_BJPS_Model_.h"
#include <stdio.h>
#include <stdlib.h>

void inicializar_conjunto(ConjuntoDomino *conjunto) {
    int idx = 0;
    int i, j;
    
    for (i = 0; i <= 6; i++) {
        for (j = i; j <= 6; j++) {
            conjunto->pecas_ordenadas[idx].lado_a = i;
            conjunto->pecas_ordenadas[idx].lado_b = j;
            conjunto->pecas_ordenadas[idx].status = DISPONIVEL;
            
            conjunto->pecas_atuais[idx] = conjunto->pecas_ordenadas[idx];
            idx++;
        }
    }
}

void embaralhar_conjunto(ConjuntoDomino *conjunto) {
    int i, j;
    PecaDomino temp;
    
    for (i = TOTAL_PECAS - 1; i > 0; i--) {
        j = rand() % (i + 1);
        
        temp = conjunto->pecas_atuais[i];
        conjunto->pecas_atuais[i] = conjunto->pecas_atuais[j];
        conjunto->pecas_atuais[j] = temp;
    }
}

void reiniciar_partida(ConjuntoDomino *conjunto) {
    inicializar_conjunto(conjunto);
    embaralhar_conjunto(conjunto);
}

void inicializar_mesa(MesaDomino *mesa) {
    mesa->quantidade = 0;
    mesa->extremidade_esquerda = -1;
    mesa->extremidade_direita = -1;
}

// REQ21: Zera o placar. So deve ser chamada uma unica vez, no inicio da
// execucao do programa (antes do loop do menu), para comecar a contagem de
// uma nova sequencia de partidas em 0x0.
void inicializar_placar(EstadoJogo *jogo) {
    jogo->placar_jogador1 = 0;
    jogo->placar_jogador2 = 0;
}

// REQ18: Salva o estado completo do jogo em um arquivo binario
int salvar_estado_jogo(const EstadoJogo *jogo) {
    FILE *arq = fopen(NOME_ARQUIVO_SALVO, "wb");
    if (!arq) return 0;

    fwrite(jogo, sizeof(EstadoJogo), 1, arq);
    fclose(arq);
    return 1;
}

// REQ19: Carrega o jogo salvo
int carregar_estado_jogo(EstadoJogo *jogo) {
    FILE *arq = fopen(NOME_ARQUIVO_SALVO, "rb");
    if (!arq) return 0;

    fread(jogo, sizeof(EstadoJogo), 1, arq);
    fclose(arq);
    return 1;
}