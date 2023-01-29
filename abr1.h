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

void traiter(Data1ABR e,FILE* out) ;
void parcoursInfixe(PABR1 a, FILE* out);
void parcoursInfixeR(PABR1 a, FILE* out);
PABR1 creerArbre(Data1ABR e);
PABR1 insertionABRMax(PABR1 a,Data1ABR e);
PABR1 insertionABRMin(PABR1 a,Data1ABR e);
PABR1 insertionABRAverage(PABR1 a, Data1ABR e);
void calculateAverage(PABR1 a);
