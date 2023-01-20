#ifndef AVL2_H
#define AVL2_H
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct data2{
    long date2;
    float associated_Data2;
    int average_increment;
}Data2;

typedef struct avl2{
    Data2 elmt;
    struct avl2 * fg;
    struct avl2 * fd;
    int equilibre;
}AVL2;

typedef AVL2* PAVL2;

void traiter2(Data2 e,FILE* out);
void parcoursInfixe2(PAVL2 a, FILE* out);
void parcoursInfixeR2(PAVL2 a, FILE* out);

PAVL2 creerArbre2(Data2 e);

PAVL2 rotationGauche2(PAVL2 a);
PAVL2 rotationDroite2(PAVL2 a);
PAVL2 doublerotationGauche2(PAVL2 a);
PAVL2 doublerotationDroite2(PAVL2 a);
PAVL2 equilibrerAVL2(PAVL2 a);
PAVL2 insertionAVLAverage2(PAVL2 a,Data2 e, int* h);
void calculateAverage2(PAVL2 a);
#endif
