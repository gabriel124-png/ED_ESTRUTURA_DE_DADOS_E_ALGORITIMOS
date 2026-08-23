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

void distribuirFilmes(Ingresso filmes[], int totalFilmes){
	embaralharFilmes(filmes, totalFilmes);
	int porSala = totalFilmes / MAX_SALAS;
	int quantSala [MAX_SALAS] = {0};
	char horarioSala[MAX_SALAS][MAX_QTD_FILMES][10];
	for(int i=0; i<totalFilmes; i++){
	   int colocado =0;
		for(int s=0; s< MAX_SALAS && !colocado; s++){
			if(quantSala[s] >= porSala) continue; /* verificar conflitos de horario na sala */
			int conflito =0;
			for(int h=0; h  < quantSala[s]; h++){
				if(strcmp(horarioSala[s][h], filmes[i].horario)==0){
					conflito =1; // variavel de controle dentro da condição.
					break;
				}
			}
			if(conflito) continue; // já tem filme nesse horario

			filmes[i].sala = s + 1;
			filmes[i].amanha = 0;
			strcpy(horarioSala[s][quantSala[s]], filmes[i].horario); // guarda o horario do filme.
			quantSala[s]++;
			colocado = 1;
		}
		if(!colocado){
			filmes[i].sala =0;
			filmes[i].amanha =1;
		}
	}
}
