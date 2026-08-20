#include <stdlib.h>
#include <time.h>
#include "random.h"

void inicializarSorteio(){
    srand(time(NULL));
}

Ingresso sortearFilme(Ingresso filmes[], int total){
    int indice = rand() % total;
    return filmes[indice];
}

Cliente sortearCliente(Cliente clientes[], int total){
    int indice = rand() % total;
    return clientes[indice];
}
