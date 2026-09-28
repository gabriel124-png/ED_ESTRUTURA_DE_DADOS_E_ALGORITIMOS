#include <stdio.h>
#include "fila.h"

void inicializaFila(FilaCirc *fila) {
    fila->inicio = 0;
    fila->fim = 0;
    fila->total = 0;
}

int vaziaFila(FilaCirc *fila) {
    return (fila->total == 0);
}

int cheiaFila(FilaCirc *fila) {
    return (fila->total == MAX_FILA);
}

void enfileirar(FilaCirc *fila, Cliente c) {
    if (cheiaFila(fila)) {
        printf("Erro: Fila cheia!\n");
        return;
    }
    fila->itens[fila->fim] = c;
    fila->fim = (fila->fim + 1) % MAX_FILA; // LÃ³gica circular
    fila->total++;
}

Cliente desenfileirar(FilaCirc *fila) {
    Cliente cVazio;
    cVazio.nome[0] = '\0';
    
    if (vaziaFila(fila)) {
        printf("Erro: Fila vazia!\n");
        return cVazio;
    }
    
    Cliente item = fila->itens[fila->inicio];
    fila->inicio = (fila->inicio + 1) % MAX_FILA; // LÃ³gica circular
    fila->total--;
    return item;
}

void imprimirFila(FilaCirc *fila) {
    if (vaziaFila(fila)) {
        printf("Fila vazia.\n");
        return;
    }
    int pos = fila->inicio;
    for (int i = 0; i < fila->total; i++) {
        printf(" - %s (Idade: %d)\n", fila->itens[pos].nome, fila->itens[pos].idade);
        pos = (pos + 1) % MAX_FILA;
    }
}
