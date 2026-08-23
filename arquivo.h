#ifndef ARQUIVO_H
#define ARQUIVO_H

#define MAX_FILMES 100      /* tamanho maximo do texto do nome do filme */
#define MAX_NOMES 100       /* tamanho maximo do texto do nome do cliente */

#define MAX_QTD_FILMES 50   /* quantidade maxima de filmes no array */
#define MAX_QTD_CLIENTES 100 /* quantidade maxima de clientes no array */

#define MAX_SALAS 6 /* quantidade maxima de salas do cinema */
#define MAX_LUGARES 20 /* quantidade maxima acentos por sala */

typedef struct Ingresso{
    char filme[MAX_FILMES];
    int sala;
    int amanha;
    char horario[10];
    float preco;
}Ingresso;

typedef struct Cliente{
    char nome[MAX_NOMES];
    int idade;
    char genero;
    Ingresso ingresso;
}Cliente;

void lerFilmes();
void lerClientes();

/* carregam os dados do arquivo para dentro de um array; devolvem quantos itens foram lidos */
int carregarFilmes(Ingresso filmes[], int max);
int carregarClientes(Cliente clientes[], int max);

#endif
