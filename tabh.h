#ifndef TABH_H
#define TABH_H
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct data_tabh{
    int station;
    int height;
    float latitude;
    float longitude;
    float duplicate[3];
    float duplicate2[3];

}Data_tabh;

typedef struct linkedListh {
	Data_tabh elmt;
	struct linkedListh* next;
}LinkedListh;

LinkedListh * createLinkedListh(Data_tabh e);
LinkedListh * insertionStarth(LinkedListh* pList, Data_tabh e);
LinkedListh * insertionTabh(LinkedListh *pList, Data_tabh e);
void treatListh(LinkedListh *pList,FILE* out);
#endif
