#ifndef AVLM_H
#define AVLM_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct data_m{
    int station;
    int moisture;
    int doublon[61];
    int counter;
}Data_m;

typedef struct avl_m{
    Data_m elmt;
    struct avl_m * fg;
    struct avl_m * fd;
    int equilibre;
}AVL_m;

typedef AVL_m* PAVL_m;

void traiter_m(int count,Data_m e,FILE* out);
void traiter_m2(Data_m e,FILE* out);
void parcoursInfixe_m(PAVL_m a, FILE* out);
void parcoursInfixeR_m(PAVL_m a, FILE* out);
void parcoursInfixe_m2(PAVL_m a, FILE* out);
void parcoursInfixeR_m2(PAVL_m a, FILE* out);

PAVL_m creerArbre_m(Data_m e);

PAVL_m rotationGauche_m(PAVL_m a);
PAVL_m rotationDroite_m(PAVL_m a);
PAVL_m doublerotationGauche_m(PAVL_m a);
PAVL_m doublerotationDroite_m(PAVL_m a);
PAVL_m equilibrerAVL_m(PAVL_m a);

PAVL_m insertionAVLM(PAVL_m a,Data_m e, int* h);
PAVL_m insertionAVLMMax(PAVL_m a,Data_m e, int* h);

#endif
