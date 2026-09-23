//DOM_BJPS_View - Projeto Dominó LP2026
//13/08/2026
//Bruna, João Pedro Freitas Vilar, Pedru Gama, Samira

#ifndef VIEW_H
#define VIEW_H

#include "DOM_BJPS_Model_.h"

void limpar_tela(void);
void aguardar_enter(void);
void exibir_menu(void);
void exibir_pecas(const char *titulo, const PecaDomino pecas[], int quantidade);
void exibir_mensagem(const char *mensagem);
int solicitar_opcao(void);

void exibir_menu_jogo(int jogador_atual);
void exibir_mao_jogador(int id_jogador, const PecaDomino pecas[], int quantidade);
void exibir_status_adversario_oculto(int id_adversario, int quantidade_pecas);
void exibir_mesa(const MesaDomino *mesa);
void exibir_regras_jogo(void);
void exibir_placar(int placar_jogador1, int placar_jogador2); // REQ21

int ler_quantidade_jogadores(void);
void exibir_primeiro_jogador(int numero_jogador);
char ler_acao_turno(void);
int ler_numero_peca(int qtd_mao);
int ler_lado_jogada(void);
void exibir_vencedor(int numero_jogador);

#endif