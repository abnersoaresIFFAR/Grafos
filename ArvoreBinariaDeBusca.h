#ifndef ARVOREBINARIADEBUSCA_H
#define ARVOREBINARIADEBUSCA_H

typedef struct NodeABB{
    int valor;
    NodeABB *pai;
    NodeABB *esq;
    NodeABB *dir;
} NodeABB;

// Operações
void inserirNodeABB(int valor);
void removerNodeABB(int valor);
void mostrarArvoreABB();
void buscaABB(int valor);

// Métodos para percorrer a árvore
void preOrder();
void inOrder();
void postOrder();

// Auxiliares
NodeABB *esquerdaABB();
NodeABB *direitaABB();
NodeABB *irmaoABB();
NodeABB *iniciaABB(int valor);

#endif