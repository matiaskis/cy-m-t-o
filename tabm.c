#include "tabm.h"


LinkedListm * createLinkedListm(Data_tabm e){
	LinkedListm * c =  malloc(sizeof(LinkedListm));
	if(c==NULL){
		exit(1);
	}
	c->elmt=e;
    c->elmt.counter=0;
	c->next=NULL;
	return c;
}

LinkedListm * insertionStartm(LinkedListm* pList, Data_tabm e){
	LinkedListm* new=createLinkedListm(e);
	new -> next = pList;
	return new;
}

LinkedListm * insertionTabm(LinkedListm *pList, Data_tabm e) {
	
	LinkedListm *p1 = pList;
	if(pList==NULL){
		return createLinkedListm(e);
	}
	else if (pList->elmt.moisture < e.moisture) {
		pList=insertionStartm(pList,e);
	}
	else{
		
		while(p1->next != NULL && p1->next->elmt.moisture >= e.moisture){ 
			p1=p1->next;
		}
        if(p1->elmt.moisture == e.moisture){
            p1->elmt.duplicates[p1->elmt.counter]=e.station;
            p1->elmt.duplicatela[p1->elmt.counter]=e.latitude;
            p1->elmt.duplicatelo[p1->elmt.counter]=e.longitude;
            p1->elmt.counter=p1->elmt.counter+1;
                
        }
		else if(p1->next==NULL){
			p1->next=createLinkedListm(e);
		}
		else{
            LinkedListm* new =createLinkedListm(e);

			new->next=p1->next;
			p1->next = new;
		}
	}
	return pList;           
}
LinkedListm * insertionTabMAXm(LinkedListm *pList, Data_tabm e) {
	
	LinkedListm *p1 = pList;
	if(pList==NULL){
		return createLinkedListm(e);
	}
	else if (pList->elmt.station > e.station) {
		pList=insertionStartm(pList,e);
	}
	else{
		
		while(p1->next != NULL && p1->next->elmt.station <= e.station){ 
			p1=p1->next;
		}
        if(p1->elmt.station == e.station){
            if(p1->elmt.moisture < e.moisture){
                p1->elmt.moisture = e.moisture;
            }
            
        }
		else if(p1->next==NULL){
			p1->next=createLinkedListm(e);
		}
		else{
            LinkedListm* new =createLinkedListm(e);

			new->next=p1->next;
			p1->next = new;
		}
	}
	return pList;           
}

void treat_tabm2(LinkedListm* pList,FILE* out) {
    LinkedListm* p1 =pList;
    if (pList == NULL){

    }
		
	else {
		while (p1->next != NULL) {
            fprintf(out,"%d;",p1->elmt.station);
            fprintf(out,"%d;",p1->elmt.moisture);
            fprintf(out,"%f,",p1->elmt.latitude);
            fprintf(out,"%f\n",p1->elmt.longitude);
            p1 = p1->next;
        }
        fprintf(out,"%d;",p1->elmt.station);
        fprintf(out,"%d;",p1->elmt.moisture);
        fprintf(out,"%f,",p1->elmt.latitude);
        fprintf(out,"%f\n",p1->elmt.longitude);
    }
}

void treat_tabm(LinkedListm* pList,FILE* out) {
    LinkedListm* p1 =pList;
    if (pList == NULL){

    }
		
	else {
		while (p1->next != NULL) {
            fprintf(out,"%d ",p1->elmt.station);
            fprintf(out,"%f ",p1->elmt.latitude);
            fprintf(out,"%f ",p1->elmt.longitude);
            fprintf(out,"%d\n",p1->elmt.moisture);
   
            for(int i=0; i < p1->elmt.counter; i++ ){
                fprintf(out,"%d ",(int)p1->elmt.duplicates[i]);
                fprintf(out,"%f ",p1->elmt.duplicatela[i]);
                fprintf(out,"%f ",p1->elmt.duplicatelo[i]);
                fprintf(out,"%d\n",p1->elmt.moisture);
            }   
            p1 = p1->next;     
        }
        fprintf(out,"%d ",p1->elmt.station);
        fprintf(out,"%f ",p1->elmt.latitude);
        fprintf(out,"%f ",p1->elmt.longitude);
        fprintf(out,"%d\n",p1->elmt.moisture);
   
        for(int i=0; i < p1->elmt.counter; i++ ){
            fprintf(out,"%d ",(int)p1->elmt.duplicates[i]);
            fprintf(out,"%f ",p1->elmt.duplicatela[i]);
            fprintf(out,"%f ",p1->elmt.duplicatelo[i]);
            fprintf(out,"%d\n",p1->elmt.moisture);
        }   
    }
}
