//DOM_BJPS_Model.h - Projeto Domino LP2026
//Bruna, Joao Pedro Freitas Vilar, Pedru Gama, Samira

#ifndef DOM_BJPS_MODEL_H
#define DOM_BJPS_MODEL_H

#define TOTAL_PECAS 28
#define PECAS_POR_JOGADOR 7
#define QTD_MIN_JOGADORES 1
#define QTD_MAX_JOGADORES 2

typedef struct {
    int lado_a;
    int lado_b;
    char status; // 'D' = disponivel (monte), '1' = jogador 1, '2' = jogador 2
} PecaDomino;

typedef struct {
    PecaDomino pecas[TOTAL_PECAS]; // pecas colocadas na mesa, na ordem em que foram jogadas
    int qtd_pecas;                 // quantidade de pecas atualmente na mesa
    int extremidade_esquerda;      // valor aberto na ponta esquerda (-1 = mesa vazia)
    int extremidade_direita;       // valor aberto na ponta direita (-1 = mesa vazia)
} Mesa;

// REQ01/REQ02/REQ08
void gerar_pecas(PecaDomino pecas[]);
void embaralhar_pecas(PecaDomino pecas[]);
void distribuir_pecas(PecaDomino pecas[]);

// REQ09
void criar_mesa(Mesa *mesa);

// REQ10
int maior_dobrada_do_jogador(PecaDomino pecas[], char jogador);
int maior_soma_do_jogador(PecaDomino pecas[], char jogador);
char definir_primeiro_jogador(PecaDomino pecas[]);

// REQ11
int comprar_peca(PecaDomino pecas[], char jogador);
int qtd_pecas_disponiveis(PecaDomino pecas[]);

// REQ12
int jogada_valida(PecaDomino peca, int extremidade);
int jogada_valida_esquerda(PecaDomino peca, Mesa *mesa);
int jogada_valida_direita(PecaDomino peca, Mesa *mesa);

#endif
