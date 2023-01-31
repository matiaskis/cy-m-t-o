#ifndef ABR3_H
#define ABR3_H
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct data_abr3{
    int station;
    float associated_Data;
    long date;
}Data_abr3;

typedef struct abr3{
    Data_abr3 elmt;
    struct abr3 * secondTree;
    struct abr3 * fg;
    struct abr3 * fd;
}ABR3;

typedef ABR3* PABR3;


void treat_abr3(Data_abr3 e,FILE* out);
void secondInfixPath(PABR3 a,FILE * out);
void infixPath_abr3(PABR3 a, FILE* out) ;
void secondinfixPathR_abr3(PABR3 a,FILE * out);
void infixPathR_abr3(PABR3 a, FILE* out) ;
PABR3 createTree_abr3(Data_abr3 e);
PABR3 createTree_oabr3(Data_abr3 e);
PABR3 insertionABR3SecondTree(PABR3 a,Data3 e);
PABR3 insertionABR_oabr3(PABR3 a,Data3 e);
#endif
