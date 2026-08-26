#ifndef PILHA_H
#define PILHA_H

#include <stdio.h>
#define MAX_PILHA 100

typedef struct{
  int itens[MAX_PILHA];
  int topo;
}PilhaEst;

void inicializaPilha(PilhaEst *pilha){
  pilha->topo=-1;
}

int vaziaPilha(PilhaEst *pilha){
  return(pilha->topo ==-1);
}

int topo(PilhaEst *pilha){
  if(vaziaPilha(pilha)){
	printf("Erro: Pilha vazia\n");
	return -10; // Retorna erro.
   }
   return pilha->itens[pilha->topo];
}

int cheiaPilha(PilhaEst *pilha){
  return(pilha->topo == MAX_PILHA -1);
}

int pop(PilhaEst *pilha){
  if(vaziaPilha(pilha)){
	printf("Erro: Pilha vazia\n");
	return -12; // Retorna erro.
  }
  int item = pilha->itens[pilha->topo];
  pilha->topo--;
  return item;
}

void push(PilhaEst *pilha, int item){
  if(cheiaPilha(pilha)){
	printf("Erro: Pilha cheia\n");
	return;
  }
  pilha->topo++;
  pilha->itens[pilha->topo]=item;
}

#endif
