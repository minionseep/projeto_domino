//DOM_BJPS_Controller - Projeto Dominó LP2026
//13/08/2026
//Bruna, João Pedro Freitas Vilar, Pedru Gama, Samira
#include "DOM_BJPS_Controller.h"
#include "DOM_BJPS_View.c"
#include <stdlib.h>
#include <time.h>

// REQ07: Determina quantidade de jogadores (1 ou 2)
void determinar_quantidade_jogadores(EstadoJogo *jogo) {
    int qtd = 0;
    while (qtd != 1 && qtd != 2) {
        qtd = ler_quantidade_jogadores();
    }
    jogo->num_jogadores = qtd;
    jogo->jogadores[0].id = 1;
    jogo->jogadores[0].eh_computador = 0;
    jogo->jogadores[0].qtd_mao = 0;

    jogo->jogadores[1].id = 2;
    jogo->jogadores[1].eh_computador = (qtd == 1) ? 1 : 0;
    jogo->jogadores[1].qtd_mao = 0;
}

// REQ08: Distribui aleatoriamente 7 peças para cada jogador
void distribuir_pecas_iniciais(EstadoJogo *jogo) {
    int i;
    jogo->indice_compra = 0;

    for (i = 0; i < 7; i++) {
        // Jogador 1
        jogo->jogadores[0].mao[i] = jogo->conjunto.pecas_atuais[jogo->indice_compra];
        jogo->jogadores[0].mao[i].status = COM_JOGADOR1;
        jogo->jogadores[0].qtd_mao++;
        jogo->indice_compra++;

        // Jogador 2
        jogo->jogadores[1].mao[i] = jogo->conjunto.pecas_atuais[jogo->indice_compra];
        jogo->jogadores[1].mao[i].status = COM_JOGADOR2;
        jogo->jogadores[1].qtd_mao++;
        jogo->indice_compra++;
    }
}

// REQ10: Define o primeiro jogador a jogar
void definir_primeiro_jogador(EstadoJogo *jogo) {
    int i;
    int maior_duplo_p1 = -1, maior_duplo_p2 = -1;

    for (i = 0; i < 7; i++) {
        if (jogo->jogadores[0].mao[i].lado_a == jogo->jogadores[0].mao[i].lado_b) {
            if (jogo->jogadores[0].mao[i].lado_a > maior_duplo_p1)
                maior_duplo_p1 = jogo->jogadores[0].mao[i].lado_a;
        }
        if (jogo->jogadores[1].mao[i].lado_a == jogo->jogadores[1].mao[i].lado_b) {
            if (jogo->jogadores[1].mao[i].lado_a > maior_duplo_p2)
                maior_duplo_p2 = jogo->jogadores[1].mao[i].lado_a;
        }
    }

    if (maior_duplo_p1 > maior_duplo_p2) {
        jogo->jogador_atual = 0;
    } else if (maior_duplo_p2 > maior_duplo_p1) {
        jogo->jogador_atual = 1;
    } else {
        jogo->jogador_atual = 0;
    }
    
    exibir_primeiro_jogador(jogo->jogador_atual + 1);
}

// REQ11 / REQ16: Comprar peças disponíveis
int comprar_peca(EstadoJogo *jogo, int idx_jogador) {
    if (jogo->indice_compra >= TOTAL_PECAS) {
        exibir_mensagem("Monte de compras vazio! Nao ha mais pecas para comprar.");
        return 0;
    }

    Jogador *j = &jogo->jogadores[idx_jogador];
    PecaDomino peca_comprada = jogo->conjunto.pecas_atuais[jogo->indice_compra];
    peca_comprada.status = (idx_jogador == 0) ? COM_JOGADOR1 : COM_JOGADOR2;

    j->mao[j->qtd_mao] = peca_comprada;
    j->qtd_mao++;
    jogo->indice_compra++;

    exibir_mensagem("Peca comprada com sucesso!");
    return 1;
}

// REQ12: Verifica se a jogada é válida
int validar_jogada(PecaDomino peca, int extremidade) {
    return (peca.lado_a == extremidade || peca.lado_b == extremidade);
}

// REQ15: Finalizar jogo
void finalizar_jogo(EstadoJogo *jogo) {
    jogo->jogo_ativo = 0;
    exibir_mensagem("Partida finalizada!");
}

// Lógica para os turnos do jogo
void processar_turno(EstadoJogo *jogo) {
    char acao;
    int idx_atual = jogo->jogador_atual;
    Jogador *j = &jogo->jogadores[idx_atual];
    MesaDomino *mesa = &jogo->mesa;

    exibir_mesa(mesa);
    
    if (idx_atual == 0) {
        exibir_mao_jogador(1, j->mao, j->qtd_mao);                     // REQ13
        exibir_status_adversario_oculto(2, jogo->jogadores[1].qtd_mao); // REQ14
    } else {
        if (!j->eh_computador) {
            exibir_mao_jogador(2, j->mao, j->qtd_mao);                 // REQ13
            exibir_status_adversario_oculto(1, jogo->jogadores[0].qtd_mao); // REQ14
        }
    }

    exibir_menu_jogo(idx_atual);
    acao = ler_acao_turno();

    if (acao == 'J' || acao == 'j') {
        int num_peca, lado;
        num_peca = ler_numero_peca(j->qtd_mao);

        if (num_peca < 1 || num_peca > j->qtd_mao) {
            exibir_mensagem("Peca invalida!");
            return;
        }

        PecaDomino peca = j->mao[num_peca - 1];

        if (mesa->quantidade == 0) {
            mesa->pecas[0] = peca;
            mesa->quantidade = 1;
            mesa->extremidade_esquerda = peca.lado_a;
            mesa->extremidade_direita = peca.lado_b;
        } else {
            lado = ler_lado_jogada();

            int ext = (lado == 1) ? mesa->extremidade_esquerda : mesa->extremidade_direita;

            if (!validar_jogada(peca, ext)) { // REQ12
                exibir_mensagem("Jogada invalida! A peca nao bate com a extremidade.");
                return;
            }

            if (lado == 1) {
                int novo_ext = (peca.lado_a == ext) ? peca.lado_b : peca.lado_a;
                mesa->extremidade_esquerda = novo_ext;
            } else {
                int novo_ext = (peca.lado_a == ext) ? peca.lado_b : peca.lado_a;
                mesa->extremidade_direita = novo_ext;
            }
            mesa->pecas[mesa->quantidade++] = peca;
        }

        // Remove da mão
        int k;
        for (k = num_peca - 1; k < j->qtd_mao - 1; k++) {
            j->mao[k] = j->mao[k + 1];
        }
        j->qtd_mao--;

        if (j->qtd_mao == 0) {
            exibir_vencedor(idx_atual + 1);
            finalizar_jogo(jogo);
            return;
        }

        jogo->jogador_atual = (idx_atual == 0) ? 1 : 0;

    } else if (acao == 'C' || acao == 'c') { // REQ11 / REQ16
        comprar_peca(jogo, idx_atual);
    } else if (acao == 'P' || acao == 'p') {
        exibir_mensagem("Jogador passou a vez.");
        jogo->jogador_atual = (idx_atual == 0) ? 1 : 0;
    } else if (acao == 'F' || acao == 'f') { // REQ15
        finalizar_jogo(jogo);
    } else {
        exibir_mensagem("Opcao invalida!");
    }
}

void iniciar_partida_domino(EstadoJogo *jogo) {
    reiniciar_partida(&jogo->conjunto);  // REQ03
    inicializar_mesa(&jogo->mesa);      // REQ09
    determinar_quantidade_jogadores(jogo); // REQ07
    distribuir_pecas_iniciais(jogo);    // REQ08
    definir_primeiro_jogador(jogo);     // REQ10

    jogo->jogo_ativo = 1;

    while (jogo->jogo_ativo) {
        processar_turno(jogo);
    }
}

void executar_sistema(void) {
    srand((unsigned int)time(NULL));

    EstadoJogo jogo;
    inicializar_conjunto(&jogo.conjunto);

    int opcao = -1;

    while (opcao != 0) {
        exibir_menu();
        opcao = solicitar_opcao();

        switch (opcao) {
            case 1:
                exibir_pecas("PECAS ORDENADAS", jogo.conjunto.pecas_ordenadas, TOTAL_PECAS);
                break;

            case 2:
                exibir_pecas("PECAS ATUAIS (EMBARALHADAS)", jogo.conjunto.pecas_atuais, TOTAL_PECAS);
                break;

            case 3:
                embaralhar_conjunto(&jogo.conjunto);
                exibir_mensagem("As pecas foram embaralhadas com sucesso!");
                break;

            case 4:
                reiniciar_partida(&jogo.conjunto);
                exibir_mensagem("Nova partida preparada! Pecas resetadas e embaralhadas.");
                break;

            case 5:
                iniciar_partida_domino(&jogo);
                break;

            case 6:
                exibir_regras_jogo(); // REQ17
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
