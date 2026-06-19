#ifndef ARVOREBINARIADEBUSCA_H
#define ARVOREBINARIADEBUSCA_H

typedef struct Node{
    int valor;
    Node *pai;
    Node *esq;
    Node *dir;
} Node;

// Operações
void inserirNode(Node *raiz, int valor);
void removerNode(Node *raiz, int valor);
void mostrarArvore(Node *raiz);
void busca(Node *raiz, int valor);

// Métodos para percorrer a árvore
void preOrder(Node *raiz);
void inOrder(Node *raiz);
void postOrder(Node *raiz);

// Auxiliares
Node *esquerda(Node *raiz);
Node *direita(Node *raiz);
Node *irmao(Node *raiz);
Node *inicia(Node *raiz, int valor);

#endif