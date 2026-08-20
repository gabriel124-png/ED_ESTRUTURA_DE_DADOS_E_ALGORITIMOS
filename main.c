#include <stdio.h>
#include <string.h>
#include "arquivo.h"
#include "random.h"

int main(){
    int op;
    inicializarSorteio();
    Ingresso filmes[MAX_QTD_FILMES];
    Cliente clientes[MAX_QTD_CLIENTES];
    int totalFilmes = carregarFilmes(filmes, MAX_QTD_FILMES);
    int totalClientes = carregarClientes(clientes, MAX_QTD_CLIENTES);

    do{
        printf("\n===RECEPCAO===\n");
        printf("3 - Sortear ingresso automatico\n");
        printf("2 - Listar clientes\n");
        printf("1 - Listar filmes\n");
        printf("0 - Sair do cinema Baroni\n");
        scanf("%d",&op);
        switch (op)
        {
        case 3:
            if(totalFilmes > 0 && totalClientes > 0){
                Ingresso filmeSorteado = sortearFilme(filmes, totalFilmes);
                Cliente clienteSorteado = sortearCliente(clientes, totalClientes);
                printf("\n--- INGRESSO SORTEADO ---\n");
                printf("Cliente: %s\n", clienteSorteado.nome);
                printf("Filme:   %s\n", filmeSorteado.filme);
                printf("Sala:    %d\n", filmeSorteado.sala);
                printf("Horario: %s\n", filmeSorteado.horario);
                printf("Preco:   R$ %.2f\n", filmeSorteado.preco);
            } else {
                printf("Nao ha filmes ou clientes carregados para sortear.\n");
            }
            break;
        case 2:
            lerClientes();
            break;
        case 1:
            lerFilmes();
            break;

        case 0:
            printf("Saida\n");
            break;

        default:
            printf("Não existe esse caminho no cinema Baroni\n");
            break;
        }
    }while(op != 0);

    return 0;
}