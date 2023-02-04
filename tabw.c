#include "tabw.h"


LinkedListw * createLinkedListw(Data_tabw e){
	LinkedListw * c =  malloc(sizeof(LinkedListw));
	if(c==NULL){
		exit(1);
	}
	c->elmt=e;
    c->elmt.ave_counter=1;
	c->next=NULL;
	return c;
}

LinkedListw * insertionStartw(LinkedListw* pList, Data_tabw e){
	LinkedListw* new=createLinkedListw(e);
	new -> next = pList;
	return new;
}

LinkedListw * insertionTabw(LinkedListw *pList, Data_tabw e) {
	
	LinkedListw *p1 = pList;
	if(pList==NULL){
		return createLinkedListw(e);
	}
	else if (pList->elmt.station > e.station) {
		pList=insertionStartw(pList,e);
	}
	else{
		
		while(p1->next != NULL && p1->next->elmt.station <= e.station){ 
			p1=p1->next;
		}
        if(p1->elmt.station == e.station){
            
            p1->elmt.wind1_ave=p1->elmt.wind1_ave+e.wind1_ave;
            p1->elmt.wind2_ave=p1->elmt.wind2_ave+e.wind2_ave;

            p1->elmt.ave_counter=p1->elmt.ave_counter+1;
            
        }
		else if(p1->next==NULL){
			p1->next=createLinkedListw(e);
		}
		else{
            LinkedListw* new =createLinkedListw(e);

			new->next=p1->next;
			p1->next = new;
		}
	}
	return pList;           
}

void calculateAverageTabw(LinkedListw * pList){
    LinkedListw * p1=pList;
    while(p1->next != NULL){
        p1->elmt.wind1_ave=p1->elmt.wind1_ave/p1->elmt.ave_counter;
        p1->elmt.wind2_ave=p1->elmt.wind2_ave/p1->elmt.ave_counter;
		p1=p1->next;
    }
    p1->elmt.wind1_ave=p1->elmt.wind1_ave/p1->elmt.ave_counter;
    p1->elmt.wind2_ave=p1->elmt.wind2_ave/p1->elmt.ave_counter;

}

void treatListw(LinkedListw *pList,FILE* out){
	LinkedListw* p1 =pList;
    if (pList == NULL){

    }
		
	else {
		while (p1->next != NULL) {
			fprintf(out,"%d ",p1->elmt.station);
            fprintf(out,"%f ",p1->elmt.wind1_ave);
            fprintf(out,"%f ",p1->elmt.wind2_ave);
            fprintf(out,"%f ",p1->elmt.latitude);
            fprintf(out,"%f\n",p1->elmt.longitude);
			p1 = p1->next;
		}
		fprintf(out,"%d ",p1->elmt.station);
        fprintf(out,"%f ",p1->elmt.wind1_ave);
        fprintf(out,"%f ",p1->elmt.wind2_ave);
        fprintf(out,"%f ",p1->elmt.latitude);
        fprintf(out,"%f\n",p1->elmt.longitude);
	}
}
