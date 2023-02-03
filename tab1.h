#ifndef AVLM_H
#define AVLM_H

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
	linkList* next;
}LinkedList;

typedef struct LinkedList* PLinkedList;
