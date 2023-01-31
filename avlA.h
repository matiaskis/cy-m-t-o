#ifndef AVLA_H
#define AVLA_H
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct dataa1{
    int station;
    float associated_DataA1;
    float associated_DataA2;
    int average_increment;
}DataA1;

typedef struct AVLAA{
    DataA1 elmt;
    struct AVLAA * fg;
    struct AVLAA * fd;
    int equilibre;
}AVLAA;

typedef AVLAA* PAVLAA;
void traiterA(DataA1 e,FILE* out);
void parcoursInfixeA(PAVLAA a, FILE* out);
void parcoursInfixeRA(PAVLAA a, FILE* out);
PAVLAA creerArbreA(DataA1 e);
PAVLAA rotationGaucheA(PAVLAA a);
PAVLAA rotationDroiteA(PAVLAA a);
PAVLAA doublerotationGaucheA(PAVLAA a);
PAVLAA doublerotationDroiteA(PAVLAA a);
PAVLAA equilibrerAVLAA(PAVLAA a);
PAVLAA insertionAVLAAAverage(PAVLAA a,DataA1 e, int* h);
void calculateAverageA(PAVLAA a);
#endif
