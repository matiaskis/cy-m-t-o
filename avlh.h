#ifndef AVLH_H
#define AVLH_H
#include <stdio.h>
#include <stdlib.h>
#include <string.h>


typedef struct data_h{
    int station;
    int height;
    //float latitude;
    //float longitude;
    int doublon;
    int doublon2;
}Data_h;

typedef struct avl_h{
    Data_h elmt;
    struct avl_h * fg;
    struct avl_h * fd;
    int equilibre;
}AVL_H;

typedef AVL_H* PAVL_H;

void traiter_h(Data_h e,FILE* out);
void parcoursInfixe_h(PAVL_H a, FILE* out);
void parcoursInfixeR_h(PAVL_H a, FILE* out);

PAVL_H creerArbre_h(Data_h e);

PAVL_H rotationGauche_h(PAVL_H a);
PAVL_H rotationDroite_h(PAVL_H a);
PAVL_H doublerotationGauche_h(PAVL_H a);
PAVL_H doublerotationDroite_h(PAVL_H a);
PAVL_H equilibrerAVL_h(PAVL_H a);
PAVL_H insertionAVLHHeight(PAVL_H a,Data_h e, int* h);
#endif
