#ifndef TABW_H
#define TABW_H
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct data_tabw{
    int station;
    float wind1_ave;
    float wind2_ave;
    float latitude;
    float longitude;
    int ave_counter;
}Data_tabw;

typedef struct linkedListw {
	Data_tabw elmt;
	struct linkedListw* next;
}LinkedListw;

LinkedListw * createLinkedListw(Data_tabw e);
LinkedListw * insertionStartw(LinkedListw* pList, Data_tabw e);
LinkedListw * insertionTabw(LinkedListw *pList, Data_tabw e);
void calculateAverageTabw(LinkedListw * pList);
void treatListw(LinkedListw *pList,FILE* out);
#endif
