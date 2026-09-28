#ifndef RANDOM_H
#define RANDOM_H

#include "arquivo.h"
#include "pilha.h"

void inicializarSorteio();
void distribuirFilmes(Ingresso filmes[], int totalFilmes);
void preencherFilaClientes(FilaCirc *filaEntrada, Cliente clientes[], int totalClientes);
void preencherPilhasIngressos(PilhaEst pilhas[], Ingresso filmes[], int totalFilmes);

#endif
