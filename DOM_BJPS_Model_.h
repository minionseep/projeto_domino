//DOM_BJPS_Model - Projeto Dominó LP2026
//13/08/2026
//Bruna, João Pedro Freitas Vilar, Pedru Gama, Samira
#ifndef MODEL_H
#define MODEL_H

#define TOTAL_PECAS 28
#define MAX_PECAS_MAO 28
#define NOME_ARQUIVO_SALVO "partida_domino.dat"

typedef enum {
    DISPONIVEL,
    NA_MESA,
    COM_JOGADOR1,
    COM_JOGADOR2
} StatusPeca;

typedef struct {
    int lado_a;
    int lado_b;
    StatusPeca status;
} PecaDomino;

typedef struct {
    PecaDomino pecas_ordenadas[TOTAL_PECAS];
    PecaDomino pecas_atuais[TOTAL_PECAS];
} ConjuntoDomino;

typedef struct {
    PecaDomino pecas[TOTAL_PECAS];
    int quantidade;
    int extremidade_esquerda;
    int extremidade_direita;
} MesaDomino;

typedef struct {
    int id; // 1 ou 2
    PecaDomino mao[MAX_PECAS_MAO];
    int qtd_mao;
    int eh_computador; // 0 = Humano, 1 = Computador
} Jogador;

typedef struct {
    ConjuntoDomino conjunto;
    MesaDomino mesa;
    Jogador jogadores[2];
    int num_jogadores; 
    int jogador_atual; 
    int indice_compra; 
    int jogo_ativo;    
    // REQ21: Placar de vitorias. Faz parte do EstadoJogo (e portanto e
    // salvo/carregado junto com a partida) para que o placar so exista em
    // duas situacoes legitimas: (1) partidas jogadas em sequencia durante a
    // mesma execucao do programa, a partir de 0x0; ou (2) uma partida salva
    // que e recarregada, trazendo consigo o historico ja acumulado. Nao ha
    // como "inventar" um placar para um jogador novo que nunca jogou nem
    // carregou nada.
    int placar_jogador1;
    int placar_jogador2;
} EstadoJogo;

void inicializar_conjunto(ConjuntoDomino *conjunto);  
void embaralhar_conjunto(ConjuntoDomino *conjunto);    
void reiniciar_partida(ConjuntoDomino *conjunto);      
void inicializar_mesa(MesaDomino *mesa);              
void inicializar_placar(EstadoJogo *jogo);            // REQ21

// REQ18 e REQ19
int salvar_estado_jogo(const EstadoJogo *jogo);
int carregar_estado_jogo(EstadoJogo *jogo);

#endif