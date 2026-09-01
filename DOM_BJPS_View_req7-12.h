//DOM_BJPS_View.h - Projeto Domino LP2026
//Bruna, Joao Pedro Freitas Vilar, Pedru Gama, Samira

#ifndef DOM_BJPS_VIEW_H
#define DOM_BJPS_VIEW_H

#include "DOM_BJPS_Model_req7-12.h"

// REQ07: pergunta e valida a quantidade de jogadores (1 ou 2)
int definir_qtd_jogadores(void);

// Exibicoes usadas para conferencia/teste (REQ08, REQ09)
void exibir_pecas_jogador(PecaDomino pecas[], char jogador);
void exibir_mesa(Mesa *mesa);

// Exibicoes de orquestracao (usadas pelo Projeto/Controller, nunca fazem
// printf direto fora daqui, so aqui na View)
void exibir_modo_escolhido(int qtd_jogadores);
void exibir_primeiro_jogador(char jogador);
void exibir_resultado_compra(PecaDomino pecas[], int indice_compra);
void exibir_teste_jogada_valida(PecaDomino peca, int valida);

#endif
