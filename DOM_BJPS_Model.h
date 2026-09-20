//DOM_BJPS_Model - Projeto Dominó LP2026
//13/08/2026
//Bruna, João Pedro Freitas Vilar, Pedru Gama, Samira
#ifndef MODEL_H
#define MODEL_H

#define TOTAL_PECAS 28
#define MAX_PECAS_MAO 28

// Status da peça no jogo
typedef enum {
    DISPONIVEL,
    NA_MESA,
    COM_JOGADOR1,
    COM_JOGADOR2
} StatusPeca;

// Estrutura de uma única peça (REQ01)
typedef struct {
    int lado_a;
    int lado_b;
    StatusPeca status;
} PecaDomino;

// Estrutura com os conjuntos de peças (Mantida do original)
typedef struct {
    PecaDomino pecas_ordenadas[TOTAL_PECAS];
    PecaDomino pecas_atuais[TOTAL_PECAS];
} ConjuntoDomino;

// REQ09: Estrutura da Mesa do Jogo
typedef struct {
    PecaDomino pecas[TOTAL_PECAS];
    int quantidade;
    int extremidade_esquerda;
    int extremidade_direita;
} MesaDomino;

// Estrutura do Jogador
typedef struct {
    int id; // 1 ou 2
    PecaDomino mao[MAX_PECAS_MAO];
    int qtd_mao;
    int eh_computador; // 0 = Humano, 1 = Computador
} Jogador;

// Estrutura para gerenciar o Estado Completo do Jogo
typedef struct {
    ConjuntoDomino conjunto;
    MesaDomino mesa;
    Jogador jogadores[2];
    int num_jogadores; // REQ07 (1 ou 2)
    int jogador_atual; // REQ10 (0 para Jogador 1, 1 para Jogador 2)
    int indice_compra; // Próxima peça do monte disponível para compra
    int jogo_ativo;    // REQ15
} EstadoJogo;

// Assinaturas das funções (Model) - Mantidas as originais e adicionadas as novas
void inicializar_conjunto(ConjuntoDomino *conjunto);  // REQ01
void embaralhar_conjunto(ConjuntoDomino *conjunto);    // REQ02
void reiniciar_partida(ConjuntoDomino *conjunto);      // REQ03
void inicializar_mesa(MesaDomino *mesa);              // REQ09

#endif
