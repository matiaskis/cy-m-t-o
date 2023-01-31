
#include "avl1.h"
#include "avlM.h"



void traiter_m(int count,Data_m e,FILE* out) {
    fprintf(out,"%d ",e.station);
    fprintf(out,"%d\n",e.moisture);
   
    for(int i=0; i < count; i++ ){
        fprintf(out,"%d ",e.doublon[i]);
        fprintf(out,"%d\n",e.moisture);
        
    }
      
    
  
}
void traiter_m2(Data_m e,FILE* out) {
    fprintf(out,"%d ",e.station);
    fprintf(out,"%d\n",e.moisture);
}
 

void parcoursInfixe_m(PAVL_m a, FILE* out) {
if (a!=NULL) {
    parcoursInfixe_m(a->fg,out);
    traiter_m(a->elmt.counter,a->elmt,out);
    free(a);
    parcoursInfixe_m(a->fd,out);
}
}

void parcoursInfixeR_m(PAVL_m a, FILE* out) {
if (a!=NULL) {
    parcoursInfixeR_m(a->fd,out); 
    traiter_m(a->elmt.counter,a->elmt,out);
    free(a);
    parcoursInfixeR_m(a->fg,out);
}
}

void parcoursInfixe_m2(PAVL_m a, FILE* out) {
if (a!=NULL) {
    parcoursInfixe_m2(a->fg,out);
    traiter_m2(a->elmt,out);
    free(a);
    parcoursInfixe_m2(a->fd,out);
}
}

void parcoursInfixeR_m2(PAVL_m a, FILE* out) {
if (a!=NULL) {
    parcoursInfixeR_m2(a->fd,out); 
    traiter_m2(a->elmt,out);
    free(a);
    parcoursInfixeR_m2(a->fg,out);
}
}




PAVL_m creerArbre_m(Data_m e){
    PAVL_m noeud ;
    noeud=malloc(sizeof(AVL_m));
    if(noeud==NULL){
        exit(1);
    }
    noeud->elmt=e;
    noeud->fg= NULL;
    noeud->fd= NULL;
    noeud->equilibre= 0;
    return noeud;
}


PAVL_m rotationGauche_m(PAVL_m a){

 

    PAVL_m pivot; 
    float eq_a, eq_p;

 

    pivot = a->fd;
    a->fd = pivot->fg;
    pivot->fg = a;
    eq_a = a->equilibre;
    eq_p = pivot->equilibre;
    a->equilibre = eq_a - max(eq_p, 0) - 1;
    pivot->equilibre = min(min( eq_a-2, eq_a+eq_p-2), eq_p-1 );
    a = pivot;
    return a;
    }

 

    PAVL_m rotationDroite_m(PAVL_m a){

 

    PAVL_m pivot ;
    float eq_a, eq_p;

 

    pivot = a->fg;
    a->fg = pivot->fd;
    pivot->fd = a;
    eq_a = a->equilibre;
    eq_p = pivot->equilibre;
    a->equilibre = eq_a - min(eq_p, 0) + 1;
    pivot->equilibre = max(max( eq_a+2, eq_a+eq_p+2), eq_p+1 );
    a = pivot;
    return a;
}

 

PAVL_m doubleRotationGauche_m(PAVL_m a){

 

    a->fd = rotationDroite_m(a->fd);
     return rotationGauche_m(a);
}

 

PAVL_m doubleRotationDroite_m(PAVL_m a){
    a->fg = rotationGauche_m(a->fg);
     return rotationDroite_m(a);
}

 

PAVL_m equilibrerAVL_m(PAVL_m a){

 

if (a->equilibre >=  2){
    if (a->fd->equilibre >= 0){
        return rotationGauche_m(a);
    }

    else return doubleRotationGauche_m(a);
}
else if (a->equilibre  <=  -2){ 
    if (a->fg->equilibre <= 0){
         return rotationDroite_m(a);
    }

 

    else return doubleRotationDroite_m(a);
}
return a;
}


PAVL_m insertionAVLMMax(PAVL_m a,Data_m e, int* h){

    if (a== NULL){
        *h=1;
        return creerArbre_m(e);
    }
    else if (e.station < a->elmt.station){
    a->fg=insertionAVLMMax(a->fg, e, h);
        *h =-*h; 
    }
    else if(e.station > a->elmt.station){
        a->fd=insertionAVLMMax(a->fd, e, h);
        
    }
    else{
        if(e.moisture > a->elmt.moisture){
            a->elmt=e;
        }
        *h=0;
        return a;
    }
    if (*h != 0){
        a->equilibre = a->equilibre + *h;
        a=equilibrerAVL_m(a);
        if (a->equilibre== 0){
            *h = 0;
        }
        else *h = 1;
    }
    
    return a;
    }

PAVL_m insertionAVLM(PAVL_m a,Data_m e, int* h){

    if (a== NULL){
        *h=1;
       
        return creerArbre_m(e);
    }
    else if (e.moisture < a->elmt.moisture ){
    a->fg=insertionAVLM(a->fg, e, h);
        *h =-*h; 
    }
    else if(e.moisture > a->elmt.moisture ){
        a->fd=insertionAVLM(a->fd, e, h);
        
    }
    else{
        a->elmt.doublon[a->elmt.counter]=e.station;
        a->elmt.counter=a->elmt.counter+1;
                  
        
        *h=0;
        return a;


    }
    if (*h != 0){
        a->equilibre = a->equilibre + *h;
        a=equilibrerAVL_m(a);
        if (a->equilibre== 0){
            *h = 0;
        }
        else *h = 1;
    }
    
    return a;
    }
