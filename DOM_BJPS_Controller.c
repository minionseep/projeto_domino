//DOM_BJPS_Controller - Projeto Dominó LP2026
//13/08/2026
//Bruna, João Pedro Freitas Vilar, Pedru Gama, Samira
#include "DOM_BJPS_Controller.h"
#include "DOM_BJPS_Model.h"
#include "DOM_BJPS_View.h"
#include <stdlib.h>
#include <time.h>

void executar_sistema(void) {
    // Semente para os números aleatórios do Dev-C++
    srand((unsigned int)time(NULL));

    ConjuntoDomino conjunto;
    inicializar_conjunto(&conjunto);

    int opcao = -1;

    while (opcao != 0) {
        exibir_menu();
        opcao = solicitar_opcao();

        switch (opcao) {
            case 1:
                exibir_pecas("PECAS ORDENADAS", conjunto.pecas_ordenadas, TOTAL_PECAS);
                break;

            case 2:
                exibir_pecas("PECAS ATUAIS (EMBARALHADAS)", conjunto.pecas_atuais, TOTAL_PECAS);
                break;

            case 3:
                embaralhar_conjunto(&conjunto);
                exibir_mensagem("As pecas foram embaralhadas com sucesso!");
                break;

            case 4:
                reiniciar_partida(&conjunto);
                exibir_mensagem("Nova partida preparada! Pecas resetadas e embaralhadas.");
                break;

            case 0:
                exibir_mensagem("Encerrando a aplicacao. Ate logo!");
                break;

            default:
                exibir_mensagem("Opcao invalida! Tente novamente.");
                break;
        }
    }
}
