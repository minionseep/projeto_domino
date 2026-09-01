//DOM_BJPS_Projeto.c - Projeto Domino LP2026
//Bruna, Joao Pedro Freitas Vilar, Pedru Gama, Samira
//Teste de integracao do que ja foi feito (REQ07 a REQ12)
//Quando o Controller.c estiver pronto (com jogar()), troque este main()
//pela chamada a jogar(), como no exemplo do professor.

#include <stdlib.h>
#include <time.h>
#include "DOM_BJPS_Model_req7-12.c"
#include "DOM_BJPS_View_req7-12.c"

int main(void) {
    PecaDomino pecas[TOTAL_PECAS];
    Mesa mesa;
    int qtd_jogadores;
    char primeiro_jogador;
    int indice_compra;

    srand((unsigned int)time(NULL));

    qtd_jogadores = definir_qtd_jogadores();          // REQ07
    gerar_pecas(pecas);                               // REQ01/02
    distribuir_pecas(pecas);                          // REQ08
    criar_mesa(&mesa);                                // REQ09

    exibir_modo_escolhido(qtd_jogadores);
    exibir_pecas_jogador(pecas, '1');
    exibir_pecas_jogador(pecas, '2');
    exibir_mesa(&mesa);

    primeiro_jogador = definir_primeiro_jogador(pecas); // REQ10
    exibir_primeiro_jogador(primeiro_jogador);

    indice_compra = comprar_peca(pecas, '1');           // REQ11
    exibir_resultado_compra(pecas, indice_compra);

    exibir_teste_jogada_valida(pecas[0],                 // REQ12
        jogada_valida(pecas[0], mesa.extremidade_esquerda));

    return 0;
}
