#include "tabh.h"


LinkedListh * createLinkedListh(Data_tabh e){
	LinkedListh * c =  malloc(sizeof(LinkedListh));
	if(c==NULL){
		exit(1);
	}
	c->elmt=e;
    c->elmt.duplicate[0]=0;
    c->elmt.duplicate[1]=0;
    c->elmt.duplicate[2]=0;
    c->elmt.duplicate2[0]=0;
    c->elmt.duplicate2[1]=0;
    c->elmt.duplicate2[2]=0;

	c->next=NULL;
	return c;
}

LinkedListh * insertionStarth(LinkedListh* pList, Data_tabh e){
	LinkedListh* new=createLinkedListh(e);
	new -> next = pList;
	return new;
}

LinkedListh * insertionTabh(LinkedListh *pList, Data_tabh e) {
	
	LinkedListh *p1 = pList;
	if(pList==NULL){
		return createLinkedListh(e);
	}
	else if (pList->elmt.height < e.height) {
		pList=insertionStarth(pList,e);
	}
	else{
		
		while(p1->next != NULL && p1->next->elmt.height >= e.height){ 
			p1=p1->next;
		}
        if(p1->elmt.height == e.height){
            if(e.station!=p1->elmt.station){
                if(e.station != p1->elmt.duplicate[0] && p1->elmt.duplicate[0] != 0 ){
                    p1->elmt.duplicate2[0]=e.station;
                    p1->elmt.duplicate2[1]=e.latitude;
                    p1->elmt.duplicate2[2]=e.longitude;
                }
                else{ 
                    p1->elmt.duplicate[0]=e.station;
                    p1->elmt.duplicate[1]=e.latitude;
                    p1->elmt.duplicate[2]=e.longitude;
                }
            }
            
        }
		else if(p1->next==NULL){
			p1->next=createLinkedListh(e);
		}
		else{
            LinkedListh* new =createLinkedListh(e);

			new->next=p1->next;
			p1->next = new;
		}
	}
	return pList;           
}


void treatListh(LinkedListh *pList,FILE* out){
	LinkedListh* p1 =pList;
    if (pList == NULL){

    }
		
	else {
		while (p1->next != NULL) {
                fprintf(out,"%d ",p1->elmt.station);
                fprintf(out,"%d ",p1->elmt.height);
                fprintf(out,"%f ",p1->elmt.latitude);
                fprintf(out,"%f\n",p1->elmt.longitude);
            if(p1->elmt.duplicate[0]!=0){
                fprintf(out,"%d ",(int)p1->elmt.duplicate[0]);
                fprintf(out,"%d ",p1->elmt.height);
                fprintf(out,"%f ",p1->elmt.duplicate[1]);
                fprintf(out,"%f\n",p1->elmt.duplicate[2]);
            }
            if(p1->elmt.duplicate2[0] !=0 ){
                fprintf(out,"%d ",(int)p1->elmt.duplicate2[0]);
                fprintf(out,"%d ",p1->elmt.height);
                fprintf(out,"%f ",p1->elmt.duplicate2[1]);
                fprintf(out,"%f\n",p1->elmt.duplicate2[2]);
            }
			p1 = p1->next;
		}
        fprintf(out,"%d ",p1->elmt.station);
        fprintf(out,"%d ",p1->elmt.height);
        fprintf(out,"%f ",p1->elmt.latitude);
        fprintf(out,"%f\n",p1->elmt.longitude);
        if(p1->elmt.duplicate[0]!=0){
            fprintf(out,"%d ",(int)p1->elmt.duplicate[0]);
            fprintf(out,"%d ",p1->elmt.height);
            fprintf(out,"%f ",p1->elmt.duplicate[1]);
            fprintf(out,"%f\n",p1->elmt.duplicate[2]);
        }
        if(p1->elmt.duplicate2[0] !=0 ){
            fprintf(out,"%d ",(int)p1->elmt.duplicate2[0]);
            fprintf(out,"%d ",p1->elmt.height);
            fprintf(out,"%f ",p1->elmt.duplicate2[1]);
            fprintf(out,"%f\n",p1->elmt.duplicate2[2]);
        }
	}
}
