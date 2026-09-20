//DOM_BJPS_Controller - Projeto Dominó LP2026
//13/08/2026
//Bruna, João Pedro Freitas Vilar, Pedru Gama, Samira
#ifndef CONTROLLER_H
#define CONTROLLER_H

#include "DOM_BJPS_Model.h"

// REQNF05 / REQNF06: Ponto de controle principal
void executar_sistema(void);

// Funções do fluxo do jogo (REQ07 a REQ16)
void iniciar_partida_domino(EstadoJogo *jogo);
void determinar_quantidade_jogadores(EstadoJogo *jogo); // REQ07
void distribuir_pecas_iniciais(EstadoJogo *jogo);        // REQ08
void definir_primeiro_jogador(EstadoJogo *jogo);         // REQ10
int  comprar_peca(EstadoJogo *jogo, int idx_jogador);    // REQ11 e REQ16
int  validar_jogada(PecaDomino peca, int extremidade);   // REQ12
void processar_turno(EstadoJogo *jogo);
void finalizar_jogo(EstadoJogo *jogo);                  // REQ15

#endif
