#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "avlh.h"
#include "avl1.h"

 

void treat_abrh(Date_abrh e,FILE* out) {
    fprintf(out,"%d ",e.station);
    fprintf(out,"%d\n",e.height);
   // fprintf(out,"%f ",e.latitude);
    //fprintf(out,"%f\n",e.longitude);
    if(e.duplicate!=0){
        fprintf(out,"%d ",e.duplicate);
        fprintf(out,"%d\n",e.height);
        //fprintf(out,"%f ",e.latitude);
        //fprintf(out,"%f\n",e.longitude);
    }
    if(e.duplicate2 !=0 ){
        fprintf(out,"%d ",e.duplicate2);
        fprintf(out,"%d\n",e.height);
    }
}

 

void infixPath_abrh(PABR_H a, FILE* out) {
if (a!=NULL) {
    infixPath_abrh(a->fg,out);
    treat_abrh(a->elmt,out);
    free(a);
    infixPath_abrh(a->fd,out);
}
}

void infixPathR_abrh(PABR_H a, FILE* out) {
if (a!=NULL) {
    infixPathR_abrh(a->fd,out); 
    treat_abrh(a->elmt,out);
    free(a);
    infixPathR_abrh(a->fg,out);
}
}




PABR_H createTree_abrh(Date_abrh e){
    PABR_H tree ;
    tree=malloc(sizeof(ABR_H));
    if(tree==NULL){
        exit(1);
    }
    tree->elmt=e;
    tree->fg= NULL;
    tree->fd= NULL;
    tree->equilibre= 0;
    return tree;
}




PABR_H insertionABRHeight(PABR_H a,Date_abrh e){

    if (a== NULL){
   
        return createTree_abrh(e);
    }
    else if (e.height < a->elmt.height){
    a->fg=insertionABRHeight(a->fg, e);
      
    }
    else if(e.height > a->elmt.height){
        a->fd=insertionABRHeight(a->fd, e);
        
    }
    else{
        if(e.station!=a->elmt.station){
            if(e.station != a->elmt.duplicate && a->elmt.duplicate != 0 ){
                a->elmt.duplicate2=e.station;
            }
            else a->elmt.duplicate=e.station;
        }
      
        return a;
    }

    
    return a;
    }
