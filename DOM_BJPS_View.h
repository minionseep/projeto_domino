//DOM_BJPS_View - Projeto Dominó LP2026
//13/08/2026
//Bruna, João Pedro Freitas Vilar, Pedru Gama, Samira

#ifndef VIEW_H
#define VIEW_H

#include "DOM_BJPS_Model.h"

// Assinaturas das funções (View)
void exibir_menu(void);
void exibir_pecas(const char *titulo, const PecaDomino pecas[], int quantidade); // REQ04
void exibir_mensagem(const char *mensagem);
int solicitar_opcao(void);

#endif
