#include "abrh.h"

 

void treat_abrh(Data_abrh e,FILE* out) {
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




PABR_H createTree_abrh(Data_abrh e){
    PABR_H tree=NULL ;
    tree=(ABR_H *)malloc(sizeof(ABR_H));
    if(tree==NULL){
        exit(1);
    }
    tree->elmt=e;
    tree->elmt.duplicate[0]=0;
    tree->elmt.duplicate[1]=0;
    tree->elmt.duplicate[2]=0;
    tree->elmt.duplicate2[0]=0;
    tree->elmt.duplicate2[1]=0;
    tree->elmt.duplicate2[2]=0;

  
    tree->fg= NULL;
    tree->fd= NULL;
    
    return tree;
}




PABR_H insertionABRHeight(PABR_H a,Data_abrh e){

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
            if(e.station != a->elmt.duplicate[0] && a->elmt.duplicate[0] != 0 ){
                a->elmt.duplicate2[0]=e.station;
                a->elmt.duplicate2[1]=e.latitude;
                a->elmt.duplicate2[2]=e.longitude;
            }
            else{ a->elmt.duplicate[0]=e.station;
                a->elmt.duplicate[1]=e.latitude;
                a->elmt.duplicate[2]=e.longitude;
            }
        }
      
        return a;
    }

    
    return a;
    }

    
