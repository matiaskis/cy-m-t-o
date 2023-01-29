#include "abr1.h"

void traiter(Data1ABR e,FILE* out) {
    fprintf(out,"%d ",e.station);
    fprintf(out,"%f\n",e.associated_data);
}

void parcoursInfixe(PABR1 a, FILE* out) {
if (a!=NULL) {
    parcoursInfixe(a->fg,out);
    traiter(a->elmt,out);
    free(a);
    parcoursInfixe(a->fd,out);
}
}

void parcoursInfixeR(PABR1 a, FILE* out) {
if (a!=NULL) {
    parcoursInfixeR(a->fd,out); 
    traiter(a->elmt,out);
    free(a);
    parcoursInfixeR(a->fg,out);
}
}



PABR1 creerArbre(Data1ABR e){
    PABR noeud ;
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



 

PABR1 insertionABRMax(PABR1 a,Data1ABR e){

    if (a== NULL){
        return creerArbre(e);
    }
    else if (e.station < a->elmt.station){
    a->fg=insertionABRMax(a->fg, e);

    }
    else if(e.station > a->elmt.station){
        a->fd=insertionABRMax(a->fd, e);
        
    }
    else{
        if(e.associated_data > a->elmt.associated_data){
            a->elmt=e;
        }
    
    }
    return a;
    }

PABR1 insertionABRMin(PABR1 a,Data1ABR e){

    if (a== NULL){

        return creerArbre(e);
    }
    else if (e.station < a->elmt.station){
    a->fg=insertionABRMin(a->fg, e);

    }
    else if(e.station > a->elmt.station){
        a->fd=insertionABRMin(a->fd, e);
        
    }
    else{
        if(e.associated_data < a->elmt.associated_data){
            a->elmt=e;
        }
     
       
    }
  
    
    return a;
    }
    
PABR1 insertionABRAverage(PABR1 a, Data1ABR e){

    if (a== NULL){
        return creerArbre(e);
    }
    else if (e.station < a->elmt.station){
        a->fg=insertionABRAverage(a->fg, e);
    }
    else if(e.station > a->elmt.station){
        a->fd=insertionABRAverage(a->fd, e);
        
    }
    else{
        a->elmt.associated_data=a->elmt.associated_data+e.associated_data;
        a->elmt.average_increment=a->elmt.average_increment+1;
    }
    return a;
    }
 
void calculateAverage(PABR1 a){
    if (a!=NULL) {
    calculateAverage(a->fg);
    a->elmt.associated_data=a->elmt.associated_data/a->elmt.average_increment;
    calculateAverage(a->fd);
    }
}
