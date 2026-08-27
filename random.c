#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>
#include "random.h"

void inicializarSorteio(){
    srand(time(NULL));
}

static void embaralharFilmes(Ingresso filmes[], int total){/* algoritimo fisher yates */
	for(int i = total -1; i>0; i--){
		int j = rand() % (i + 1); // sorteia uma posição entre 0 e i
		Ingresso tmp  = filmes[i]; // daqui até o fim do for metodo bublle sort
		filmes[i] = filmes[j];
		filmes[j] = tmp; // troca a posicao de i e j
	}
}

static int horarioparaminuto(char horario[]){
	int hora, minuto;
	sscanf(horario, "%d:%d", &hora, &minuto);
	return hora * 60 + minuto; // converte hora em minutos.
}
static int conflitodehorario(int inicio1, int inicio2, int fim1, int fim2){
	return (inicio1 < fim2) && (inicio2 < fim1); // impede a sobreposicao de horario.
}

void distribuirFilmes(Ingresso filmes[], int totalFilmes){
	embaralharFilmes(filmes, totalFilmes);
	int porSala = totalFilmes / MAX_SALAS;
	int quantSala [MAX_SALAS] = {0};
	int inicioSala[MAX_SALAS][MAX_QTD_FILMES];
	int fimSala[MAX_SALAS][MAX_QTD_FILMES];
	for(int i=0; i<totalFilmes; i++){
	    int colocado =0;
	    int inicioNovo = horarioparaminuto(filmes[i].horario);
	    int fimNovo = inicioNovo + filmes[i].duracao;
		for(int s=0; s< MAX_SALAS && !colocado; s++){
			if(quantSala[s] >= porSala) continue; /* verificar conflitos de horario na sala */
			int conflito =0;
			for(int h=0; h  < quantSala[s]; h++){
				if(conflitodehorario(inicioNovo, inicioSala[s][h], fimNovo, fimSala[s][h])){
					conflito =1; // variavel de controle dentro da condição.
					break;
				}
			}
			if(conflito) continue; // já tem filme nesse horario

			filmes[i].sala = s + 1;
			filmes[i].amanha = 0;
			inicioSala[s][quantSala[s]] = inicioNovo; // guarda os horarios de inicio dos filmes.
			fimSala[s][quantSala[s]] = fimNovo; // guarda os horarios do fim dos filmes.
			quantSala[s]++;
			colocado = 1;
		}
		if(!colocado){
			filmes[i].sala =0;
			filmes[i].amanha =1;
		}
	}
	for(int a =0; a<totalFilmes-1; a++){/* inicio do laco e condicoes do bublle sort */
				for(int b =0; b<totalFilmes-1-a; b++){
					int salabb = filmes[b+1].sala;
					int salab = filmes[b].sala;
					int mesmaSala = salab == salabb; // troca o filme  por outro de fora da sala.
					int trocafora = salab > salabb; // troca o filme por outro dentro da sala.
					int trocaporhorario = mesmaSala && horarioparaminuto(filmes[b].horario) > horarioparaminuto(filmes[b+1].horario);
					if(trocafora || trocaporhorario){/* aqui comeca o bublle sort dessa funcao */
						Ingresso tmp = filmes[b];
						filmes[b] = filmes[b+1];
						filmes[b+1] = tmp;
					}
				}
			}
}

void gerarIngressos(Ingresso filmes[], int totalFilmes, int totalClientes, PilhaEst *pilha){
	int indice[MAX_QTD_FILMES];
	int totalHoje =0;
	for(int i =0; i<totalFilmes; i++){
		if(filmes[i].amanha ==0){
			indice[totalHoje] = i;
			totalHoje ++;
		}
	}
	if(totalHoje == 0){
		printf("\nNao a filmes para o dia de hoje\n");
		return ;
	}
	for(int c=0; c<totalClientes; c++){
		int sorteio = rand() % totalHoje;
		int indiceFilme = indice[sorteio];
		push(pilha, indiceFilme);
	}
}
