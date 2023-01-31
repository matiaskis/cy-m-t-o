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

void treatA(DataA1 e,FILE* out);
void infixPathA(PAVLAA a, FILE* out);
void infixPathRA(PAVLAA a, FILE* out);
PAVLAA createTreeA(DataA1 e);
PAVLAA LeftRotationA(PAVLAA a);
PAVLAA RightRotationA(PAVLAA a);
PAVLAA doubleLeftRotationA(PAVLAA a);
PAVLAA doubleRightRotationA(PAVLAA a);
PAVLAA balanceAVLAA(PAVLAA a);
PAVLAA insertionAVLAAAverage(PAVLAA a,DataA1 e, int* h);
void calculateAverageA(PAVLAA a);
#endif
