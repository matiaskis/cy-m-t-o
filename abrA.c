#include "abrA.h"

void treat_abra(Data_abra e,FILE* out) {
    fprintf(out,"%d ",e.station);
    fprintf(out,"%f ",e.associated_DataA1);
    fprintf(out,"%f ",e.associated_DataA2);
    fprintf(out,"%f ",e.latitude);
    fprintf(out,"%f\n",e.longitude);
}

void infixPath_abra(PABRAA a, FILE* out) {
if (a!=NULL) {
    infixPath_abra(a->fg,out);
    treat_abra(a->elmt,out);
    free(a);
    infixPath_abra(a->fd,out);
}
}

void infixPathR_abra(PABRAA a, FILE* out) {
if (a!=NULL) {
    infixPathR_abra(a->fd,out); 
    treat_abra(a->elmt,out);
    free(a);
    infixPathR_abra(a->fg,out);
}
}

PABRAA createTree_abra(Data_abra e){
    PABRAA tree ;
    tree=malloc(sizeof(ABRAA));
    if(tree==NULL){
        exit(1);
    }
    tree->elmt=e;
    tree->fg= NULL;
    tree->fd= NULL;
    tree->elmt.average_increment=1;  
    return tree;
}

PABRAA insertionAverage_abra(PABRAA a,Data_abra e){

    if (a== NULL){
     
        return createTree_abra(e);
    }
    else if (e.station < a->elmt.station){
        a->fg=insertionAverage_abra(a->fg, e);
   
    }
    else if(e.station > a->elmt.station){
        a->fd=insertionAverage_abra(a->fd, e);
        
    }
    else{
        a->elmt.associated_DataA1=a->elmt.associated_DataA1+e.associated_DataA1;
        a->elmt.associated_DataA2=a->elmt.associated_DataA2+e.associated_DataA2;
        a->elmt.average_increment=a->elmt.average_increment+1;

        return a;
    }
 
    return a;
    }
 
void calculateAverage_abra(PABRAA a){
    if (a!=NULL) {
        calculateAverage_abra(a->fg);
        a->elmt.associated_DataA1=a->elmt.associated_DataA1/a->elmt.average_increment;
        a->elmt.associated_DataA2=a->elmt.associated_DataA2/a->elmt.average_increment;
        calculateAverage_abra(a->fd);
    }
}


