#include "abr1.h"


void treat_abr1(Data1ABR e,FILE* out) {
    fprintf(out,"%d ",e.station);
    fprintf(out,"%f\n",e.associated_data);
}

void infixPath_abr1(PABR1 a, FILE* out) {
if (a!=NULL) {
    infixPath_abr1(a->fg,out);
    traite_abr1(a->elmt,out);
    free(a);
    infixPath_abr1(a->fd,out);
}
}

void infixPathR_abr1(PABR1 a, FILE* out) {
if (a!=NULL) {
    infixPathR_abr1(a->fd,out); 
    treat_abr1(a->elmt,out);
    free(a);
    infixPathR_abr1(a->fg,out);
}
}



PABR1 createTree_abr1(Data1ABR e){
    PABR1 tree ;
    tree=malloc(sizeof(ABR1));
    if(tree==NULL){
        exit(1);
    }
    tree->elmt=e;
    tree->fg= NULL;
    tree->fd= NULL;
    tree->elmt.average_increment=1;
    return tree;
}



 

PABR1 insertionMax_abr1(PABR1 a,Data1ABR e){

    if (a== NULL){
        return createTree_abr1(e);
    }
    else if (e.station < a->elmt.station){
    a->fg=insertionMax_abr1(a->fg, e);

    }
    else if(e.station > a->elmt.station){
        a->fd=insertionMax_abr1(a->fd, e);
        
    }
    else{
        if(e.associated_data > a->elmt.associated_data){
            a->elmt=e;
        }
    
    }
    return a;
    }

PABR1 insertionMin_abr1(PABR1 a,Data1ABR e){

    if (a== NULL){

        return createTree_abr1(e);
    }
    else if (e.station < a->elmt.station){
    a->fg=insertionMin_abr1(a->fg, e);

    }
    else if(e.station > a->elmt.station){
        a->fd=insertionMin_abr1(a->fd, e);
        
    }
    else{
        if(e.associated_data < a->elmt.associated_data){
            a->elmt=e;
        }
     
       
    }
  
    
    return a;
    }
    
PABR1 insertionAverage_abr1(PABR1 a, Data1ABR e){

    if (a== NULL){
        return createTree_abr1(e);
    }
    else if (e.station < a->elmt.station){
        a->fg=insertionAverage_abr1(a->fg, e);
    }
    else if(e.station > a->elmt.station){
        a->fd=insertionAverage_abr1(a->fd, e);
        
    }
    else{
        a->elmt.associated_data=a->elmt.associated_data+e.associated_data;
        a->elmt.average_increment=a->elmt.average_increment+1;
    }
    return a;
    }
 
void calculateAverage_abr1(PABR1 a){
    if (a!=NULL) {
    calculateAverage_abr1(a->fg);
    a->elmt.associated_data=a->elmt.associated_data/a->elmt.average_increment;
    calculateAverage_abr1(a->fd);
    }
}
