#ifndef ABR2_H
#define ABR2_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct data_abr2{
    int station;
    float associated_data;
    int average_increment;
}Data_abr2;

typedef struct abr2{
    Data elmt;
    struct abr2 * fg;
    struct abr2 * fd;
    int equilibre;
}ABR2;

typedef ABR2* PABR2;

void traiter_abr2(Data_abr2 e,FILE* out) ;
void parcoursInfixe_abr2(PABR2 a, FILE* out);
void parcoursInfixeR_abr2(PABR2 a, FILE* out);
PABR2 creerArbre_abr2(Data_abr2 e);
PABR2 insertionAverage_abr2(PABR2 a, Data_abr2 e);
void calculateAverage_abr2(PABR2 a);
#endif
