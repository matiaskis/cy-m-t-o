#ifndef AVL_H
#define AVL_H

typedef struct data{
    int station;
    float associated_data;
    int average_increment;

}Data;

typedef struct avl{
    Data elmt;
    struct avl * fg;
    struct avl * fd;
    int equilibre;
}AVL;


typedef AVL* PAVL;

void traiter(Data e,FILE* out);
void parcoursInfixe(PAVL a, FILE* out);
void parcoursInfixeR(PAVL a, FILE* out);
int max(int a, int b);
int min(int a, int b);
PAVL creerArbre(Data e);

PAVL rotationGauche(PAVL a);
PAVL rotationDroite(PAVL a);
PAVL doublerotationGauche(PAVL a);
PAVL doublerotationDroite(PAVL a);
PAVL equilibrerAVL(PAVL a);
PAVL insertionAVLMax(PAVL a,Data e, int* h);
PAVL insertionAVLMin(PAVL a,Data e, int* h);
PAVL insertionAVLAverage(PAVL a,Data e, int* h);
void calculateAverage(PAVL a);
#endif
