#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "avlh.h"
#include "avl1.h"

 

void traiter_h(Data_h e,FILE* out) {
    fprintf(out,"%d ",e.station);
    fprintf(out,"%d\n",e.height);
   // fprintf(out,"%f ",e.latitude);
    //fprintf(out,"%f\n",e.longitude);
    if(e.doublon!=0){
        fprintf(out,"%d ",e.doublon);
        fprintf(out,"%d\n",e.height);
        //fprintf(out,"%f ",e.latitude);
        //fprintf(out,"%f\n",e.longitude);
    }
    if(e.doublon2 !=0 ){
        fprintf(out,"%d ",e.doublon2);
        fprintf(out,"%d\n",e.height);
    }
}

 

void parcoursInfixe_h(PAVL_H a, FILE* out) {
if (a!=NULL) {
    parcoursInfixe_h(a->fg,out);
    traiter_h(a->elmt,out);
    free(a);
    parcoursInfixe_h(a->fd,out);
}
}

void parcoursInfixeR_h(PAVL_H a, FILE* out) {
if (a!=NULL) {
    parcoursInfixeR_h(a->fd,out); 
    traiter_h(a->elmt,out);
    free(a);
    parcoursInfixeR_h(a->fg,out);
}
}




PAVL_H creerArbre_h(Data_h e){
    PAVL_H noeud ;
    noeud=malloc(sizeof(AVL_H));
    if(noeud==NULL){
        exit(1);
    }
    noeud->elmt=e;
    noeud->fg= NULL;
    noeud->fd= NULL;
    noeud->equilibre= 0;
    return noeud;
}


PAVL_H rotationGauche_h(PAVL_H a){

 

    PAVL_H pivot; 
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

 

    PAVL_H rotationDroite_h(PAVL_H a){

 

    PAVL_H pivot ;
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

 

PAVL_H doubleRotationGauche_h(PAVL_H a){

 

    a->fd = rotationDroite_h(a->fd);
     return rotationGauche_h(a);
}

 

PAVL_H doubleRotationDroite_h(PAVL_H a){
    a->fg = rotationGauche_h(a->fg);
     return rotationDroite_h(a);
}

 

PAVL_H equilibrerAVL_h(PAVL_H a){

 

if (a->equilibre >=  2){
    if (a->fd->equilibre >= 0){
        return rotationGauche_h(a);
    }

    else return doubleRotationGauche_h(a);
}
else if (a->equilibre  <=  -2){ 
    if (a->fg->equilibre <= 0){
         return rotationDroite_h(a);
    }

 

    else return doubleRotationDroite_h(a);
}
return a;
}


PAVL_H insertionAVLHHeight(PAVL_H a,Data_h e, int* h){

    if (a== NULL){
        *h=1;
        return creerArbre_h(e);
    }
    else if (e.height < a->elmt.height){
    a->fg=insertionAVLHHeight(a->fg, e, h);
        *h =-*h; 
    }
    else if(e.height > a->elmt.height){
        a->fd=insertionAVLHHeight(a->fd, e, h);
        
    }
    else{
        if(e.station!=a->elmt.station){
            if(e.station != a->elmt.doublon && a->elmt.doublon != 0 ){
                a->elmt.doublon2=e.station;
            }
            else a->elmt.doublon=e.station;
        }
        *h=0;
        return a;
    }
    if (*h != 0){
        a->equilibre = a->equilibre + *h;
        a=equilibrerAVL_h(a);
        if (a->equilibre== 0){
            *h = 0;
        }
        else *h = 1;
    }
    
    return a;
    }
