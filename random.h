#ifndef RANDOM_H
#define RANDOM_H

#include "arquivo.h"
#include "pilha.h"

void inicializarSorteio();
void distribuirFilmes(Ingresso filmes[], int totalFilmes);
void gerarIngressos(Ingresso filmes[], int totalFilmes, int totalClientes, PilhaEst *pilha);

#endif
