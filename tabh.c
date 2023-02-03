#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct data_tabh{
    int station;
    int height
    float latitude
    float longitude
    float duplicate[3];
    float duplicate2[3];

}Data_tabh;

typedef struct linkedListh {
	Data_tabh elmt;
	struct linkedListh* next;
}LinkedListh;



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

LinkedListh * insertionStart(LinkedListh* pList, Data_tabh e){
	LinkedListh* new=createLinkedListh(e);
	new -> next = pList;
	return new;
}

LinkedListh * insertionTab1(LinkedListh *pList, Data_tabh e) {
	
	LinkedListh *p1 = pList;
	if(pList==NULL){
		pList=createLinkedListh(e);
	}
	else if (pList->elmt.height < e.height) {
		pList=insertionStart(pList,e);
	}
	else{
		
		while(p1->next != NULL && p1->next->elmt.height >= e.height){ 
			p1=p1->next;
		}
        if(p1->elmt.height == e.height){
            if(e.station!=a->elmt.station){
                if(e.station != a->elmt.duplicate[0] && a->elmt.duplicate[0] != 0 ){
                    a->elmt.duplicate2[0]=e.station;
                    a->elmt.duplicate2[1]=e.latitude;
                    a->elmt.duplicate2[2]=e.longitude;
                }
                else{ 
                    a->elmt.duplicate[0]=e.station;
                    a->elmt.duplicate[1]=e.latitude;
                    a->elmt.duplicate[2]=e.longitude;
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


void treatList(LinkedListh *pList,FILE* out){
	LinkedListh* p1 =pList;
    if (pList == NULL){

    }
		
	else {
		while (p1->next != NULL) {
                fprintf(out,"%d ",e.station);
                fprintf(out,"%d ",e.height);
                fprintf(out,"%f ",e.latitude);
                fprintf(out,"%f\n",e.longitude);
            if(e.duplicate[0]!=0){
                fprintf(out,"%d ",(int)e.duplicate[0]);
                fprintf(out,"%d ",e.height);
                fprintf(out,"%f ",e.duplicate[1]);
                fprintf(out,"%f\n",e.duplicate[2]);
            }
            if(e.duplicate2[0] !=0 ){
                fprintf(out,"%d ",(int)e.duplicate2[0]);
                fprintf(out,"%d ",e.height);
                fprintf(out,"%f ",e.duplicate2[1]);
                fprintf(out,"%f\n",e.duplicate2[2]);
            }
			p1 = p1->next;
		}
        fprintf(out,"%d ",e.station);
        fprintf(out,"%d ",e.height);
        fprintf(out,"%f ",e.latitude);
        fprintf(out,"%f\n",e.longitude);
        if(e.duplicate[0]!=0){
            fprintf(out,"%d ",(int)e.duplicate[0]);
            fprintf(out,"%d ",e.height);
            fprintf(out,"%f ",e.duplicate[1]);
            fprintf(out,"%f\n",e.duplicate[2]);
        }
        if(e.duplicate2[0] !=0 ){
            fprintf(out,"%d ",(int)e.duplicate2[0]);
            fprintf(out,"%d ",e.height);
            fprintf(out,"%f ",e.duplicate2[1]);
            fprintf(out,"%f\n",e.duplicate2[2]);
        }
	}
}

int main(int argc, char * argv[]){
    int station;
    float temp;
    Data_tabh e;
    LinkedListh * pList=NULL;
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
    
    treatList(pList,output_file);
}
