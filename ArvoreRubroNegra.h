#ifndef ARVORERUBRONEGRA_H
#define ARVORERUBRONEGRA_H

#include <stdbool.h>

typedef struct NodeARN{
    int valor;
    struct NodeARN *esq;
    struct NodeARN *dir;
    struct NodeARN *pai;
    bool cor;
} NodeARN;

// Operações
void inserirNodeARN(int valor);
void removerNodeARN(int valor);
void mostrarArvoreARN();
int buscaARN(int valor);

// Métodos para percorrer a árvore
void preOrder(NodeARN *raiz);
void inOrder(NodeARN *raiz);
void postOrder(NodeARN *raiz);

// Correções
void corrigirInsercao();
void corrigirRemocao();

// Auxiliares
void iniciaARN();

#endif