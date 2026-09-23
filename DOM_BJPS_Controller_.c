//DOM_BJPS_Controller - Projeto Dominó LP2026
//13/08/2026
//Bruna, João Pedro Freitas Vilar, Pedru Gama, Samira

#include "DOM_BJPS_Controller_.h"
#include "DOM_BJPS_View_.h"
#include "DOM_BJPS_Model_.h"
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

void determinar_quantidade_jogadores(EstadoJogo *jogo) {
    int qtd = 0;
    while (qtd != 1 && qtd != 2) {
        limpar_tela();
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

void distribuir_pecas_iniciais(EstadoJogo *jogo) {
    int i;
    jogo->indice_compra = 0;

    for (i = 0; i < 7; i++) {
        jogo->jogadores[0].mao[i] = jogo->conjunto.pecas_atuais[jogo->indice_compra];
        jogo->jogadores[0].mao[i].status = COM_JOGADOR1;
        jogo->jogadores[0].qtd_mao++;
        jogo->indice_compra++;

        jogo->jogadores[1].mao[i] = jogo->conjunto.pecas_atuais[jogo->indice_compra];
        jogo->jogadores[1].mao[i].status = COM_JOGADOR2;
        jogo->jogadores[1].qtd_mao++;
        jogo->indice_compra++;
    }
}

void definir_primeiro_jogador(EstadoJogo *jogo) {
    int duplo, i;
    int idx_vencedor = -1;
    int idx_peca = -1;

    for (duplo = 6; duplo >= 0 && idx_vencedor == -1; duplo--) {
        for (i = 0; i < jogo->jogadores[0].qtd_mao; i++) {
            if (jogo->jogadores[0].mao[i].lado_a == duplo && jogo->jogadores[0].mao[i].lado_b == duplo) {
                idx_vencedor = 0; idx_peca = i; break;
            }
        }
        if (idx_vencedor == -1) {
            for (i = 0; i < jogo->jogadores[1].qtd_mao; i++) {
                if (jogo->jogadores[1].mao[i].lado_a == duplo && jogo->jogadores[1].mao[i].lado_b == duplo) {
                    idx_vencedor = 1; idx_peca = i; break;
                }
            }
        }
    }

    if (idx_vencedor == -1) {
        // Ninguem tem dobrada: jogador 1 comeca normalmente
        jogo->jogador_atual = 0;
        exibir_primeiro_jogador(1);
        return;
    }

    // Joga a dobrada automaticamente na mesa
    Jogador *j = &jogo->jogadores[idx_vencedor];
    PecaDomino peca = j->mao[idx_peca];
    MesaDomino *mesa = &jogo->mesa;

    mesa->pecas[0] = peca;
    mesa->quantidade = 1;
    mesa->extremidade_esquerda = peca.lado_a;
    mesa->extremidade_direita = peca.lado_b;

    int k;
    for (k = idx_peca; k < j->qtd_mao - 1; k++) j->mao[k] = j->mao[k + 1];
    j->qtd_mao--;

    exibir_primeiro_jogador(idx_vencedor + 1);

    // Primeira jogada ja feita: passa a vez pro outro jogador
    jogo->jogador_atual = (idx_vencedor == 0) ? 1 : 0;
}

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

int validar_jogada(PecaDomino peca, int extremidade) {
    return (peca.lado_a == extremidade || peca.lado_b == extremidade);
}

void finalizar_jogo(EstadoJogo *jogo) {
    jogo->jogo_ativo = 0;
    exibir_mensagem("Partida finalizada!");
    aguardar_enter();
}

// REQ21: Soma um ponto no placar do jogador vencedor (idx_vencedor: 0 ou 1)
void registrar_vitoria(EstadoJogo *jogo, int idx_vencedor) {
    if (idx_vencedor == 0) {
        jogo->placar_jogador1++;
    } else {
        jogo->placar_jogador2++;
    }
    exibir_placar(jogo->placar_jogador1, jogo->placar_jogador2);
    aguardar_enter();
}

// REQ20: Inteligencia do Computador (IA)
void processar_turno_ia(EstadoJogo *jogo) {
    Jogador *j = &jogo->jogadores[1];
    MesaDomino *mesa = &jogo->mesa;
    int i, k;

    exibir_mensagem("Turno do Computador (Jogador 2)...");

    // Mesa vazia: joga a primeira peça
    if (mesa->quantidade == 0) {
        PecaDomino peca = j->mao[0];
        mesa->pecas[0] = peca;
        mesa->quantidade = 1;
        mesa->extremidade_esquerda = peca.lado_a;
        mesa->extremidade_direita = peca.lado_b;

        for (k = 0; k < j->qtd_mao - 1; k++) j->mao[k] = j->mao[k + 1];
        j->qtd_mao--;

        exibir_mensagem("O Computador iniciou a mesa!");
        jogo->jogador_atual = 0;
        return;
    }

    // Procura por peça válida priorizando as de maior valor (duplas e maiores somas)
    int melhor_idx = -1;
    int melhor_lado = 0; // 1 = Esquerda, 2 = Direita
    int maior_pontuacao = -1;

    for (i = 0; i < j->qtd_mao; i++) {
        PecaDomino peca = j->mao[i];
        int val_a = peca.lado_a;
        int val_b = peca.lado_b;
        int pontuacao = val_a + val_b + (val_a == val_b ? 10 : 0);

        if (validar_jogada(peca, mesa->extremidade_esquerda)) {
            if (pontuacao > maior_pontuacao) {
                maior_pontuacao = pontuacao;
                melhor_idx = i;
                melhor_lado = 1;
            }
        }
        if (validar_jogada(peca, mesa->extremidade_direita)) {
            if (pontuacao > maior_pontuacao) {
                maior_pontuacao = pontuacao;
                melhor_idx = i;
                melhor_lado = 2;
            }
        }
    }

    // Se encontrou jogada
    if (melhor_idx != -1) {
        PecaDomino peca = j->mao[melhor_idx];
        int ext = (melhor_lado == 1) ? mesa->extremidade_esquerda : mesa->extremidade_direita;

        if (melhor_lado == 1) {
            if (peca.lado_b != ext) {
                int temp = peca.lado_a;
                peca.lado_a = peca.lado_b;
                peca.lado_b = temp;
            }
            for (i = mesa->quantidade; i > 0; i--) mesa->pecas[i] = mesa->pecas[i - 1];
            mesa->pecas[0] = peca;
            mesa->extremidade_esquerda = peca.lado_a;
            mesa->quantidade++;
        } else {
            if (peca.lado_a != ext) {
                int temp = peca.lado_a;
                peca.lado_a = peca.lado_b;
                peca.lado_b = temp;
            }
            mesa->pecas[mesa->quantidade] = peca;
            mesa->extremidade_direita = peca.lado_b;
            mesa->quantidade++;
        }

        for (k = melhor_idx; k < j->qtd_mao - 1; k++) j->mao[k] = j->mao[k + 1];
        j->qtd_mao--;

        exibir_mensagem("O Computador realizou uma jogada!");

        if (j->qtd_mao == 0) {
            limpar_tela();
            exibir_mesa(mesa);
            exibir_vencedor(2);
            registrar_vitoria(jogo, 1); // REQ21
            finalizar_jogo(jogo);
            return;
        }

        jogo->jogador_atual = 0;
    } else {
        // Se nao tem peca, tenta comprar
        if (comprar_peca(jogo, 1)) {
            exibir_mensagem("O Computador comprou uma peca do monte.");
        } else {
            exibir_mensagem("O Computador nao possui jogadas e passou a vez.");
            jogo->jogador_atual = 0;
        }
    }
}

void processar_turno(EstadoJogo *jogo) {
    char acao;
    int idx_atual = jogo->jogador_atual;
    Jogador *j = &jogo->jogadores[idx_atual];
    MesaDomino *mesa = &jogo->mesa;

    limpar_tela();
    exibir_mesa(mesa);

    // Se for a vez da IA (Computador)
    if (j->eh_computador) {
        processar_turno_ia(jogo);
        return;
    }

    if (idx_atual == 0) {
        exibir_mao_jogador(1, j->mao, j->qtd_mao);
        exibir_status_adversario_oculto(2, jogo->jogadores[1].qtd_mao);
    } else {
        exibir_mao_jogador(2, j->mao, j->qtd_mao);
        exibir_status_adversario_oculto(1, jogo->jogadores[0].qtd_mao);
    }

    exibir_menu_jogo(idx_atual);
    acao = ler_acao_turno();

    if (acao == 'J' || acao == 'j') {
        int num_peca, lado, i;
        num_peca = ler_numero_peca(j->qtd_mao);

        if (num_peca < 1 || num_peca > j->qtd_mao) {
            exibir_mensagem("Peca invalida!");
            aguardar_enter();
            return;
        }

        PecaDomino peca = j->mao[num_peca - 1];

        if (mesa->quantidade == 0) {
            mesa->pecas[0] = peca;
            mesa->quantidade = 1;
            mesa->extremidade_esquerda = peca.lado_a;
            mesa->extremidade_direita = peca.lado_b;
        } else {
            int cabe_esquerda = validar_jogada(peca, mesa->extremidade_esquerda);
            int cabe_direita  = validar_jogada(peca, mesa->extremidade_direita);

            if (!cabe_esquerda && !cabe_direita) {
                exibir_mensagem("Jogada invalida! A peca nao bate com nenhuma extremidade.");
                aguardar_enter();
                return;
            }

            if (cabe_esquerda && cabe_direita) {
                lado = ler_lado_jogada();   // so pergunta se for realmente ambiguo
            } else {
                lado = cabe_esquerda ? 1 : 2;  // joga automaticamente pro lado certo
            }

            int ext = (lado == 1) ? mesa->extremidade_esquerda : mesa->extremidade_direita;

            if (lado == 1) {
                if (peca.lado_b != ext) { int temp = peca.lado_a; peca.lado_a = peca.lado_b; peca.lado_b = temp; }
                for (i = mesa->quantidade; i > 0; i--) mesa->pecas[i] = mesa->pecas[i - 1];
                mesa->pecas[0] = peca;
                mesa->extremidade_esquerda = peca.lado_a;
                mesa->quantidade++;
            } else {
                if (peca.lado_a != ext) { int temp = peca.lado_a; peca.lado_a = peca.lado_b; peca.lado_b = temp; }
                mesa->pecas[mesa->quantidade] = peca;
                mesa->extremidade_direita = peca.lado_b;
                mesa->quantidade++;
            }
}

        int k;
        for (k = num_peca - 1; k < j->qtd_mao - 1; k++) j->mao[k] = j->mao[k + 1];
        j->qtd_mao--;

        if (j->qtd_mao == 0) {
            limpar_tela();
            exibir_mesa(mesa);
            exibir_vencedor(idx_atual + 1);
            registrar_vitoria(jogo, idx_atual); // REQ21
            finalizar_jogo(jogo);
            return;
        }

        jogo->jogador_atual = (idx_atual == 0) ? 1 : 0;

    } else if (acao == 'C' || acao == 'c') {
        comprar_peca(jogo, idx_atual);
        aguardar_enter();
    } else if (acao == 'P' || acao == 'p') {
        exibir_mensagem("Jogador passou a vez.");
        aguardar_enter();
        jogo->jogador_atual = (idx_atual == 0) ? 1 : 0;
    } else if (acao == 'S' || acao == 's') { // REQ18: Salvar
        if (salvar_estado_jogo(jogo)) {
            exibir_mensagem("Jogo salvo com sucesso!");
            aguardar_enter();
        } else {
            exibir_mensagem("Erro ao salvar o jogo!");
            aguardar_enter();
        }
    } else if (acao == 'F' || acao == 'f') {
        finalizar_jogo(jogo);
    } else {
        exibir_mensagem("Opcao invalida!");
        aguardar_enter();
    }
}

void iniciar_partida_domino(EstadoJogo *jogo) {
    reiniciar_partida(&jogo->conjunto);
    inicializar_mesa(&jogo->mesa);
    determinar_quantidade_jogadores(jogo);
    distribuir_pecas_iniciais(jogo);
    definir_primeiro_jogador(jogo);

    jogo->jogo_ativo = 1;

    while (jogo->jogo_ativo) {
        processar_turno(jogo);
    }
}

void executar_sistema(void) {
    srand((unsigned int)time(NULL));

    EstadoJogo jogo;
    inicializar_conjunto(&jogo.conjunto);
    inicializar_placar(&jogo); // REQ21: placar comeca em 0x0 para esta sequencia de partidas

    int opcao = -1;

    while (opcao != 0) {
        limpar_tela();
        exibir_menu();
        opcao = solicitar_opcao();

        limpar_tela();
                switch (opcao) {
                    case 1:
                        exibir_pecas("PECAS ORDENADAS", jogo.conjunto.pecas_ordenadas, TOTAL_PECAS);
                        aguardar_enter();
                        break;

                    case 2:
                        exibir_pecas("PECAS ATUAIS (EMBARALHADAS)", jogo.conjunto.pecas_atuais, TOTAL_PECAS);
                        aguardar_enter();
                        break;

                    case 3:
                        embaralhar_conjunto(&jogo.conjunto);
                        exibir_mensagem("As pecas foram embaralhadas com sucesso!");
                        aguardar_enter();
                        break;

                    case 4:
                        reiniciar_partida(&jogo.conjunto);
                        exibir_mensagem("Nova partida preparada! Pecas resetadas e embaralhadas.");
                        aguardar_enter();
                        break;

                    case 5:
                        iniciar_partida_domino(&jogo);
                        break;

                    case 6:
                        if (carregar_estado_jogo(&jogo)) {
                            exibir_mensagem("Jogo carregado com sucesso!");
                            exibir_placar(jogo.placar_jogador1, jogo.placar_jogador2); // REQ21: placar vem junto do save
                            aguardar_enter();
                            jogo.jogo_ativo = 1;
                            while (jogo.jogo_ativo) {
                                processar_turno(&jogo);
                            }
                        } else {
                            exibir_mensagem("Nenhum jogo salvo foi encontrado!");
                            aguardar_enter();
                        }   
                        break;

                    case 7:
                        exibir_regras_jogo();
                        aguardar_enter();
                        break;

                    case 8: // REQ21
                        exibir_placar(jogo.placar_jogador1, jogo.placar_jogador2);
                        aguardar_enter();
                        break;

                    case 0:
                        exibir_mensagem("Encerrando a aplicacao. Ate logo!");
                        break;

                    default:
                        exibir_mensagem("Opcao invalida! Tente novamente.");
                        aguardar_enter();
                        break;
                }
    }
}