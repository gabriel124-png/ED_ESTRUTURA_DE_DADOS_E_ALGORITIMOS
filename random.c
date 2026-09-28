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
		int j = rand() % (i + 1);
		Ingresso tmp  = filmes[i];
		filmes[i] = filmes[j];
		filmes[j] = tmp;
	}
}

static int horarioparaminuto(char horario[]){
	int hora, minuto;
	sscanf(horario, "%d:%d", &hora, &minuto);
	return hora * 60 + minuto;
}

static int conflitodehorario(int inicio1, int inicio2, int fim1, int fim2){
	return (inicio1 < fim2) && (inicio2 < fim1);
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
			if(quantSala[s] >= porSala) continue;
			int conflito =0;
			for(int h=0; h  < quantSala[s]; h++){
				if(conflitodehorario(inicioNovo, inicioSala[s][h], fimNovo, fimSala[s][h])){
					conflito =1;
					break;
				}
			}
			if(conflito) continue;

			filmes[i].sala = s + 1;
			filmes[i].amanha = 0;
			inicioSala[s][quantSala[s]] = inicioNovo;
			fimSala[s][quantSala[s]] = fimNovo;
			quantSala[s]++;
			colocado = 1;
		}
		if(!colocado){
			filmes[i].sala =0;
			filmes[i].amanha =1;
		}
	}
	for(int a =0; a<totalFilmes-1; a++){
		for(int b =0; b<totalFilmes-1-a; b++){
			int salabb = filmes[b+1].sala;
			int salab = filmes[b].sala;
			int mesmaSala = salab == salabb;
			int trocafora = salab > salabb;
			int trocaporhorario = mesmaSala && horarioparaminuto(filmes[b].horario) > horarioparaminuto(filmes[b+1].horario);
			if(trocafora || trocaporhorario){
				Ingresso tmp = filmes[b];
				filmes[b] = filmes[b+1];
				filmes[b+1] = tmp;
			}
		}
	}
}

// Coloca os clientes lidos do arquivo para dentro da Fila de Entrada do Cinema
void preencherFilaClientes(FilaCirc *filaEntrada, Cliente clientes[], int totalClientes){
    for(int i = 0; i < totalClientes; i++){
        enfileirar(filaEntrada, clientes[i]);
    }
}

// Para cada filme que passa hoje, preenche uma Pilha de Ingressos (10 ingressos por pilha)
void preencherPilhasIngressos(PilhaEst pilhas[], Ingresso filmes[], int totalFilmes){
    for(int i = 0; i < totalFilmes; i++){
        inicializaPilha(&pilhas[i]);
        if(filmes[i].amanha == 0){ // SÃ³ gera ingressos para filmes de hoje
            for(int k = 0; k < 10; k++){
                push(&pilhas[i], i); // Guarda o indice do filme na pilha
            }
        }
    }
}
