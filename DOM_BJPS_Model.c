//DOM_BJPS_Model - Projeto Dominó LP2026
//13/08/2026
//Bruna, João Pedro Freitas Vilar, Pedru Gama, Samira

#include "DOM_BJPS_Model.h"
#include <stdlib.h>

void inicializar_conjunto(ConjuntoDomino *conjunto) {
    int idx = 0;
    // REQ01: Monta o conjunto completo (0 a 6)
    for (int i = 0; i <= 6; i++) {
        for (int j = i; j <= 6; j++) {
            conjunto->pecas_ordenadas[idx].lado_a = i;
            conjunto->pecas_ordenadas[idx].lado_b = j;
            conjunto->pecas_atuais[idx] = conjunto->pecas_ordenadas[idx];
            idx++;
        }
    }
}

void embaralhar_conjunto(ConjuntoDomino *conjunto) {
    int i, j;
    PecaDomino temp;
    
    // REQ02: Embaralhamento Fisher-Yates
    for (i = TOTAL_PECAS - 1; i > 0; i--) {
        j = rand() % (i + 1);
        
        temp = conjunto->pecas_atuais[i];
        conjunto->pecas_atuais[i] = conjunto->pecas_atuais[j];
        conjunto->pecas_atuais[j] = temp;
    }
}

void reiniciar_partida(ConjuntoDomino *conjunto) {
    // REQ03: Prepara nova partida e re-embaralha
    inicializar_conjunto(conjunto);
    embaralhar_conjunto(conjunto);
}
