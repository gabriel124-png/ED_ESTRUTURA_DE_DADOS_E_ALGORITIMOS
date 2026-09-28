#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "arquivo.h"

void lerFilmes(){
    FILE *leitor;
    char linha[200];
    char *token;

    leitor = fopen("filmes.txt", "r");
    if(leitor == NULL){
        printf("Erro ao abrir o arquivo de filmes.\n");
        return;
    }

    printf("\n--- FILMES EM CARTAZ ---\n");
    while(fgets(linha, sizeof(linha), leitor) != NULL){
        Ingresso passcinema;

        /* remove o '\n' (e '\r', caso o arquivo venha do Windows) do final da linha */
        linha[strcspn(linha, "\r\n")] = '\0';

        token = strtok(linha, ";");
        if(token != NULL) strcpy(passcinema.filme, token);

        token = strtok(NULL, ";");
        if(token != NULL) strcpy(passcinema.horario, token);

        token = strtok(NULL, ";");
        if(token != NULL) passcinema.preco = atof(token);

        printf("Filme: %-40s  Horario: %s  Preco: R$ %.2f\n",
               passcinema.filme, passcinema.horario, passcinema.preco);
    }

    fclose(leitor);
}

int carregarFilmes(Ingresso filmes[], int max){
    FILE *leitor;
    char linha[200];
    char *token;
    int contador = 0;

    leitor = fopen("filmes.txt", "r");
    if(leitor == NULL){
        printf("Erro ao abrir o arquivo de filmes.\n");
        return 0;
    }

    while(fgets(linha, sizeof(linha), leitor) != NULL && contador < max){
        linha[strcspn(linha, "\r\n")] = '\0';

	filmes[contador].sala =0;  /* iniciando no while o .sala */
	filmes[contador].amanha =0;/* iniciando no while o .amanha */

        token = strtok(linha, ";"); // Pega o nome do filme do arquivo.
        if(token != NULL) strcpy(filmes[contador].filme, token);

        token = strtok(NULL, ";");  // Pega o horario da sala do arquivo.
        if(token != NULL) strcpy(filmes[contador].horario, token);

        token = strtok(NULL, ";"); // Pega o preco do ingresso do arquivo.
        if(token != NULL) filmes[contador].preco = atof(token);

	token = strtok(NULL, ";"); // Pega a duracao do filme do arquivo.
	if(token != NULL) filmes[contador].duracao = atoi(token);

        contador++;
    }

    fclose(leitor);
    return contador;
}

int carregarClientes(Cliente clientes[], int max){
    FILE *leitor;
    char linha[MAX_NOMES];
    char *token;
    int contador = 0;

    leitor = fopen("clientes.txt", "r");
    if(leitor == NULL){
        printf("Erro ao abrir o arquivo de clientes.\n");
        return 0;
    }

	    while(fgets(linha, sizeof(linha), leitor) != NULL && contador < max){
	    linha[strcspn(linha, "\r\n")] = '\0';
	    if(strlen(linha) == 0) continue;
	    token = strtok(linha, ";"); // pega o nome do cliente do arquivo.
	    if(token != NULL) strcpy(clientes[contador].nome, token);
	    token = strtok(NULL, ";"); // pega a idade do arquivo.
	    if(token != NULL) clientes[contador].idade = atoi(token);
	    token = strtok(NULL, ";"); // Pega o genero do arquivo.
	    if(token != NULL) clientes[contador].genero = token[0];

	    contador++;
	}

    fclose(leitor);
    return contador;
}

void lerClientes(){
    FILE *leitor;
    char linha[MAX_NOMES];

    leitor = fopen("clientes.txt", "r");
    if(leitor == NULL){
        printf("Erro ao abrir o arquivo de clientes.\n");
        return;
    }

    printf("\n--- CLIENTES CADASTRADOS ---\n");
    while(fgets(linha, sizeof(linha), leitor) != NULL){
        linha[strcspn(linha, "\r\n")] = '\0';
        if(strlen(linha) > 0){
            printf("Cliente: %s\n", linha);
        }
    }

    fclose(leitor);
}
