#include "avl1.h"

void traiter(Data1 e,FILE* out) {
    fprintf(out,"%d ",e.station);
    fprintf(out,"%f\n",e.associated_Data1);
}

void parcoursInfixe(PAVL1 a, FILE* out) {
if (a!=NULL) {
    parcoursInfixe(a->fg,out);
    traiter(a->elmt,out);
    free(a);
    parcoursInfixe(a->fd,out);
}
}

void parcoursInfixeR(PAVL1 a, FILE* out) {
if (a!=NULL) {
    parcoursInfixeR(a->fd,out); 
    traiter(a->elmt,out);
    free(a);
    parcoursInfixeR(a->fg,out);
}
}

int max(int a, int b) {
    return(a<b ? b : a);
}

int min(int a, int b) {
    return(a < b ? a : b);
}

PAVL1 creerArbre(Data1 e){
    PAVL1 noeud ;
    noeud=malloc(sizeof(AVL1));
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

PAVL1 rotationGauche(PAVL1 a){
    PAVL1 pivot; 
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

    PAVL1 rotationDroite(PAVL1 a){
    PAVL1 pivot ;
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

PAVL1 doubleRotationGauche(PAVL1 a){
    a->fd = rotationDroite(a->fd);
     return rotationGauche(a);
}

PAVL1 doubleRotationDroite(PAVL1 a){
    a->fg = rotationGauche(a->fg);
     return rotationDroite(a);
}

PAVL1 equilibrerAVL1(PAVL1 a){

    if (a->equilibre >=  2){
        if (a->fd->equilibre >= 0){
            return rotationGauche(a);
        }

        else return doubleRotationGauche(a);
    }
    else if (a->equilibre  <=  -2){ 
        if (a->fg->equilibre <= 0){
            return rotationDroite(a);
        }

    

        else return doubleRotationDroite(a);
    }
    return a;
}

 

PAVL1 insertionAVL1Max(PAVL1 a,Data1 e, int* h){

    if (a== NULL){
        *h=1;
        return creerArbre(e);
    }
    else if (e.station < a->elmt.station){
    a->fg=insertionAVL1Max(a->fg, e, h);
        *h =-*h; 
    }
    else if(e.station > a->elmt.station){
        a->fd=insertionAVL1Max(a->fd, e, h);
        
    }
    else{
        if(e.associated_Data1 > a->elmt.associated_Data1){
            a->elmt=e;
        }
        *h=0;
        return a;
    }
    if (*h != 0){
        a->equilibre = a->equilibre + *h;
        a=equilibrerAVL1(a);
        if (a->equilibre== 0){
            *h = 0;
        }
        else *h = 1;
    }
    
    return a;
    }

PAVL1 insertionAVL1Min(PAVL1 a,Data1 e, int* h){

    if (a== NULL){
        *h=1;
        return creerArbre(e);
    }
    else if (e.station < a->elmt.station){
    a->fg=insertionAVL1Min(a->fg, e, h);
        *h =-*h; 
    }
    else if(e.station > a->elmt.station){
        a->fd=insertionAVL1Min(a->fd, e, h);
        
    }
    else{
        if(e.associated_Data1 < a->elmt.associated_Data1){
            a->elmt=e;
        }
        *h=0;
        return a;
    }
    if (*h != 0){
        a->equilibre = a->equilibre + *h;
        a=equilibrerAVL1(a);
        if (a->equilibre== 0){
            *h = 0;
        }
        else *h = 1;
    }
    
    return a;
    }
    
PAVL1 insertionAVL1Average(PAVL1 a,Data1 e, int* h){

    if (a== NULL){
        *h=1;
        return creerArbre(e);
    }
    else if (e.station < a->elmt.station){
    a->fg=insertionAVL1Average(a->fg, e, h);
        *h =-*h; 
    }
    else if(e.station > a->elmt.station){
        a->fd=insertionAVL1Average(a->fd, e, h);
        
    }
    else{
        a->elmt.associated_Data1=a->elmt.associated_Data1+e.associated_Data1;
        a->elmt.average_increment=a->elmt.average_increment+1;
        *h=0;
        return a;
    }
    if (*h != 0){
        a->equilibre = a->equilibre + *h;
        a=equilibrerAVL1(a);
        if (a->equilibre== 0){
            *h = 0;
        }
        else *h = 1;
    }
    
    return a;
    }
 
void calculateAverage(PAVL1 a){
    if (a!=NULL) {
    calculateAverage(a->fg);
    a->elmt.associated_Data1=a->elmt.associated_Data1/a->elmt.average_increment;
    calculateAverage(a->fd);
    }
}
