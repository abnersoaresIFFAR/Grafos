#include <stdio.h>
#include <stdlib.h>
#include "ArvoreBinariaDeBusca.h"
#include "IACODES.h"

static NodeABB *raiz;

NodeABB *esquerdaABB(NodeABB *node){
    if(node == NULL)
        return NULL;

    return node->esq;
}

NodeABB *direitaABB(NodeABB *node){
    if(node == NULL)
        return NULL;

    return node->dir;
}

NodeABB *irmaoABB(NodeABB *node){
    if(node == NULL || node->pai == NULL)
        return NULL;

    if(node == node->pai->esq)
        return node->pai->dir;

    return node->pai->esq;
}

NodeABB *paiABB(NodeABB *node){
    if(node == NULL)
        return NULL;

    return node->pai;
}

void iniciaABB(){
    raiz = NULL;
}

void preOrder(){
    printf("Função Não Implementada\n");
}

void inOrder(){
    printf("Função Não Implementada\n");
}

void postOrder(){
    printf("Função Não Implementada\n");
}

void inserirNodeABB(int valor){
    NodeABB *novo = malloc(sizeof(NodeABB));

    if(novo == NULL){
        printf("Erro de alocação\n");
        return;
    }

    novo->valor = valor;
    novo->esq = NULL;
    novo->dir = NULL;
    novo->pai = NULL;

    if(raiz == NULL){
        raiz = novo;
        return;
    }

    NodeABB *atual = raiz;
    NodeABB *pai = NULL;

    while(atual != NULL){
        pai = atual;

        if(valor < atual->valor)
            atual = atual->esq;
        else if(valor > atual->valor)
            atual = atual->dir;
        else{
            free(novo);
            return;
        }
    }

    novo->pai = pai;

    if(valor < pai->valor)
        pai->esq = novo;
    else
        pai->dir = novo;
}

void removerNodeABB(int valor){
    printf("Função Não Implementada\n");
}


void mostrarArvoreABB(){
    if(raiz == NULL){
        printf("A árvore está atualmente vazia\n");
        return;
    }

    printf("\n=== ÁRVORE (vista lateralmente) ===\n");
    mostrarArvoreAux(raiz, 0);
}

void buscaABB(int valor){
    printf("Função Não Implementada\n");
}