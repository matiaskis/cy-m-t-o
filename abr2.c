#include "abr2.h"


void traiter_abr2(Data_abr2 e,FILE* out) {
    long h,d,m,y;
    h=((e.date2%100));
    d=((e.date2%10000)-e.date2%100)/100;
    m=((e.date2%1000000)-e.date2%10000)/10000;
    y=((e.date2)-e.date2%1000000)/1000000;
    fprintf(out,"%ld/%ld/%ld %ld:00:00 ",d,m,y,h);
    fprintf(out,"%f\n",e.associated_Data2);
}

void parcoursInfixe_abr2(PABR2 a, FILE* out) {
if (a!=NULL) {
    parcoursInfixe_abr2(a->fg,out);
    traiter_abr2(a->elmt,out);
    free(a);
    parcoursInfixe_abr2(a->fd,out);
}
}

void parcoursInfixeR_abr2(PABR2 a, FILE* out) {
if (a!=NULL) {
    parcoursInfixeR_abr2(a->fd,out); 
    traiter_abr2(a->elmt,out);
    parcoursInfixeR_abr2(a->fg,out);
}
}



PABR2 creerArbre_abr2(Data_abr2 e){
    PABR2 noeud ;
    noeud=malloc(sizeof(ABR2));
    if(noeud==NULL){
        exit(1);
    }
    noeud->elmt=e;
    noeud->fg= NULL;
    noeud->fd= NULL;
    noeud->equilibre= 0;
    noeud->elmt.average_increment=1;
    return noeud;
}

    
PABR2 insertionAverage_abr2(PABR2 a,Data_abr2 e){

    if (a== NULL){
        return creerArbre_abr2(e);
    }
    else if (e.date2 < a->elmt.date2){
    a->fg=insertionAverage_abr2(a->fg, e, h);
       
    }
    else if(e.date2 > a->elmt.date2){
        a->fd=insertionAverage_abr2(a->fd, e, h);
        
    }
    else{
        a->elmt.associated_Data2=a->elmt.associated_Data2+e.associated_Data2;
        a->elmt.average_increment=a->elmt.average_increment+1;
    }
    return a;
    }
 
void calculateAverage_abr2(PABR2 a){
    if (a!=NULL) {
    calculateAverage_abr2(a->fg);
    a->elmt.associated_Data2=a->elmt.associated_Data2/a->elmt.average_increment;
    calculateAverage_abr2(a->fd);
    }
}
