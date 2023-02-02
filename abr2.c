#include "abr2.h"


void treat_abr2(Data_abr2 e,FILE* out) {
    long h,d,m,y;
    h=((e.date%100));
    d=((e.date%10000)-e.date%100)/100;
    m=((e.date%1000000)-e.date%10000)/10000;
    y=((e.date)-e.date%1000000)/1000000;
    fprintf(out,"%ld/%ld/%ld %ld:00:00 ",d,m,y,h);
    fprintf(out,"%f\n",e.associated_data);
}

void infixPath_abr2(PABR2 a, FILE* out) {
if (a!=NULL) {
    infixPath_abr2(a->fg,out);
    treat_abr2(a->elmt,out);
    free(a);
    infixPath_abr2(a->fd,out);
}
}

void infixPathR_abr2(PABR2 a, FILE* out) {
if (a!=NULL) {
    infixPathR_abr2(a->fd,out); 
    treat_abr2(a->elmt,out);
    infixPathR_abr2(a->fg,out);
}
}



PABR2 createTree_abr2(Data_abr2 e){
    PABR2 tree=NULL ;
    tree=malloc(sizeof(ABR2));
    if(tree==NULL){
        exit(1);
    }
    tree->elmt=e;
    tree->fg= NULL;
    tree->fd= NULL;
    tree->elmt.average_increment=1;
    return tree;
}

    
PABR2 insertionAverage_abr2(PABR2 a,Data_abr2 e){

    if (a== NULL){
        return createTree_abr2(e);
    }
    else if (e.date < a->elmt.date){
    a->fg=insertionAverage_abr2(a->fg, e);
       
    }
    else if(e.date > a->elmt.date){
        a->fd=insertionAverage_abr2(a->fd, e);
        
    }
    else{
        a->elmt.associated_data=a->elmt.associated_data+e.associated_data;
        a->elmt.average_increment=a->elmt.average_increment+1;
    }
    return a;
    }
 
void calculateAverage_abr2(PABR2 a){
    if (a!=NULL) {
    calculateAverage_abr2(a->fg);
    a->elmt.associated_data=a->elmt.associated_data/a->elmt.average_increment;
    calculateAverage_abr2(a->fd);
    }
}

