//DOM_BJPS_Model - Projeto Dominó LP2026
//13/08/2026
//Bruna, João Pedro Freitas Vilar, Pedru Gama, Samira
#ifndef MODEL_H
#define MODEL_H

#define TOTAL_PECAS 28

// Estrutura de uma única peça (REQ01)
typedef struct {
    int lado_a;
    int lado_b;
} PecaDomino;

// Estrutura com os conjuntos de peças
typedef struct {
    PecaDomino pecas_ordenadas[TOTAL_PECAS];
    PecaDomino pecas_atuais[TOTAL_PECAS];
} ConjuntoDomino;

// Assinaturas das funções (Model)
void inicializar_conjunto(ConjuntoDomino *conjunto);  // REQ01
void embaralhar_conjunto(ConjuntoDomino *conjunto);    // REQ02
void reiniciar_partida(ConjuntoDomino *conjunto);      // REQ03

#endif
