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
    printf("Função Não Implementada\n");
}

void adicionarArestaMatriz(int inicio, int fim, float peso){
    printf("Função Não Implementada\n");
}

void mostrarGrafoMatriz(){
    printf("Função Não Implementada\n");
}

void descobrirCaminhoMatriz(int, int){
    printf("Função Não Implementada\n");
}

int existeVerticeMatriz(int id){
    printf("Função Não Implementada\n");
    return 0;
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