#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "arquivo.h"
#include "random.h"
#include "pilha.h"
#include "fila.h"

// Define o comando correto de limpeza de acordo com o Sistema Operacional
#ifdef _WIN32
    #define LIMPAR_TELA "cls"
#else
    #define LIMPAR_TELA "clear"
#endif

// Função auxiliar para pausar o e limpar
void pausar() {
    printf("\nPressione ENTER para continuar...");
    fflush(stdout);
    getchar(); // Captura o ENTER pendente
    getchar(); // Aguarda a interação do utilizador
}

int main(){
    int op;
    inicializarSorteio();
    
    Ingresso filmes[MAX_QTD_FILMES];
    Cliente clientes[MAX_QTD_CLIENTES];
    
    int totalFilmes = carregarFilmes(filmes, MAX_QTD_FILMES);
    int totalClientes = carregarClientes(clientes, MAX_QTD_CLIENTES);
    distribuirFilmes(filmes, totalFilmes);

    // Fila Principal de Compras (Fila Inicial)
    FilaCirc filaEntrada;
    inicializaFila(&filaEntrada);

    // Pilhas de Ingressos (Uma pilha para cada filme)
    PilhaEst pilhasIngressos[MAX_QTD_FILMES];
    
    // Inicializa todas as pilhas logo no início do programa
    for(int i = 0; i < MAX_QTD_FILMES; i++){
        inicializaPilha(&pilhasIngressos[i]);
    }

    // Filas de Exibição (Uma fila para cada sala de cinema)
    FilaCirc filasSalas[MAX_SALAS];
    for(int i = 0; i < MAX_SALAS; i++){
        inicializaFila(&filasSalas[i]);
    }

    int dadosCarregados = 0; // Variável de controlo para saber se já preencheu tudo

    do{
        system(LIMPAR_TELA); // <--- LIMPA O ECRÃ AO RETORNAR AO MENU PRINCIPAL

        printf("=== CINE CAPI - CINEMA BARONI ===\n");
        printf("1 - Preencher Fila de Entrada e Pilhas de Ingressos (Auto)\n");
        printf("2 - Vender Ingresso (Processar Fila ate o fim)\n");
        printf("3 - Listar Filas de Exibicao das Salas\n");
        printf("4 - Ver Fila de Espera Inicial\n");
        printf("5 - Ver Pilhas de Ingressos Disponiveis\n");
        printf("6 - Listar Todos os Filmes do Sistema\n");
        printf("7 - Listar Todos os Clientes Cadastrados\n");
        printf("0 - Sair do cinema Baroni\n");
        printf("Opcao: ");
        fflush(stdout);
        scanf(" %d", &op);

        switch (op) {
        case 1:
            system(LIMPAR_TELA);
            if(dadosCarregados == 1){
                printf("\n[AVISO] Fila e Pilhas ja foram preenchidas!\n");
            } else {
                preencherFilaClientes(&filaEntrada, clientes, totalClientes);
                preencherPilhasIngressos(pilhasIngressos, filmes, totalFilmes);
                dadosCarregados = 1;
                printf("\n[SUCESSO] Fila de compras preenchida com %d clientes!\n", totalClientes);
                printf("[SUCESSO] Pilhas de ingressos geradas para os filmes de hoje!\n");
            }
            pausar();
            break;

        case 2:
            system(LIMPAR_TELA);
            if(vaziaFila(&filaEntrada)){
                printf("\nNao ha clientes na fila inicial de compra! (Execute a Opcao 1 primeiro)\n");
                pausar();
                break;
            }

            int modoVenda = 0;
            printf("\n--- MODO DE VENDA DE INGRESSOS ---\n");
            printf("1 - Escolher 2 manualmente + Preencher o restante automaticamente\n");
            printf("2 - Escolher TODOS manualmente\n");
            printf("Escolha a opcao: ");
            fflush(stdout);
            scanf(" %d", &modoVenda);

            if(modoVenda != 1 && modoVenda != 2){
                printf("\nOpcao invalida de venda!\n");
                pausar();
                break;
            }

            system(LIMPAR_TELA); // Limpa para mostrar o fluxo de atendimento
            printf("--- PROCESSANDO VENDA DE INGRESSOS ---\n");
            
            int clientesAtendidos = 0;

            while(!vaziaFila(&filaEntrada)){
                int disponiveis[MAX_QTD_FILMES];
                int totalDisp = 0;

                for(int i = 0; i < totalFilmes; i++){
                    if(filmes[i].amanha == 0 && !vaziaPilha(&pilhasIngressos[i])){
                        disponiveis[totalDisp] = i;
                        totalDisp++;
                    }
                }

                if(totalDisp == 0){
                    printf("\n[AVISO] Ingressos esgotados para todos os filmes de hoje!\n");
                    break;
                }

                Cliente clienteAtual = desenfileirar(&filaEntrada);
                clientesAtendidos++;

                int escolhaFilme = -1;

                // Modo Automático a partir do 3º cliente
                if(modoVenda == 1 && clientesAtendidos > 2){
                    int indiceSorteado = rand() % totalDisp;
                    escolhaFilme = disponiveis[indiceSorteado];
                    printf("\n[AUTO %d] Atendendo: %-25s -> Filme Sorteado: %s", 
                           clientesAtendidos, clienteAtual.nome, filmes[escolhaFilme].filme);
                } 
                // Modo Manual (2 primeiros do modo 1 OU todos do modo 2)
                else {
                    printf("\n------------------------------------------------\n");
                    printf("Atendendo Cliente [%d]: %s (Idade: %d)\n", clientesAtendidos, clienteAtual.nome, clienteAtual.idade);
                    printf("Filmes Disponiveis Hoje:\n");
                    
                    for(int i = 0; i < totalDisp; i++){
                        int idx = disponiveis[i];
                        printf(" [%d] %s - Sala %d (%s) - R$%.2f\n", 
                               idx, filmes[idx].filme, filmes[idx].sala, filmes[idx].horario, filmes[idx].preco);
                    }

                    int opcaoValida = 0;
                    do {
                        printf("Escolha o codigo do filme para %s: ", clienteAtual.nome);
                        fflush(stdout);
                        scanf(" %d", &escolhaFilme);

                        if(escolhaFilme >= 0 && escolhaFilme < totalFilmes){
                            if(filmes[escolhaFilme].amanha == 0 && !vaziaPilha(&pilhasIngressos[escolhaFilme])){
                                opcaoValida = 1;
                            } else {
                                printf("Filme sem ingressos ou indisponivel. Tente outro.\n");
                            }
                        } else {
                            printf("Opcao invalida!\n");
                        }
                    } while(!opcaoValida);
                }

                int indiceFilmeComprado = pop(&pilhasIngressos[escolhaFilme]);
                clienteAtual.ingresso = filmes[indiceFilmeComprado];

                int numSala = clienteAtual.ingresso.sala - 1;
                enfileirar(&filasSalas[numSala], clienteAtual);
            }

            printf("\n\n[SUCESSO] Processamento de vendas concluido para todos os clientes!\n");
            pausar();
            break;

        case 3:
            system(LIMPAR_TELA);
            printf("===== FILAS DE EXIBICAO DAS SALAS =====\n");
            for(int s = 0; s < MAX_SALAS; s++){
                printf("\n--- Sala %d ---\n", s + 1);
                if(vaziaFila(&filasSalas[s])){
                    printf("  (Nenhum cliente comprou ingresso para esta sala ainda. Execute a Opcao 2)\n");
                } else {
                    imprimirFila(&filasSalas[s]);
                }
            }
            pausar();
            break;

        case 4:
            system(LIMPAR_TELA);
            printf("===== FILA INICIAL DE ESPERA =====\n");
            if(vaziaFila(&filaEntrada)){
                if(dadosCarregados == 0){
                    printf("  (A fila ainda nao foi preenchida. Execute a Opcao 1 primeiro!)\n");
                } else {
                    printf("  (Todos os clientes da fila ja foram atendidos na Opcao 2!)\n");
                }
            } else {
                imprimirFila(&filaEntrada);
            }
            pausar();
            break;

        case 5:
            system(LIMPAR_TELA);
            printf("===== PILHAS DE INGRESSOS DISPONIVEIS =====\n");
            for(int i = 0; i < totalFilmes; i++){
                if(filmes[i].amanha == 0){
                    printf("\nFilme: %-30s\n", filmes[i].filme);
                    if(vaziaPilha(&pilhasIngressos[i])){
                        printf("  -> [SEM INGRESSOS / PILHA VAZIA]\n");
                    } else {
                        printf("  -> Elementos na Pilha (Indices do filme):\n");
                        imprimirPilha(&pilhasIngressos[i]);
                    }
                }
            }
            pausar();
            break;

        case 6:
            system(LIMPAR_TELA);
            printf("===== MOSTRAR FILMES E HORARIOS =====\n");
            for(int i = 0; i < totalFilmes; i++){
                printf("Filme: %s\n", filmes[i].filme);
                if(filmes[i].amanha == 0){
                    printf("Sala: %d\n", filmes[i].sala);
                } else {
                    printf("Tem horario para amanha\n");
                }
                printf("Horario: %s\n", filmes[i].horario);
                printf("Preco: R$%.2f\n\n", filmes[i].preco);
            }
            pausar();
            break;

        case 7:
            system(LIMPAR_TELA);
            printf("===== MOSTRAR CLIENTES CADASTRADOS =====\n");
            for(int i = 0; i < totalClientes; i++){
                printf("Cliente: %s\n", clientes[i].nome);
                printf("Idade: %d\n", clientes[i].idade);
                if(clientes[i].genero == 'M'){
                    printf("Genero: Masculino\n\n");
                } else {
                    printf("Genero: Feminino\n\n");
                }
            }
            pausar();
            break;

        case 0:
            system(LIMPAR_TELA);
            printf("Saindo do cinema Baroni...\n");
            break;

        default:
            system(LIMPAR_TELA);
            printf("Nao existe esse caminho no cinema Baroni.\n");
            pausar();
            break;
        }
    } while(op != 0);

    return 0;
}
