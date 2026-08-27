#ifndef PILHA_H
#define PILHA_H

#define MAX_PILHA 100

typedef struct{
  int itens[MAX_PILHA];
  int topo;
}PilhaEst;

void inicializaPilha(PilhaEst *pilha);
int vaziaPilha(PilhaEst *pilha);
int topo(PilhaEst *pilha);
int cheiaPilha(PilhaEst *pilha);
int pop(PilhaEst *pilha);
void push(PilhaEst *pilha, int item);
void imprimirPilha(PilhaEst *pilha);

#endif
