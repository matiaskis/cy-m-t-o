#include "abr3.h"

void treat_abr3(Data_abr3 e,FILE* out){
    long h,d,m,y;
    h=((e.date%100));
    d=((e.date%10000)-e.date%100)/100;
    m=((e.date%1000000)-e.date%10000)/10000;
    y=((e.date)-e.date%1000000)/1000000;
    fprintf(out,"%ld/%ld/%ld-%ld:00:00 ",d,m,y,h);
    fprintf(out,"%d ",e.station);
    fprintf(out,"%f\n",e.associated_data);    
}

void secondInfixePath_abr3(PABR3 a,FILE * out){
    if (a!=NULL) {
        secondInfixePath_abr3(a->fg,out);
        treat_abr3(a->elmt,out);
        free(a);
        secondInfixePath_abr3(a->fd,out);
}
}

void infixPath_abr3(PABR3 a, FILE* out) {
if (a!=NULL) {
    infixPath_abr3(a->fg,out);
    secondInfixePath_abr3(a->secondTree,out);
    free(a);
    infixPath_abr3(a->fd,out);
}
}

void secondInfixePathR_abr3(PABR3 a,FILE * out){
    if (a!=NULL) {
        secondInfixePathR_abr3(a->fd,out);
        treat_abr3(a->elmt,out);
        free(a);
        secondInfixePathR_abr3(a->fg,out);
}
}

void infixPathR_abr3(PABR3 a, FILE* out) {
if (a!=NULL) {
    infixPathR_abr3(a->fd,out); 
    secondInfixePathR_abr3(a->secondTree,out);
    free(a);
    infixPathR_abr3(a->fg,out);
}
}



PABR3 createTree_abr3(Data_abr3 e){
    PABR3 tree=NULL ;
    tree=malloc(sizeof(ABR3));
    if(tree==NULL){
        exit(1);
    }
    tree->elmt=e;
    tree->fg= NULL;
    tree->fd= NULL;
    return tree;
}

PABR3 createTree_oabr3(Data_abr3 e){
    PABR3 tree=NULL ;
    tree=malloc(sizeof(ABR3));
    if(tree==NULL){
        exit(1);
    }
    tree->elmt=e;
    tree->fg= NULL;
    tree->fd= NULL;
    tree->secondTree=createTree_abr3(e);
    return tree;
}

PABR3 insertionABR3SecondTree(PABR3 a,Data_abr3 e){

    if (a== NULL){
      
        return createTree_abr3(e);
    }
    else if (e.station < a->elmt.station){
    a->fg=insertionABR3SecondTree(a->fg, e);
        
    }
    else if(e.station > a->elmt.station){
        a->fd=insertionABR3SecondTree(a->fd, e);
        
    }
    else{
        return a;
    }
    return a;
}

PABR3 insertion_oabr3(PABR3 a,Data_abr3 e){

    if (a== NULL){
     
        return createTree_oabr3(e);
    }
    else if (e.date < a->elmt.date){
        a->fg=insertion_oabr3(a->fg, e);
     

    }
    else if(e.date > a->elmt.date){
        a->fd=insertion_oabr3(a->fd, e);
    }
    else{
        a->secondTree=insertionABR3SecondTree(a->secondTree,e);
    }
    return a;
    }

