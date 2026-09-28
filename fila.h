#ifndef FILA_H  
#define FILA_H  
    
#include "arquivo.h"

#define MAX_FILA 100

typedef struct {
    Cliente itens[MAX_FILA];
    int inicio;
    int fim;
    int total;
} FilaCirc;

void inicializaFila(FilaCirc *fila);
int vaziaFila(FilaCirc *fila);
int cheiaFila(FilaCirc *fila);
void enfileirar(FilaCirc *fila, Cliente c);
Cliente desenfileirar(FilaCirc *fila);
void imprimirFila(FilaCirc *fila);

#endif
