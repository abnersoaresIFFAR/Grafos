#include <stdio.h>
#include <stdlib.h>
#include "ArvoreRubroNegra.h"
#include "IACODES.h"

static NodeARN *raiz;

// Inicia a árvore sem criar nenhum nó
void iniciaARN(){
    raiz = NULL;
}

// Pré-Ordem = raiz - esquerda - direita
void preOrderARN(NodeARN *raiz){
    if(raiz == NULL){
        return;
    }

    printf("%d", raiz->valor);
    raiz->cor ? printf("(V)  ") : printf("(P)  ");

    preOrderARN(raiz->esq);
    preOrderARN(raiz->dir);
}

// Em-Ordem = esquerda - raiz - direita
void inOrderARN(NodeARN *raiz){
    if(raiz == NULL){
        return;
    }

    inOrderARN(raiz->esq);
    printf("%d", raiz->valor);
    raiz->cor ? printf("(V)  ") : printf("(P)  ");
    
    inOrderARN(raiz->dir);
}

// Pós-Ordem = esquerda - direita - raiz
void postOrderARN(NodeARN *raiz){
    if(raiz == NULL){
        return;
    }

    postOrderARN(raiz->esq);
    postOrderARN(raiz->dir);
    printf("%d", raiz->valor);
    raiz->cor ? printf("(V)  ") : printf("(P)  ");
}

void mostrarArvoreARN(){
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
            mostrarArvoreRNAux(raiz, 0);
            printf("\n");
            break;

        case 2:
            printf("\n=== PRÉ-ORDEM ===\n");
            preOrderARN(raiz);
            printf("\n");
            break;

        case 3:
            printf("\n=== EM-ORDEM ===\n");
            inOrderARN(raiz);
            printf("\n");
            break;

        case 4:
            printf("\n=== PÓS-ORDEM ===\n");
            postOrderARN(raiz);
            printf("\n");
            break;

    }
    
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

NodeARN *buscaARN(int valor){
    // Cria um ponteiro auxiliar que percorre a árvore
    NodeARN *aux = raiz;
    
    while(aux != NULL){
        if(valor > aux->valor){
            aux = aux->dir;
        }
        else if(valor < aux->valor){
            aux = aux->esq;
        }
        else{
            return aux;
        }
    }

    // Se a execução não acabar no loop, o valor não existe na árvore
    return NULL;
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

NodeARN *sucessor(NodeARN *node){
    while(node->esq != NULL){
        node = node->esq;
    }

    return node;
}

void transplante(NodeARN *u, NodeARN *v){
    if(u->pai == NULL){
        raiz = v;
    }

    else if(u == u->pai->esq){
        u->pai->esq = v;
    }

    else{
        u->pai->dir = v;
    }

    if(v != NULL){
        v->pai = u->pai;
    }
}

void removerNodeARN(int valor){

    NodeARN *z = buscaARN(valor);

    if(z == NULL){
        printf("Valor não encontrado.\n");
        return;
    }

    NodeARN *y = z;
    NodeARN *x;
    NodeARN *xPai = NULL;

    bool corOriginal = y->cor;

    // CASO 1: z não possui filho esquerdo
    if(z->esq == NULL){

        x = z->dir;
        xPai = z->pai;
        transplante(z, z->dir);
    }

    // CASO 2: z não possui filho direito
    else if(z->dir == NULL){

        x = z->esq;
        xPai = z->pai;
        transplante(z, z->esq);
    }

    // CASO 3: z possui os dois filhos
    else{

        y = sucessor(z->dir);

        corOriginal = y->cor;

        x = y->dir;

        if(y->pai == z){

            xPai = y;
            if(x != NULL)
                x->pai = y;
        }
        else{

            xPai = y->pai;
            transplante(y, y->dir);

            y->dir = z->dir;
            y->dir->pai = y;
        }

        transplante(z, y);

        y->esq = z->esq;
        y->esq->pai = y;

        y->cor = z->cor;
    }

    free(z);

    if(corOriginal == false){
        corrigirRemocao(x, xPai);
    }

    if(raiz != NULL)
        raiz->cor = false;

    printf("Nó removido com sucesso!\n");
}

void corrigirRemocao(NodeARN *node, NodeARN *pai){
    // Nó atual a partir do qual irá rebalancear a árvore
    NodeARN *no = node;
    // Pai do nó removido ou nó em que ocorreu a deficiência de cor
    NodeARN *paiNo = pai;

    // Enquanto o nó for preto e estiver em estado de 'duplo preto'
    while((no == NULL || no->cor == false) && no != raiz){
        if(paiNo == NULL)
            break;

        // Identifica o irmão do nó atual
        NodeARN *irmao = (no == paiNo->esq) ? paiNo->dir : paiNo->esq;

        // Caso 1: o irmão é vermelho
        if(irmao != NULL && irmao->cor == true){
            irmao->cor = false;
            paiNo->cor = true;
            if(no == paiNo->esq)
                rotacaoEsq(paiNo);
            else
                rotacaoDir(paiNo);
            // Atualiza o irmão após a rotação
            irmao = (no == paiNo->esq) ? paiNo->dir : paiNo->esq;
        }

        // Caso 2: irmão preto com filhos pretos
        if(irmao == NULL ||
           ((irmao->esq == NULL || irmao->esq->cor == false) &&
            (irmao->dir == NULL || irmao->dir->cor == false))){
            if(irmao != NULL)
                irmao->cor = true;
            // Move o problema para cima na árvore
            no = paiNo;
            paiNo = paiNo->pai;
        }
        else{
            if(no == paiNo->esq){
                // Caso 3: irmão preto com filho direito preto e filho esquerdo vermelho
                if(irmao->dir == NULL || irmao->dir->cor == false){
                    if(irmao->esq != NULL)
                        irmao->esq->cor = false;
                    irmao->cor = true;
                    rotacaoDir(irmao);
                    irmao = paiNo->dir;
                }

                // Caso 4: irmão preto com filho direito vermelho
                if(irmao != NULL){
                    irmao->cor = paiNo->cor;
                    if(irmao->dir != NULL)
                        irmao->dir->cor = false;
                }
                paiNo->cor = false;
                rotacaoEsq(paiNo);
                no = raiz;
                paiNo = NULL;
            }
            else{
                // Caso 3 simétrico para o nó sendo filho direito
                if(irmao->esq == NULL || irmao->esq->cor == false){
                    if(irmao->dir != NULL)
                        irmao->dir->cor = false;
                    irmao->cor = true;
                    rotacaoEsq(irmao);
                    irmao = paiNo->esq;
                }

                // Caso 4 simétrico
                if(irmao != NULL){
                    irmao->cor = paiNo->cor;
                    if(irmao->esq != NULL)
                        irmao->esq->cor = false;
                }
                paiNo->cor = false;
                rotacaoDir(paiNo);
                no = raiz;
                paiNo = NULL;
            }
        }
    }

    // Finalmente, garante que o nó atual é preto
    if(no != NULL)
        no->cor = false;
}