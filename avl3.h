#ifndef AVL3_H
#define AVL3_H
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct data3{
    int station;
    float associated_Data3;
    long date3;
}Data3;

typedef struct avl3{
    Data3 elmt;
    struct avl3 * secondTree;
    struct avl3 * fg;
    struct avl3 * fd;
    int equilibre;
}AVL3;


typedef AVL3* PAVL3;
void traiter3(Data3 e,FILE* out);
void sousParcoursInfixe3(PAVL3 a,FILE * out);
void parcoursInfixe3(PAVL3 a, FILE* out);
void sousParcoursInfixeR3(PAVL3 a,FILE * out);
void parcoursInfixeR3(PAVL3 a, FILE* out);

PAVL3 creerArbre3(Data3 e);
PAVL3 creerArbreAVL3(Data3 e);

PAVL3 rotationGauche3(PAVL3 a);
PAVL3 rotationDroite3(PAVL3 a);
PAVL3 doublerotationGauche3(PAVL3 a);
PAVL3 doublerotationDroite3(PAVL3 a);
PAVL3 equilibrerAVL3(PAVL3 a);
PAVL3 insertionAVL3SecondTree(PAVL3 a,Data3 e, int* h);
PAVL3 insertionAVL3date(PAVL3 a,Data3 e, int* h,int * g);
#endif
