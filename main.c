#include <stdio.h>
#include <string.h>
#include "arquivo.h"
#include "random.h"
#include "pilha.h"

int main(){
    int op;
    inicializarSorteio();
    Ingresso filmes[MAX_QTD_FILMES];
    Cliente clientes[MAX_QTD_CLIENTES];
    int totalFilmes = carregarFilmes(filmes, MAX_QTD_FILMES);
    int totalClientes = carregarClientes(clientes, MAX_QTD_CLIENTES);
    distribuirFilmes(filmes, totalFilmes);
    PilhaEst pilhaIngressos;
    inicializaPilha(&pilhaIngressos);
    gerarIngressos(filmes, totalFilmes, totalClientes, &pilhaIngressos);

    do{
        printf("\n===RECEPCAO===\n");
	printf("5 - Verificar fila(nao implementado)\n");
	printf("4 - Verificar a fila\n");
        printf("3 - Verificar sala do filme\n");
        printf("2 - Listar clientes\n");
        printf("1 - Listar filmes\n");
        printf("0 - Sair do cinema Baroni\n");
        scanf("%d",&op);
        switch (op)
        {
	case 4:
		for(int i= pilhaIngressos.topo; i>=0;i--){
			int control = pilhaIngressos.itens[i];
			printf(" %s (%s) - Sala %d\n",filmes[control].filme, filmes[control].horario, filmes[control].sala );
		}
	break;
        case 3:
            for(int i =0; i<MAX_SALAS; i++){
                printf("\n=== Sala: %d ===\n", i+1);
                for(int j =0; j<totalFilmes; j++){
                    if(filmes[j].sala == i+1){
                        printf(" %s (%s)\n", filmes[j].filme, filmes[j].horario);
                    }
                }
            }
            printf("\n=== Filmes adiados para amanha ===\n");
       	     for(int j=0; j<totalFilmes; j++){
                if(filmes[j].amanha == 1){
                    printf(" %s (%s)\n", filmes[j].filme, filmes[j].horario);
                }
            }
        break;
        case 2:
            printf("=====Mostrar clientes no cinema=====\n");
		for(int i =0; i<totalClientes; i++){
			printf("Clientes: %s\n", clientes[i].nome);
			printf("Idade: %d\n", clientes[i].idade);
			if(clientes[i].genero == 'M'){
				printf("Masculino\n\n");
			}else{
				printf("Feminino\n\n");
			}
		}
        break;
        case 1:
            printf("=====Mostrar filmes e horarios=====\n");
		for(int i =0; i<totalFilmes; i++){
			printf("Filmes: %s\n", filmes[i].filme);
			if(filmes[i].amanha == 0){
				printf("Sala: %d\n", filmes[i].sala);
			}else{
				printf("Tem horario para amanha\n");
			}
			printf("Horario: %s\n", filmes[i].horario);
			printf("Preco: R$%.2f\n\n", filmes[i].preco);
		}
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
