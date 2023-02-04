#ifndef TABM_H
#define TABM_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct data_tabm{
    int station;
    int moisture;
    float duplicates[61];
    float duplicatela[61];
    float duplicatelo[61];
    int counter;
    float latitude;
    float longitude;
}Data_tabm;

typedef struct linkedListm{
    Data_tabm elmt;
    struct linkedListm * next;
}LinkedListm;
LinkedListm * createLinkedListm(Data_tabm e);
LinkedListm * insertionStartm(LinkedListm* pList, Data_tabm e);
LinkedListm * insertionTabm(LinkedListm *pList, Data_tabm e);
LinkedListm * insertionTabMAXm(LinkedListm *pList, Data_tabm e);
void treat_tabm2(LinkedListm* pList,FILE* out);
void treat_tabm(LinkedListm* pList,FILE* out);

#endif
