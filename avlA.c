#include "avl1.h"
#include "avlA.h"

void traiterA(DataA1 e,FILE* out) {
    fprintf(out,"%d ",e.station);
    fprintf(out,"%f\n",e.associated_DataA1);
    fprintf(out,"%f\n",e.associated_DataA2);
}

void parcoursInfixeA(PAVLAA a, FILE* out) {
if (a!=NULL) {
    parcoursInfixeA(a->fg,out);
    traiterA(a->elmt,out);
    free(a);
    parcoursInfixeA(a->fd,out);
}
}

void parcoursInfixeRA(PAVLAA a, FILE* out) {
if (a!=NULL) {
    parcoursInfixeRA(a->fd,out); 
    traiterA(a->elmt,out);
    free(a);
    parcoursInfixeRA(a->fg,out);
}
}

PAVLAA creerArbreA(DataA1 e){
    PAVLAA noeud ;
    noeud=malloc(sizeof(AVLAA));
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

PAVLAA rotationGaucheA(PAVLAA a){
    PAVLAA pivot; 
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

    PAVLAA rotationDroiteA(PAVLAA a){
    PAVLAA pivot ;
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

PAVLAA doubleRotationGaucheA(PAVLAA a){
    a->fd = rotationDroiteA(a->fd);
     return rotationGaucheA(a);
}

PAVLAA doubleRotationDroiteA(PAVLAA a){
    a->fg = rotationGaucheA(a->fg);
     return rotationDroiteA(a);
}

PAVLAA equilibrerAVLAA(PAVLAA a){

    if (a->equilibre >=  2){
        if (a->fd->equilibre >= 0){
            return rotationGaucheA(a);
        }

        else return doubleRotationGaucheA(a);
    }
    else if (a->equilibre  <=  -2){ 
        if (a->fg->equilibre <= 0){
            return rotationDroiteA(a);
        }

    

        else return doubleRotationDroiteA(a);
    }
    return a;
}

    
PAVLAA insertionAVLAAAverage(PAVLAA a,DataA1 e, int* h){

    if (a== NULL){
        *h=1;
        return creerArbreA(e);
    }
    else if (e.station < a->elmt.station){
    a->fg=insertionAVLAAAverage(a->fg, e, h);
        *h =-*h; 
    }
    else if(e.station > a->elmt.station){
        a->fd=insertionAVLAAAverage(a->fd, e, h);
        
    }
    else{
        a->elmt.associated_DataA1=a->elmt.associated_DataA1+e.associated_DataA1;
        a->elmt.associated_DataA2=a->elmt.associated_DataA2+e.associated_DataA2;
        a->elmt.average_increment=a->elmt.average_increment+1;
        *h=0;
        return a;
    }
    if (*h != 0){
        a->equilibre = a->equilibre + *h;
        a=equilibrerAVLAA(a);
        if (a->equilibre== 0){
            *h = 0;
        }
        else *h = 1;
    }
    
    return a;
    }
 
void calculateAverageA(PAVLAA a){
    if (a!=NULL) {
    calculateAverageA(a->fg);
    a->elmt.associated_DataA1=a->elmt.associated_DataA1/a->elmt.average_increment;
    a->elmt.associated_DataA2=a->elmt.associated_DataA2/a->elmt.average_increment;
    calculateAverageA(a->fd);
    }
}
