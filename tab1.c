#include"tab1.h"


LinkedList * createLinkedList(Data_tab1 e){
	LinkedList * c =  malloc(sizeof(LinkedList));
	if(c==NULL){
		exit(1);
	}
	c->elmt.station=e.station;
    c->elmt.temp_ave=e.temp_ave;
    c->elmt.temp_max=e.temp_max;
    c->elmt.temp_min=e.temp_min;
    c->elmt.ave_counter=1;
	c->next=NULL;
	return c;
}

LinkedList * insertionStart(LinkedList* pList, Data_tab1 e){
	LinkedList* new=createLinkedList(e);
	new -> next = pList;
	return new;
}

LinkedList * insertionTab1(LinkedList *pList, Data_tab1 e) {
	
	LinkedList *p1 = pList;
	if(pList==NULL){
		return createLinkedList(e);
	}
	else if (pList->elmt.station > e.station) {
		pList=insertionStart(pList,e);
	}
	else{
		
		while(p1->next != NULL && p1->next->elmt.station <= e.station){ 
			p1=p1->next;
		}
        if(p1->elmt.station == e.station){
            
            p1->elmt.temp_ave=p1->elmt.temp_ave+e.temp_ave;
            p1->elmt.ave_counter=p1->elmt.ave_counter+1;
            if(e.temp_max > p1->elmt.temp_max){
                p1->elmt.temp_max=e.temp_max;
            }
            if(e.temp_min < p1->elmt.temp_min){
                p1->elmt.temp_min=e.temp_min;
            }
        }
		else if(p1->next==NULL){
			p1->next=createLinkedList(e);
		}
		else{
            LinkedList* new =createLinkedList(e);

			new->next=p1->next;
			p1->next = new;
		}
	}
	return pList;           
}

void calculateAverageTab1(LinkedList * pList){
    LinkedList * p1=pList;
    while(p1->next != NULL){
        p1->elmt.temp_ave=p1->elmt.temp_ave/p1->elmt.ave_counter;
        p1=p1->next;
    }
    p1->elmt.temp_ave=p1->elmt.temp_ave/p1->elmt.ave_counter;
}

void treatList(LinkedList *pList,FILE* out){
	LinkedList* p1 =pList;
    if (pList == NULL){

    }
		
	else {
		while (p1->next != NULL) {
			fprintf(out,"%d ",p1->elmt.station);
            fprintf(out,"%f ",p1->elmt.temp_ave);
            fprintf(out,"%f ",p1->elmt.temp_max);
            fprintf(out,"%f\n",p1->elmt.temp_min);
			p1 = p1->next;
		}
		fprintf(out,"%d ",p1->elmt.station);
        fprintf(out,"%f ",p1->elmt.temp_ave);
        fprintf(out,"%f ",p1->elmt.temp_max);
        fprintf(out,"%f\n",p1->elmt.temp_min);
	}
}
