#include <stdio.h>
#include <stdlib.h>
#include "ArvoreBinariaDeBusca.h"
#include "IACODES.h"

static NodeABB *raiz;

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

    if(raiz == NULL){
        raiz = novo;
        printf("Nó criado com sucesso!\n");
        return;
    }

    NodeABB *atual = raiz;
    NodeABB *anterior = NULL;

    while(atual != NULL){
        anterior = atual;

        if(valor < atual->valor)
            atual = atual->esq;
        else if(valor > atual->valor)
            atual = atual->dir;
        else{
            free(novo);

            printf("Um nó com esse valor já existe na árvore!\n");
            return;
        }
    }

    if(valor < anterior->valor)
        anterior->esq = novo;
    else
        anterior->dir = novo;

    printf("Nó criado com sucesso!\n");
}

NodeABB *removerRecABB(NodeABB *raiz, int valor){
    if(raiz == NULL){
        printf("Um nó com o valor não foi encontrado\n");
        return NULL;
    }

    if(valor < raiz->valor){
        raiz->esq = removerRecABB(raiz->esq, valor);
    }

    else if(valor > raiz->valor){
        raiz->dir = removerRecABB(raiz->dir, valor);
    }

    else{
        if(raiz->esq == NULL && raiz->dir == NULL){
            free(raiz);

            printf("O nó com o valor inserido foi removido com sucesso!\n");
            return NULL;
        }

        else if(raiz->esq == NULL){
            NodeABB* temp = raiz->dir;
            free(raiz);

            printf("O nó com o valor inserido foi removido com sucesso!\n");
            return temp;
        }

        else if(raiz->dir == NULL){
            NodeABB* temp = raiz->esq;
            free(raiz);

            printf("O nó com o valor inserido foi removido com sucesso!\n");
            return temp;
        }

        else{
            NodeABB* sucessor = raiz->dir;
            while(sucessor->esq != NULL){
                sucessor = sucessor->esq;
            }

            raiz->valor = sucessor->valor;
            raiz->dir = removerRecABB(raiz->dir, sucessor->valor);
        }
    }

    return raiz;
}

void removerNodeABB(int valor){
    raiz = removerRecABB(raiz, valor);
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
    NodeABB *aux = raiz;
    
    while(aux != NULL){
        if(valor > aux->valor){
            aux = aux->dir;
        }
        else if(valor < aux->valor){
            aux = aux->esq;
        }
        else if(valor == aux->valor){
            printf("Um nó com este valor existe na árvore!\n");
            return;
        }
    }

    printf("Não existe um nó com este valor na árvore!\n");
}