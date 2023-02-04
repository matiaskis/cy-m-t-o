#ifndef TAB1_H
#define TAB1_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct data_tab1{
    int station;
    float temp_ave;
    float temp_max;
    float temp_min;
    int ave_counter;
}Data_tab1;

typedef struct linkedList {
	Data_tab1 elmt;
	struct linkedList* next;
}LinkedList;

LinkedList * createLinkedList(Data_tab1 e);
LinkedList * insertionStart(LinkedList* pList, Data_tab1 e);
LinkedList * insertionTab1(LinkedList *pList, Data_tab1 e);
void calculateAverageTab1(LinkedList * pList);
void treatList(LinkedList *pList,FILE* out);
#endif
