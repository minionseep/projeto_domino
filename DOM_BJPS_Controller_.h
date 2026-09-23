//DOM_BJPS_Controller - Projeto Dominó LP2026
//13/08/2026
//Bruna, João Pedro Freitas Vilar, Pedru Gama, Samira
#ifndef CONTROLLER_H
#define CONTROLLER_H

#include "DOM_BJPS_Model_.h"

void executar_sistema(void);
void iniciar_partida_domino(EstadoJogo *jogo);
void determinar_quantidade_jogadores(EstadoJogo *jogo);
void distribuir_pecas_iniciais(EstadoJogo *jogo);       
void definir_primeiro_jogador(EstadoJogo *jogo);        
int  comprar_peca(EstadoJogo *jogo, int idx_jogador);   
int  validar_jogada(PecaDomino peca, int extremidade);  
void processar_turno(EstadoJogo *jogo);
void processar_turno_ia(EstadoJogo *jogo); // REQ20
void finalizar_jogo(EstadoJogo *jogo);                 
void registrar_vitoria(EstadoJogo *jogo, int idx_vencedor); // REQ21

#endif