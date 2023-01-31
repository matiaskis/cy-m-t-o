#ifndef ABRH_H
#define ABRH_H
#include <stdio.h>
#include <stdlib.h>
#include <string.h>


typedef struct data_abrh{
    int station;
    int height;
    //float latitude;
    //float longitude;
    int duplicate;
    int duplicate2;
}Data_abrh;

typedef struct abr_h{
    Data_abrh elmt;
    struct abr_h * fg;
    struct abr_h * fd;
}ABR_H;

typedef ABR_H* PABR_H;

void treat_abrh(Data_abrh e,FILE* out);
void infixPath_h(PABR_H a, FILE* out);
void infixPathR_h(PABR_H a, FILE* out);
PABR_H createTree_abrh(Data_abrh e);
PABR_H insertionABRHeight(PABR_H a,Data_abrh e);
#endif
