#ifndef IACODES_H
#define IACODES_H

#include "GrafosGrafica.h"
#include "ArvoreBinariaDeBusca.h"
#include "ArvoreRubroNegra.h"

int IA_lerInteiro(const char *);
float IA_lerDecimal(const char *);
void IA_lerTexto(char*, int, const char *);

void IA_mostrarGrafoGrafica(); // função que gera o grafo em versão visual

// funções que vão mostrar a árvore inteira deitada
void mostrarArvoreBBAux(NodeABB *node, int nivel);
void mostrarArvoreRNAux(NodeARN *node, int nivel);
#endif //IACODES_H