#include "abrm.h"



void treat_m(int count,Data_abrm e,FILE* out) {
    fprintf(out,"%d ",e.station);
    fprintf(out,"%d\n",e.moisture);
   
    for(int i=0; i < count; i++ ){
        fprintf(out,"%d ",e.doublon[i]);
        fprintf(out,"%d\n",e.moisture);
        
    }
      
    
  
}
void treat_m2(Data_abrm e,FILE* out) {
    fprintf(out,"%d ",e.station);
    fprintf(out,"%d\n",e.moisture);
}
 

void infixPath_m(PABR_m a, FILE* out) {
if (a!=NULL) {
    infixPath_m(a->fg,out);
    treat_m(a->elmt.counter,a->elmt,out);
    free(a);
    infixPath_m(a->fd,out);
}
}

void infixPathR_m(PABR_m a, FILE* out) {
if (a!=NULL) {
    infixPathR_m(a->fd,out); 
    treat_m(a->elmt.counter,a->elmt,out);
    free(a);
    infixPathR_m(a->fg,out);
}
}

void infixPath_m2(PABR_m a, FILE* out) {
if (a!=NULL) {
    infixPath_m2(a->fg,out);
    treat_m2(a->elmt,out);
    free(a);
    infixPath_m2(a->fd,out);
}
}

void infixPathR_m2(PABR_m a, FILE* out) {
if (a!=NULL) {
    infixPathR_m2(a->fd,out); 
    treat_m2(a->elmt,out);
    free(a);
    infixPathR_m2(a->fg,out);
}
}




PABR_m createTree_m(Data_abrm e){
    PABR_m tree ;
    tree=malloc(sizeof(ABR_m));
    if(tree==NULL){
        exit(1);
    }
    tree->elmt=e;
    tree->fg= NULL;
    tree->fd= NULL;
    return tree;
}





PABR_m insertionABRMMax(PABR_m a,Data_abrm e){

    if (a== NULL){
        return createTree_m(e);
    }
    else if (e.station < a->elmt.station){
    a->fg=insertionABRMMax(a->fg, e);
    }
    else if(e.station > a->elmt.station){
        a->fd=insertionABRMMax(a->fd, e);
        
    }
    else{
        if(e.moisture > a->elmt.moisture){
            a->elmt=e;
        }
        return a;
    }
    
    return a;
    }

PABR_m insertionABRM(PABR_m a,Data_abrm e){

    if (a== NULL){
       
        return createTree_m(e);
    }
    else if (e.moisture < a->elmt.moisture ){
    a->fg=insertionABRM(a->fg, e);
    }
    else if(e.moisture > a->elmt.moisture ){
        a->fd=insertionABRM(a->fd, e);
        
    }
    else{
        a->elmt.doublon[a->elmt.counter]=e.station;
        a->elmt.counter=a->elmt.counter+1;
                  
        return a;


    }
    
    return a;
    }