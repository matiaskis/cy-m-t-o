#include "abr1.h"


void traiter_abr1(Data1ABR e,FILE* out) {
    fprintf(out,"%d ",e.station);
    fprintf(out,"%f\n",e.associated_data);
}

void parcoursInfixe_abr1(PABR1 a, FILE* out) {
if (a!=NULL) {
    parcoursInfixe_abr1(a->fg,out);
    traite_abr1r(a->elmt,out);
    free(a);
    parcoursInfixe_abr1(a->fd,out);
}
}

void parcoursInfixeR_abr1(PABR1 a, FILE* out) {
if (a!=NULL) {
    parcoursInfixeR_abr1(a->fd,out); 
    traiter_abr1(a->elmt,out);
    free(a);
    parcoursInfixeR_abr1(a->fg,out);
}
}



PABR1 creerArbre_abr1(Data1ABR e){
    PABR1 noeud ;
    noeud=malloc(sizeof(ABR));
    if(noeud==NULL){
        exit(1);
    }
    noeud->elmt=e;
    noeud->fg= NULL;
    noeud->fd= NULL;
    noeud->elmt.average_increment=1;
    return noeud;
}



 

PABR1 insertionMax_abr1(PABR1 a,Data1ABR e){

    if (a== NULL){
        return creerArbre(e);
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

        return creerArbre_abr1(e);
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
        return creerArbre_abr1(e);
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
