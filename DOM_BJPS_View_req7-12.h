//DOM_BJPS_View.h - Projeto Domino LP2026
//Bruna, Joao Pedro Freitas Vilar, Pedru Gama, Samira

#ifndef DOM_BJPS_VIEW_H
#define DOM_BJPS_VIEW_H

#include "DOM_BJPS_Model.h"

// REQ07: pergunta e valida a quantidade de jogadores (1 ou 2)
int definir_qtd_jogadores(void);

// Exibicoes usadas para conferencia/teste (REQ08, REQ09)
void exibir_pecas_jogador(PecaDomino pecas[], char jogador);
void exibir_mesa(Mesa *mesa);

#endif
