//DOM_BJPS_Projeto.c - Projeto Domino LP2026
//Bruna, Joao Pedro Freitas Vilar, Pedru Gama, Samira
//Teste de integracao do que ja foi feito (REQ07 a REQ12)
//Quando o Controller.c estiver pronto (com jogar()), troque este main()
//pela chamada a jogar(), como no exemplo do professor.

#include <stdlib.h>
#include <time.h>
#include "DOM_BJPS_Model.c"
#include "DOM_BJPS_View.c"

int main(void) {
    PecaDomino pecas[TOTAL_PECAS];
    Mesa mesa;
    int qtd_jogadores;
    char primeiro_jogador;
    int indice_compra;

    srand((unsigned int)time(NULL)); //funcao para gerar numeros aleatorios diferentes a cada execucao

    qtd_jogadores = definir_qtd_jogadores();          // REQ07
    gerar_pecas(pecas);                               // REQ01/02
    distribuir_pecas(pecas);                          // REQ08
    criar_mesa(&mesa);                                // REQ09

    printf("\nModo escolhido: %d jogador(es)\n", qtd_jogadores);
    exibir_pecas_jogador(pecas, '1');
    exibir_pecas_jogador(pecas, '2');
    exibir_mesa(&mesa);

    primeiro_jogador = definir_primeiro_jogador(pecas); // REQ10
    printf("\nO jogador %c fara a primeira jogada!\n", primeiro_jogador);

    indice_compra = comprar_peca(pecas, '1');           // REQ11
    if (indice_compra != -1) {
        printf("Jogador 1 comprou [%d|%d]\n", pecas[indice_compra].lado_a, pecas[indice_compra].lado_b);
    }

    printf("Peca [3|5] valida na extremidade -1 (mesa vazia)? %s\n", // REQ12
           jogada_valida(pecas[0], mesa.extremidade_esquerda) ? "SIM" : "NAO");

    return 0;
}
