#ifndef ABRM_H
#define ABRM_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct data_abrm{
    int station;
    int moisture;
    int duplicate[61];
    int counter;
}Data_abrm;

typedef struct abr_m{
    Data_abrm elmt;
    struct abr_m * fg;
    struct abr_m * fd;
}ABR_m;

typedef ABR_m* PABR_m;

void treat_m(int count,Data_abrm e,FILE* out);
void treat_m2(Data_abrm e,FILE* out);
void infixPath_m(PABR_m a, FILE* out);
void infixPathR_m(PABR_m a, FILE* out);
void infixPath_m2(PABR_m a, FILE* out);
void infixPathR_m2(PABR_m a, FILE* out);

PABR_m creerArbre_m(Data_abrm e);

PABR_m insertionABRM(PABR_m a,Data_abrm e);
PABR_m insertionABRMMax(PABR_m a,Data_abrm e);

#endif
