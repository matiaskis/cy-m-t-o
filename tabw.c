#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct data_tabw{
    int station;
    float win1_ave;
    float win2_ave;
    float latitude
    float longitude
    int ave_counter;
}Data_tabw;

typedef struct linkedListw {
	Data_tabw elmt;
	struct linkedListw* next;
}LinkedListw;



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

LinkedListw * insertionStart(LinkedListw* pList, Data_tabw e){
	LinkedListw* new=createLinkedListw(e);
	new -> next = pList;
	return new;
}

LinkedListw * insertionTab1(LinkedListw *pList, Data_tabw e) {
	
	LinkedListw *p1 = pList;
	if(pList==NULL){
		pList=createLinkedListw(e);
	}
	else if (pList->elmt.station > e.station) {
		pList=insertionStart(pList,e);
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

void calculateAverageTab1(LinkedListw * pList){
    LinkedListw * p1=pList;
    while(p1->next != NULL){
        p1->elmt.wind1_ave=p1->elmt.wind1_ave/p1->elmt.ave_counter;
        p1->elmt.wind2_ave=p1->elmt.wind2/p1->elmt.ave_counter;
    }
    p1->elmt.wind1_ave=p1->elmt.temp_ave/p1->elmt.ave_counter;
    p1->elmt.wind2_ave=p1->elmt.wind2/p1->elmt.ave_counter;

}

void treatList(LinkedListw *pList,FILE* out){
	LinkedListw* p1 =pList;
    if (pList == NULL){

    }
		
	else {
		while (p1->next != NULL) {
			fprintf(out,"%d ",p1->elmt.station);
            fprintf(out,"%f ",p1->elmt.win1_ave);
            fprintf(out,"%f ",p1->elmt.win2_ave);
            fprintf(out,"%f ",p1->elmt.latitude);
            fprintf(out,"%f\n",p1->elmt.longitude);
			p1 = p1->next;
		}
		fprintf(out,"%d ",p1->elmt.station);
        fprintf(out,"%f ",p1->elmt.win1_ave);
        fprintf(out,"%f ",p1->elmt.win2_ave);
        fprintf(out,"%f ",p1->elmt.latitude);
        fprintf(out,"%f\n",p1->elmt.longitude);
	}
}

int main(int argc, char * argv[]){
    int station;
    float temp;
    Data_tabw e;
    LinkedListw * pList=NULL;
    FILE* data_file=fopen(argv[1],"r+");
    FILE* output_file=fopen(argv[2],"w");
    while(fscanf(data_file,"%d;",&station) == 1 ){
        fscanf(data_file,"%f",&temp) == 1;
        e.station=station;
        e.temp_ave=temp;
        e.temp_max=temp;
        e.temp_min=temp;
        
        pList=insertionTab1(pList,e);
        
    }
    printf("jxgasfqGJXJQVCJFQDfcj");
    calculateAverageTab1(pList);
    treatList(pList,output_file);
}
