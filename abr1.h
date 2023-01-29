#ifndef ABR1_H
#define ABR1_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct data1ABR{
    int station;
    float associated_data;
    int average_increment;
}Data1ABR;

typedef struct abr1{
    Data elmt;
    struct abr1 * fg;
    struct abr1 * fd;
    int equilibre;
}ABR1;

typedef ABR1* PABR1;

void traiter_abr1(Data1ABR e,FILE* out) ;
void parcoursInfixe_abr1(PABR1 a, FILE* out);
void parcoursInfixeR_abr1(PABR1 a, FILE* out);
PABR1 creerArbre_abr1(Data1ABR e);
PABR1 insertionMax_abr1(PABR1 a,Data1ABR e);
PABR1 insertionMin_abr1(PABR1 a,Data1ABR e);
PABR1 insertionAverage_abr1(PABR1 a, Data1ABR e);
void calculateAverage_abr1(PABR1 a);
#endif
