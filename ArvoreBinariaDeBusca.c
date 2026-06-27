#include <stdio.h>
#include <stdlib.h>
#include "ArvoreBinariaDeBusca.h"
#include "IACODES.h"

static NodeABB *raiz;

// Inicia a árvore sem criar nenhum nó
void iniciaABB(){
    raiz = NULL;
}

// Pré-Ordem = raiz - esquerda - direita
void preOrderABB(NodeABB *raiz){
    if(raiz == NULL){
        return;
    }

    printf("%d  ", raiz->valor);
    preOrderABB(raiz->esq);
    preOrderABB(raiz->dir);
}

// Em-Ordem = esquerda - raiz - direita
void inOrderABB(NodeABB *raiz){
    if(raiz == NULL){
        return;
    }

    inOrderABB(raiz->esq);
    printf("%d  ", raiz->valor);
    inOrderABB(raiz->dir);
}

// Pós-Ordem = esquerda - direita - raiz
void postOrderABB(NodeABB *raiz){
    if(raiz == NULL){
        return;
    }

    postOrderABB(raiz->esq);
    postOrderABB(raiz->dir);
    printf("%d  ", raiz->valor);
}

void inserirNodeABB(int valor){
    NodeABB *novo = malloc(sizeof(NodeABB));

    if(novo == NULL){
        printf("Erro de alocação\n");
        return;
    }

    // Define valor e filhos como NULL (é folha)
    novo->valor = valor;
    novo->pai = NULL;
    novo->esq = NULL;
    novo->dir = NULL;

    // Se a árvore estiver vazia, ela se tornará o novo nó
    if(raiz == NULL){
        raiz = novo;
        printf("Nó criado com sucesso!\n");
        return;
    }

    // Cria dois ponteiros para navegar na árvore
    NodeABB *atual = raiz;
    NodeABB *anterior = NULL;

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

    printf("Nó criado com sucesso!\n");
}

NodeABB *removerRecABB(NodeABB *raiz, int valor){
    // Se raiz for NULL ou a árvore está vazia ou a função percorreu toda a árvore
    if(raiz == NULL){
        return NULL;
    }

    // Navega para a esquerda/direita até chegar ao final da árvore ou parar no valor
    if(valor < raiz->valor){
        raiz->esq = removerRecABB(raiz->esq, valor);

        if(raiz->esq != NULL){
            raiz->esq->pai = raiz;
        }
    }

    else if(valor > raiz->valor){
        raiz->dir = removerRecABB(raiz->dir, valor);

        if(raiz->dir != NULL){
            raiz->dir->pai = raiz;
        }
    }

    // Indica que um nó com o valor indicado foi encontrado e começa a avaliar qual é o caso da remoção
    else{
        // CASO 1: Será removido um nó folha
        if(raiz->esq == NULL && raiz->dir == NULL){
            free(raiz);

            return NULL;
        }

        // CASO 2: Será removido um nó com um filho direito
        else if(raiz->esq == NULL){
            NodeABB* temp = raiz->dir;
            temp->pai = raiz->pai;
            
            free(raiz);

            return temp;
        }

        // CASO 3: Será removido um nó com um filho esquerdo
        else if(raiz->dir == NULL){
            NodeABB* temp = raiz->esq;
            temp->pai = raiz->pai;

            free(raiz);

            return temp;
        }

        // CASO 4: Será removido um nó que possui ambos os filhos
        else{
            // Sucessor é o filho mais da esquerda do filho direito do nó a ser removido
            NodeABB* sucessor = raiz->dir;
            while(sucessor->esq != NULL){
                sucessor = sucessor->esq;
            }

            // Substitui valores entre nó a ser removido e sucessor e remove sucessor original
            raiz->valor = sucessor->valor;
            raiz->dir = removerRecABB(raiz->dir, sucessor->valor);

            if(raiz->dir != NULL){
                raiz->dir->pai = raiz;
            }
        }
    }

    return raiz;
}

// Função "pública" para ser chamada na main
void removerNodeABB(int valor){
    // Se valor existe na árvore, será removido
    if(buscaABB(valor)){
        raiz = removerRecABB(raiz, valor);

        // Coloca o pai da possível nova raiz como NULL
        if(raiz != NULL){
            raiz->pai = NULL;
        }
        
        printf("Nó com valor escolhido foi removido com sucesso!\n");
    }
    else{
        printf("Um nó com o valor escolhido não existe na árvore!\n");
    }
    
}

// Oferece ao usuário a opção de escolher como a árvore vai ser mostrada
void mostrarArvoreABB(){
    if(raiz == NULL){
        printf("A árvore está atualmente vazia\n");
        return;
    }

    int escolha = -1;

    while(escolha < 0 || escolha > 4){
        printf("\nPor favor, escolha como a árvore será mostrada:\n");
        printf("[1] Toda a árvore\n");
        printf("[2] Pré-Ordem\n");
        printf("[3] Em-Ordem\n");
        printf("[4] Pós-Ordem\n");
        printf("[0] Cancelar\n");

        escolha = IA_lerInteiro("\nOpte apenas por [1], [2], [3] ou [4]: ");
    }

    switch(escolha){
        case 0:
            printf("Cancelando...\n");
            return;
            break;
        
        case 1:
            printf("\n=== ÁRVORE INTEIRA (vista lateralmente) ===\n");
            mostrarArvoreBBAux(raiz, 0);
            printf("\n");
            break;

        case 2:
            printf("\n=== PRÉ-ORDEM ===\n");
            preOrderABB(raiz);
            printf("\n");
            break;

        case 3:
            printf("\n=== EM-ORDEM ===\n");
            inOrderABB(raiz);
            printf("\n");
            break;

        case 4:
            printf("\n=== PÓS-ORDEM ===\n");
            postOrderABB(raiz);
            printf("\n");
            break;

    }
    
}

// Busca se existe algum nó com o valor indicado na árvore
int buscaABB(int valor){
    // Cria um ponteiro auxiliar que percorre a árvore
    NodeABB *aux = raiz;
    
    while(aux != NULL){
        if(valor > aux->valor){
            aux = aux->dir;
        }
        else if(valor < aux->valor){
            aux = aux->esq;
        }
        else{
            return 1;
        }
    }

    // Se a execução não acabar no loop, o valor não existe na árvore
    return 0;
}