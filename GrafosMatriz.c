#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "GrafosMatriz.h"

static int EH_PONDERADO;
static int EH_DIRIGIDO;
static int QUANTIDADE_VERTICES;
static GrafoM* raiz[100];
static float matrizAdj[100][100];

void inicializarGrafoMatriz(int eh_ponderado, int eh_dirigido){
    // Inicia a matriz de adjacência
    for(int i = 0; i < 100; i++){
        for(int j = 0; j < 100; j++){
            matrizAdj[i][j] = 0.0;
        }
        raiz[i] = NULL;  // Inicia o array de vértices
    }

    EH_PONDERADO = eh_ponderado;
    EH_DIRIGIDO = eh_dirigido;
    QUANTIDADE_VERTICES = 0;
}

void adicionarVerticeMatriz(int id, char* texto){
    if(id < 0 || id >= 100){
        printf("ID fora do intervalo permitido (0-99)\n");
        return;
    }

    if(raiz[id] != NULL){
        printf("O vértice com ID %d já existe\n", id);
        return;
    }

    raiz[id] = malloc(sizeof(GrafoM));
    if(raiz[id] == NULL){
        printf("Erro na alocação de memória para novo vértice\n");
        return;
    }

    raiz[id]->id = id;
    raiz[id]->peso = 0.0;
    strncpy(raiz[id]->nome, texto, 99);
    raiz[id]->nome[99] = '\0';

    QUANTIDADE_VERTICES++;
    printf("Novo vértice (%d) adicionado ao grafo de representação por matriz.\n", id);
}

void adicionarArestaMatriz(int inicio, int fim, float peso){
    // Verifica se os vértices escolhidos existem
    if(!existeVerticeMatriz(inicio)){
        printf("Não é possível adicionar aresta, pois não existe o vértice inicial (%d)\n", inicio);
        return;
    }

    if(!existeVerticeMatriz(fim)){
        printf("Não é possível adicionar aresta, pois não existe o vértice final (%d)\n", fim);
        return;
    }

    // Define peso como 1 se o grafo for não ponderado
    if(!EH_PONDERADO){
        peso = 1.0;
    }

    // Adiciona a aresta para ambos os sentidos, se necessário
    matrizAdj[inicio][fim] = peso;

    if(!EH_DIRIGIDO){
        matrizAdj[fim][inicio] = peso;
    }

    if(EH_PONDERADO){
        printf("A aresta (%d, %d, %.2f) foi adicionada com sucesso.\n", inicio, fim, peso);
    }
    else{
        printf("A aresta (%d, %d) foi adicionaa com sucesso.\n", inicio, fim);
    }
}

void mostrarGrafoMatriz(){
    printf("\n=== GRAFO EM MATRIZ DE ADJACÊNCIA ===\n");
    printf("\nVértices:\n");

    for(int i = 0; i < 100; i++){
        if(raiz[i] != NULL){
            printf("/t[%d] $s\n", raiz[i]->id, raiz[i]->nome);
        }
    }

    printf("\nMatriz:\n");

    // Primeiro, será printado os IDs dos vértices
    printf("\t");
    for(int i = 0; i < 100; i++){
        if(raiz[i] != NULL){
            printf("%3d", raiz[i]->id);
        }
    }
    printf("\n");

    // Depois as linhas da matriz
    for(int i = 0; i < 100; i++){
        if(raiz[i] != NULL){
            printf("%3d:", raiz[i]->id);
            for(int j = 0; j < 100; j++){
                if(raiz[i] != NULL){
                    if(EH_PONDERADO){
                        printf("%.2f", matrizAdj[i][j]);
                    }

                    else{
                        printf("%.0f", matrizAdj[i][j]);
                    }
                }
            }

            printf("\n");
        }
    }

    printf("\n");
}

void descobrirCaminhoMatriz(int, int){
    printf("Função Não Implementada\n");
}

int existeVerticeMatriz(int id){
    if(id < 0 || id >= 100) return 0;
    
    return raiz[id] != NULL; // Retorna 0 se o vertice for NULL e 1 se não for
}

void removerArestaMatriz(int inicio, int fim){
    printf("Função Não Implementada\n");
}

void removerVerticeMatriz(int){
    printf("Função Não Implementada\n");
}

int obterListaIDDosVerticesMatriz(int*){
    printf("Função Não Implementada\n");
    return -1;
}