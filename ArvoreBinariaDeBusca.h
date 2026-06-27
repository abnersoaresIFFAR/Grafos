#ifndef ARVOREBINARIADEBUSCA_H
#define ARVOREBINARIADEBUSCA_H

typedef struct NodeABB{
    int valor;
    struct NodeABB *pai;
    struct NodeABB *esq;
    struct NodeABB *dir;
} NodeABB;

// Operações
void inserirNodeABB(int valor);
void removerNodeABB(int valor);
void mostrarArvoreABB();
int buscaABB(int valor);

// Métodos para percorrer a árvore
void preOrderABB(NodeABB *raiz);
void inOrderABB(NodeABB *raiz);
void postOrderABB(NodeABB *raiz);

// Auxiliares
void iniciaABB();

#endif