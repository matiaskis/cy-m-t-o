#ifndef AVL1_H
#define AVL1_H
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct data1{
    int station;
    float associated_Data1;
    int average_increment;
}Data1;

typedef struct avl1{
    Data1 elmt;
    struct avl1 * fg;
    struct avl1 * fd;
    int equilibre;
}AVL1;

typedef AVL1* PAVL1;
void traiter(Data1 e,FILE* out);
void parcoursInfixe(PAVL1 a, FILE* out);
void parcoursInfixeR(PAVL1 a, FILE* out);
int max(int a, int b);
int min(int a, int b);
PAVL1 creerArbre(Data1 e);

PAVL1 rotationGauche(PAVL1 a);
PAVL1 rotationDroite(PAVL1 a);
PAVL1 doublerotationGauche(PAVL1 a);
PAVL1 doublerotationDroite(PAVL1 a);
PAVL1 equilibrerAVL1(PAVL1 a);
PAVL1 insertionAVL1Max(PAVL1 a,Data1 e, int* h);
PAVL1 insertionAVL1Min(PAVL1 a,Data1 e, int* h);
PAVL1 insertionAVL1Average(PAVL1 a,Data1 e, int* h);
void calculateAverage(PAVL1 a);
#endif
