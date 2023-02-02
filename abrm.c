#include "abrm.h"




void treat_abrm(int count,Data_abrm e,FILE* out) {
    fprintf(out,"%d ",e.station);
    fprintf(out,"%f ",e.latitude);
    fprintf(out,"%f ",e.longitude);
    fprintf(out,"%d\n",e.moisture);
   
    for(int i=0; i < count; i++ ){
        fprintf(out,"%d ",(int)e.duplicates[i]);
        fprintf(out,"%f ",e.duplicatela[i]);
        fprintf(out,"%f ",e.duplicatelo[i]);
        fprintf(out,"%d\n",e.moisture);
    }     
    
  
}
void treat_abrm2(Data_abrm e,FILE* out) {
     fprintf(out,"%d;",e.station);
    fprintf(out,"%d;",e.moisture);
    fprintf(out,"%f,",e.latitude);
    fprintf(out,"%f\n",e.longitude);
}
 

void infixPath_abrm(PABR_m a, FILE* out) {
if (a!=NULL) {
    infixPath_abrm(a->fg,out);
    treat_abrm(a->elmt.counter,a->elmt,out);
    free(a);
    infixPath_abrm(a->fd,out);
}
}

void infixPathR_abrm(PABR_m a, FILE* out) {
if (a!=NULL) {
    infixPathR_abrm(a->fd,out); 
    treat_abrm(a->elmt.counter,a->elmt,out);
    free(a);
    infixPathR_abrm(a->fg,out);
}
}

void infixPath_abrm2(PABR_m a, FILE* out) {
if (a!=NULL) {
    infixPath_abrm2(a->fg,out);
    treat_abrm2(a->elmt,out);
    free(a);
    infixPath_abrm2(a->fd,out);
}
}

void infixPathR_abrm2(PABR_m a, FILE* out) {
if (a!=NULL) {
    infixPathR_abrm2(a->fd,out); 
    treat_abrm2(a->elmt,out);
    free(a);
    infixPathR_abrm2(a->fg,out);
}
}




PABR_m createTree_abrm(Data_abrm e){
    PABR_m tree=NULL ;
    tree=malloc(sizeof(ABR_m));
    if(tree==NULL){
        exit(1);
    }
    tree->elmt=e;
    tree->elmt.counter=0;
    tree->fg= NULL;
    tree->fd= NULL;
    return tree;
}





PABR_m insertionABRMMax(PABR_m a,Data_abrm e){

    if (a== NULL){
        return createTree_abrm(e);
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
       
        return createTree_abrm(e);
    }
    else if (e.moisture < a->elmt.moisture ){
    a->fg=insertionABRM(a->fg, e);
    }
    else if(e.moisture > a->elmt.moisture ){
        a->fd=insertionABRM(a->fd, e);
        
    }
    else{
        a->elmt.duplicate[a->elmt.counter]=e.station;
        a->elmt.counter=a->elmt.counter+1;
                  
        return a;


    }
    
    return a;
    }

