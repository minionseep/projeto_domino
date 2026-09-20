//DOM_BJPS_View - Projeto Dominó LP2026
//13/08/2026
//Bruna, João Pedro Freitas Vilar, Pedru Gama, Samira

#ifndef VIEW_H
#define VIEW_H

#include "DOM_BJPS_Model.h"

// Assinaturas das funções (View) - Originais Mantidas
void exibir_menu(void);
void exibir_pecas(const char *titulo, const PecaDomino pecas[], int quantidade); // REQ04
void exibir_mensagem(const char *mensagem);
int solicitar_opcao(void);

// Assinaturas Adicionadas (REQ07 a REQ17)
void exibir_menu_jogo(int jogador_atual);
void exibir_mao_jogador(int id_jogador, const PecaDomino pecas[], int quantidade); // REQ13
void exibir_status_adversario_oculto(int id_adversario, int quantidade_pecas);      // REQ14
void exibir_mesa(const MesaDomino *mesa);
void exibir_regras_jogo(void);                                                     // REQ17

// Funcoes de entrada movidas do Controller para a View (SOMENTE aqui pode
// ter printf/scanf)
int ler_quantidade_jogadores(void);                    // REQ07
void exibir_primeiro_jogador(int numero_jogador);       // REQ10
char ler_acao_turno(void);
int ler_numero_peca(int qtd_mao);
int ler_lado_jogada(void);
void exibir_vencedor(int numero_jogador);

#endif
