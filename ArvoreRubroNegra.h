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
NodeARN *buscaARN(int valor);

// Métodos para percorrer a árvore
void preOrderARN(NodeARN *raiz);
void inOrderARN(NodeARN *raiz);
void postOrderARN(NodeARN *raiz);

// Rotações
void rotacaoEsq(NodeARN *node);
void rotacaoDir(NodeARN *node);

// Correções
void corrigirInsercao(NodeARN *node);
void corrigirRemocao(NodeARN *node, NodeARN *pai);

// Auxiliares
void iniciaARN();
NodeARN *sucessor(NodeARN *node);
void transplante(NodeARN *u, NodeARN *v);

#endif