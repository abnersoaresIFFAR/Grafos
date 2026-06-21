/*
Autoria: Professor Alex Borges
Ano 2026
Código desenvolvido para ensino da disciplina de Estrutura de Dados 2
Bacharelado em Ciência da Computação
Instituto Federal Farroupilha
*/

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "GrafosGrafica.h"
#include "GrafosLista.h"
#include "GrafosMatriz.h"
#include "IACODES.h"
#include "ArvoreBinariaDeBusca.h"

// VARIAVEIS GLOBAIS
typedef enum {INVALIDO, GRAFICA, LISTA, MATRIZ} GRAFOMETODO; // armazena o método de se trabalhar com grafos
typedef enum {EH_DIRIGIDO, NAO_EH_DIRIGIDO} DIRECAO; // informa se o grafo é ou não é direcionado
typedef enum {EH_PONDERADO, NAO_EH_PONDERADO} PONDERACAO; // informa se o grafo é ou não é ponderado
typedef enum {GRAFOS, ARVORES} ESTRUTURA; // informa se será trabalhado com grafos ou árvores
typedef enum {INVALIDO, ABB, ARN} ARVOREMETODO; // armazena o método a se trabalhar com árvores

// VALORES INICIAIS DO PROGRAMA
int UNICID = 0;
GRAFOMETODO GRAFMET = INVALIDO;
DIRECAO QUALDIRECAO = NAO_EH_DIRIGIDO;
PONDERACAO QUALPONDERACAO = NAO_EH_PONDERADO;
ESTRUTURA QUALESTRUTURA = GRAFOS;
ARVOREMETODO ARVMET = INVALIDO;

// SÉRIE DE FUNÇÕES PRÁTICAS
int 
MENU(){ /* MOSTRA O MENU PARA O USUÁRIO */
    int opcao;
    while(1){ // repita pra sempre
        if(GRAFMET == INVALIDO && ARVMET == INVALIDO){
            printf("Por favor, escolha um método de se trabalhar com\n");
            printf("\n    === GRAFOS ===\n");
            printf("[1] Grafos com representação gráfica\n");
            printf("[2] Grafo com lista de adjacência\n");
            printf("[3] Grafo com matriz de adjacência\n");
            printf("\n    === ÁRVORES ===\n");
            printf("[4] Árvore Binária de Busca\n");
            printf("Opte apenas por [1], [2], [3] ou [4]: ");
            scanf("%d", &opcao);
            if(opcao < 1 || opcao > 4){
                printf("Valor inválido digitado\n");
                continue;
            }
        }
        else if(GRAFMET != INVALIDO){ // se for diferente de inválido, foi escolhido algo entre os grafos
            printf("Por favor, escolha uma opção:\n");
            
            printf("[1] Adicionar Vértice\n");
            printf("[2] Adicionar Aresta\n");
            printf("[3] Remover Aresta\n");
            printf("[4] Remover Vértice\n");
            printf("[5] Ver Grafo\n");
            printf("[6] Descobrir Caminho\n");
            printf("[0] SAIR\n");
            printf("Opte apenas por [1], [2], [3], [4], [5], [6] ou [0]: ");
            scanf("%d", &opcao);
            if(opcao < 0 || opcao > 6){
                printf("Valor inválido digitado\n");
                continue;
            }
        }

        else if(ARVMET != INVALIDO){ // se for diferente de inválido, foi escolhido algo entre as árvores
            QUALESTRUTURA = ARVORES;
            printf("Por favor, escolha uma opção:\n");

            printf("[1] Inserir Nó\n");
            printf("[2] Remover Nó\n");
            printf("[3] Ver Árvore\n");
            printf("[4] Buscar Valor na Árvore\n");
            printf("[0] SAIR\n");
            printf("Opte apenas por [1], [2], [3], [4] ou [0]: ");
            scanf("%d", &opcao);
            if(opcao < 0 || opcao > 4){
                printf("Valor inválido digitado\n");
                continue;
            }
        }
        //se nenhum continue foi executado, pode sair do laço
        break;
    }

    return opcao;
}

void pausa() {
    int c;

    printf("Aperte ENTER para continuar...");

    // limpa caracteres pendentes
    while ((c = getchar()) != '\n' && c != EOF);

    // espera um novo ENTER
    getchar();

    system("clear");
}

int lerIDVertices(){
    //função que mostra os IDs dos vértices e retorna o ID digitado, ou não há vertices e retorna -1
    int lista_ids[100];
    int qntd_id = 0;
    if(GRAFMET == GRAFICA){
        qntd_id = obterListaIDDosVerticesGrafica(lista_ids);
    }
    else if(GRAFMET == LISTA){
        qntd_id = obterListaIDDosVerticesLista(lista_ids);
    }
    else if(GRAFMET == MATRIZ){
        qntd_id = obterListaIDDosVerticesMatriz(lista_ids);
    }

    if(qntd_id == 0){
        printf("Não há vértices no grafo para serem removidos.\n");
        return -1;
    }
    else{
        int id_vertice;
        int digitou_certo = 0;
        while(digitou_certo == 0){
            printf("Há os seguintes vértices no grafo: ");
            for(int i = 0; i < qntd_id; i++){
                printf("[%d], ", lista_ids[i]);
            }
            id_vertice = IA_lerInteiro("agora, escolha um vértice: ");
            for(int i = 0; i < qntd_id; i++){
                if(lista_ids[i] == id_vertice){
                    digitou_certo = 1;
                }
            }

            if(digitou_certo == 0){
                printf("O id digitado não existe na lista apresentada.\n");
            }
        }
        return id_vertice;
    }
}

int existeVertice(int id){
    int existe = 0;
    if(GRAFMET == GRAFICA){
        existe = existeVerticeGrafica(id);
    }
    else if(GRAFMET == LISTA){
        existe = existeVerticeLista(id);
    }
    else if(GRAFMET == MATRIZ){
        existe = existeVerticeMatriz(id);
    }
    return existe;
}

void inicializarGrafo(){
    int pond = QUALPONDERACAO == NAO_EH_PONDERADO ? 0 : 1;
    int dire = QUALDIRECAO == NAO_EH_DIRIGIDO ? 0 : 1;
    if(GRAFMET == GRAFICA){
        inicializarGrafoGrafica(pond, dire);
    }
    else if(GRAFMET == LISTA){
        inicializarGrafoLista(pond, dire);
    }
    else if(GRAFMET == MATRIZ){
        inicializarGrafoMatriz(pond, dire);
    }
}

void adicionarVertice(){
    char texto[255];
    IA_lerTexto(texto, 255, "Diga a informação que deseja armazenar no vértice: ");
    int id = UNICID++;

    if(GRAFMET == GRAFICA){
        adicionarVerticeGrafica(id, texto);
    }
    else if(GRAFMET == LISTA){
        adicionarVerticeLista(id, texto);
    }
    else if(GRAFMET == MATRIZ){
        adicionarVerticeMatriz(id, texto);
    }
}

void adicionarAresta(){
    printf("Vamos adicionar uma aresta:\n");
    int inicio = lerIDVertices();
    int fim = lerIDVertices();

    if(inicio == -1 || fim == -1){
        printf("Não há vértices disponíveis a serem adicionados arestas.\n");
    }

    if(inicio == fim){
        printf("Não é permitido adicionar uma aresta laço.\n");
        return;
    }

    float peso = 0.0;

    if(QUALPONDERACAO == EH_PONDERADO){
        peso = IA_lerDecimal("Diga qual o peso a ser adicionado na aresta:");
    }

    if(GRAFMET == GRAFICA){
        adicionarArestaGrafica(inicio, fim, peso);
    }
    else if(GRAFMET == LISTA){
        adicionarArestaLista(inicio, fim, peso);
    }
    else if(GRAFMET == MATRIZ){
        adicionarArestaMatriz(inicio, fim, peso);
    }
}

void removerAresta(){
    printf("Vamos remover uma aresta:\n");
    int inicio = lerIDVertices();
    int fim = lerIDVertices();

    if(inicio == -1 || fim == -1){
        printf("Não há vértices disponíveis a serem removidas arestas.\n");
    }

    if(inicio == fim){
        printf("Não existe aresta laço.\n");
        return;
    }
    
    if(GRAFMET == GRAFICA){
        removerArestaGrafica(inicio, fim);
    }
    else if(GRAFMET == LISTA){
        removerArestaLista(inicio, fim);
    }
    else if(GRAFMET == MATRIZ){
        removerArestaMatriz(inicio, fim);
    }
}

void removerVertice(){
    printf("Vamos remover um vértice:\n");
    int id = lerIDVertices();

    if(id == -1){
        printf("Não há vértices disponíveis a serem removidas.\n");
    }
    
    if(GRAFMET == GRAFICA){
        removerVerticeGrafica(id);
    }
    else if(GRAFMET == LISTA){
        removerVerticeLista(id);
    }
    else if(GRAFMET == MATRIZ){
        removerVerticeMatriz(id);
    }
}

void mostrarGrafo(){
    if(GRAFMET == GRAFICA){
        mostrarGrafoGrafica();
    }
    else if(GRAFMET == LISTA){
        mostrarGrafoLista();
    }
    else if(GRAFMET == MATRIZ){
        mostrarGrafoMatriz();
    }
}

void descobrirCaminho(){
    printf("Vamos descobrir o caminho:");
    int inicio = lerIDVertices();
    int fim = lerIDVertices();

    if(inicio == -1 || fim == -1){
        printf("Não há vértices disponíveis para traçar um caminho.\n");
    }
    
    if(GRAFMET == GRAFICA){
        descobrirCaminhoGrafica(inicio, fim);
    }
    else if(GRAFMET == LISTA){
        descobrirCaminhoLista(inicio, fim);
    }
    else if(GRAFMET == MATRIZ){
        descobrirCaminhoMatriz(inicio, fim);
    }
}

void inserirNode(){
    int val;
    val = IA_lerInteiro("Diga o valor que deseja armazenar no nó adicionado: ");

    if(ARVMET == ABB){
        inserirNodeABB(val);
    }
}
void removerNode(){
    int val;
    val = IA_lerInteiro("Diga o valor do nó que deseja remover: ");

    if(ARVMET == ABB){
        removerNodeABB(val);
    }
}
void mostrarArvore(){
    if(ARVMET == ABB){
        mostrarArvoreABB();
    }
}
void busca(){
    int val;
    val = IA_lerInteiro("Diga o valor do nó que deseja procurar: ");

    if(ARVMET == ABB){
        buscaABB(val);
    }
}

int main(){
    //variáveis que auxiliam o fluxo de interação
    int opcaomenu;

    //Código Principal
    printf("Olá aluno de ED2, seja bem vindo ao programa.\n");
    do{ //repete pra sempre
        opcaomenu = MENU();

        // primeira execução será sempre essa daqui, definindo tipo de grafo
        if(GRAFMET == INVALIDO && ARVMET == INVALIDO){
            
            if(opcaomenu == 1){
                GRAFMET = GRAFICA;
                printf("Aplicando sistema de grafos com representação gráfica...\n");
            }
            else if(opcaomenu == 2){
                GRAFMET = LISTA;
                printf("Aplicando sistema de grafos com lista de adjacência...\n");
            }
            else if(opcaomenu == 3){
                GRAFMET = MATRIZ;
                printf("Aplicando sistema de grafos com matriz de adjacência...\n");
            }
            else if(opcaomenu == 4){
                QUALESTRUTURA = ARVORES;
                ARVMET = ABB;
                printf("Aplicando sistema de árvore binaria de busca...\n");
            }
        }
        else{
            if(QUALESTRUTURA == GRAFOS){
                if     (opcaomenu == 1) adicionarVertice();
                else if(opcaomenu == 2) adicionarAresta();
                else if(opcaomenu == 3) removerAresta();
                else if(opcaomenu == 4) removerVertice();
                else if(opcaomenu == 5) mostrarGrafo();
                else if(opcaomenu == 6) descobrirCaminho();
            }
            else if(QUALESTRUTURA == ARVORES){
                if     (opcaomenu == 1) inserirNode();
                else if(opcaomenu == 2) removerNode();
                else if(opcaomenu == 3) mostrarArvore();
                else if(opcaomenu == 4) busca();
            }
        }

        if(opcaomenu != 0) pausa();
    }while(opcaomenu != 0);
    //fim código principal
    printf("Agradecemos a preferência\n");

    return 0;
}