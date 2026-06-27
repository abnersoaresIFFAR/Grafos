#include <stdio.h>
#include <stdlib.h>
#include "ArvoreRubroNegra.h"

static NodeARN *raiz;

// Inicia a árvore sem criar nenhum nó
void iniciaARN(){
    raiz = NULL;
}

// Pré-Ordem = raiz - esquerda - direita
void preOrder(NodeARN *raiz){
    if(raiz == NULL){
        return;
    }

    printf("%d", raiz->valor);
    raiz->cor ? printf("(V)  ") : printf("(P)  ");

    preOrder(raiz->esq);
    preOrder(raiz->dir);
}

// Em-Ordem = esquerda - raiz - direita
void inOrder(NodeARN *raiz){
    if(raiz == NULL){
        return;
    }

    inOrder(raiz->esq);
    printf("%d", raiz->valor);
    raiz->cor ? printf("(V)  ") : printf("(P)  ");
    
    inOrder(raiz->dir);
}

// Pós-Ordem = esquerda - direita - raiz
void postOrder(NodeARN *raiz){
    if(raiz == NULL){
        return;
    }

    postOrder(raiz->esq);
    postOrder(raiz->dir);
    printf("%d", raiz->valor);
    raiz->cor ? printf("(V)  ") : printf("(P)  ");
}

// Realiza uma rotação simples à esquerda
void rotacaoEsq(NodeARN *node){
    NodeARN *aux = node->dir;

    // O filho esquerdo do antigo filho direito passa a ser o novo filho direito
    node->dir = aux->esq;

    if(aux->esq != NULL){
        aux->esq->pai = node;
    }

    // Liga o novo nó ao antigo pai
    aux->pai = node->pai;

    if(node->pai == NULL){
        raiz = aux;
    }

    else if(node == node->pai->esq){
        node->pai->esq = aux;
    }

    else{
        node->pai->dir = aux;
    }

    // Finaliza a rotação
    aux->esq = node;
    node->pai = aux;
}

// Realiza uma rotação simples à direita
void rotacaoDir(NodeARN *node){
    NodeARN *aux = node->esq;

    // O filho direito do antigo filho esquerdo passa a ser o novo filho esquerdo
    node->esq = aux->dir;

    if(aux->dir != NULL){
        aux->dir->pai = node;
    }

    // Liga o novo nó ao antigo pai
    aux->pai = node->pai;

    if(node->pai == NULL){
        raiz = aux;
    }

    else if(node == node->pai->dir){
        node->pai->dir = aux;
    }

    else{
        node->pai->esq = aux;
    }

    // Finaliza a rotação
    aux->dir = node;
    node->pai = aux;
}

void inserirNodeARN(int valor){
    NodeARN *novo = malloc(sizeof(NodeARN));

    if(novo == NULL){
        printf("Erro de alocação\n");
        return;
    }

    // Define valor e filhos como NULL (é folha)
    novo->valor = valor;
    novo->pai = NULL;
    novo->esq = NULL;
    novo->dir = NULL;
    novo->cor = true;

    // Se a árvore estiver vazia, ela se tornará o novo nó
    if(raiz == NULL){
        raiz = novo;
        corrigirInsercao(raiz);

        printf("Nó criado com sucesso!\n");
        return;
    }

    // Cria dois ponteiros para navegar na árvore
    NodeARN *atual = raiz;
    NodeARN *anterior = NULL;

    while(atual != NULL){
        anterior = atual;

        // Se o valor a ser inserido for menor que o nó atual, navega-se para filho esquerdo
        if(valor < atual->valor)
            atual = atual->esq;

        // Se o valor a ser inserido for maior que o nó atual, navega-se para filho direito
        else if(valor > atual->valor)
            atual = atual->dir;

        // Se não for nenhum dos casos, o valor a ser inserido é igual ao nó atual
        else{
            free(novo);

            printf("Um nó com esse valor já existe na árvore!\n");
            return;
        }
    }

    // Define o pai do novo nó como o nó anterior a ele
    novo->pai = anterior;

    // Determinaa se o nó a ser inseridp vai ficar na esquerda ou na direita do último nó válido encontrado 
    if(valor < anterior->valor)
        anterior->esq = novo;
    else
        anterior->dir = novo;

    corrigirInsercao(novo);

    printf("Nó criado com sucesso!\n");
}

// Corrige possíveis violações das propriedaes da árvore rubro negra
void corrigirInsercao(NodeARN *node){

    while(node != raiz && node->pai->cor == true){

        NodeARN *pai = node->pai;
        NodeARN *avo = pai->pai;

        // Caso o pai seja filho esquerdo do avô
        if(pai == avo->esq){

            NodeARN *tio = avo->dir;

            // CASO 1: Tio vermelho
            if(tio != NULL && tio->cor == true){

                pai->cor = false;
                tio->cor = false;
                avo->cor = true;

                node = avo;
            }

            else{

                // CASO 2
                if(node == pai->dir){
                    node = pai;
                    rotacaoEsq(node);

                    pai = node->pai;
                    avo = pai->pai;
                }

                // Caso 3
                pai->cor = false;
                avo->cor = true;

                rotacaoDir(avo);
            }
        }

        // Caso o pai seja filho direito do avô
        else{

            NodeARN *tio = avo->esq;

            // CASO 1: Tio vermelho
            if(tio != NULL && tio->cor == true){

                pai->cor = false;
                tio->cor = false;
                avo->cor = true;

                node = avo;
            }

            else{

                // CASO 2
                if(node == pai->esq){
                    node = pai;
                    rotacaoDir(node);

                    pai = node->pai;
                    avo = pai->pai;
                }

                // CASO 3
                pai->cor = false;
                avo->cor = true;

                rotacaoEsq(avo);
            }
        }
    }

    // A raiz deve ser sempre preta
    raiz->cor = false;
}