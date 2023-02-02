#include "tab1.h"

LinkedList * createLinkedList(Data_tab1 e){
	LinkedList * c =  malloc(sizeof(LinkedList));
	if(c==NULL){
		exit(1);
	}
	c->elmt=e;
	c->next=NULL;
	return c;
}

LinkedList * insertionStart(LinkedList* pList, Data_tab1 e){
	LinkedList* new=createLinkedList(a);
	new -> next = pList;
	return new;
}

LinkedList *insertionTab1(LinkedList *pList, Data_tab1 e) {
	LinkedList *new=createLinkedList(e);
	LinkedList *p1 = pList;
	if(pList==NULL){
		pList=new;
	}
	else if (pList->elmt.station > e.station) {
		pList=insertionStart(pList,e);
	}
	else{
		
		while(p1->next!= NULL && p1->next->elmt.station < e.station){ 
			p1=p1->next;
		}
		if(p1->next==NULL){
			p1->next=new;
		}
		else{
			new->next=p1->next;
			p1->next = new;
		}
	}
	return pList;           
}

void displayList(LinkedList *pList){
	if (pList == NULL)
		puts("Liste vide\n");
	else {
		while (pList->next != NULL) {
			fprintf();
			pList = pList->next;
		}
		fprintf();
	}
}
