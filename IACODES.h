#ifndef IACODES_H
#define IACODES_H

#include "GrafosGrafica.h"
#include "ArvoreBinariaDeBusca.h"

int IA_lerInteiro(const char *);
float IA_lerDecimal(const char *);
void IA_lerTexto(char*, int, const char *);

void IA_mostrarGrafoGrafica(); // função que gera o grafo em versão visual

void mostrarArvoreAux(NodeABB *node, int nivel);

#endif //IACODES_H