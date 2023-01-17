#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct data{
    int station;
    int height;
    float latitude;
    float longitude;
    int doublon;
}Data;

typedef struct avl{
    Data elmt;
    struct avl * fg;
    struct avl * fd;
    int equilibre;
}AVL;


typedef AVL* PAVL;


void traiter(Data e,FILE* out) {
    fprintf(out,"%d ",e.station);
    fprintf(out,"%d ",e.height);
    fprintf(out,"%f ",e.latitude);
    fprintf(out,"%f\n",e.longitude);
    if(e.doublon!=0){
        fprintf(out,"%d",e.doublon);
        fprintf(out,"%f ",e.height);
        fprintf(out,"%f ",e.latitude);
        fprintf(out,"%f\n",e.longitude);
    }
}

 

void parcoursInfixe(PAVL a, FILE* out) {
if (a!=NULL) {
    parcoursInfixe(a->fg,out);
    traiter(a->elmt,out);
    parcoursInfixe(a->fd,out);
}
}

void parcoursInfixeR(PAVL a, FILE* out) {
if (a!=NULL) {
    parcoursInfixeR(a->fd,out); 
    traiter(a->elmt,out);
    parcoursInfixeR(a->fg,out);
}
}

int max(int a, int b) {
    return(a<b ? b : a);
}

int min(int a, int b) {
    return(a < b ? a : b);
}


PAVL creerArbre(Data e){
    PAVL noeud ;
    noeud=malloc(sizeof(AVL));
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


PAVL rotationGauche(PAVL a){

 

    PAVL pivot; 
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

 

    PAVL rotationDroite(PAVL a){

 

    PAVL pivot ;
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

 

PAVL doubleRotationGauche(PAVL a){

 

    a->fd = rotationDroite(a->fd);
     return rotationGauche(a);
}

 

PAVL doubleRotationDroite(PAVL a){
    a->fg = rotationGauche(a->fg);
     return rotationDroite(a);
}

 

PAVL equilibrerAVL(PAVL a){

 

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

 

PAVL insertionAVLMax(PAVL a,Data e, int* h){

    if (a== NULL){
        *h=1;
        return creerArbre(e);
    }
    else if (e.station < a->elmt.station){
    a->fg=insertionAVLMax(a->fg, e, h);
        *h =-*h; 
    }
    else if(e.station > a->elmt.station){
        a->fd=insertionAVLMax(a->fd, e, h);
        
    }
    else{
        if(e.height > a->elmt.height){
            a->elmt=e;
        }
        *h=0;
        return a;
    }
    if (*h != 0){
        a->equilibre = a->equilibre + *h;
        a=equilibrerAVL(a);
        if (a->equilibre== 0){
            *h = 0;
        }
        else *h = 1;
    }
    
    return a;
    }

PAVL insertionAVLMin(PAVL a,Data e, int* h){

    if (a== NULL){
        *h=1;
        return creerArbre(e);
    }
    else if (e.station < a->elmt.station){
    a->fg=insertionAVLMin(a->fg, e, h);
        *h =-*h; 
    }
    else if(e.station > a->elmt.station){
        a->fd=insertionAVLMin(a->fd, e, h);
        
    }
    else{
        if(e.height < a->elmt.height){
            a->elmt=e;
        }
        *h=0;
        return a;
    }
    if (*h != 0){
        a->equilibre = a->equilibre + *h;
        a=equilibrerAVL(a);
        if (a->equilibre== 0){
            *h = 0;
        }
        else *h = 1;
    }
    
    return a;
    }
    
PAVL insertionAVLAverage(PAVL a,Data e, int* h){

    if (a== NULL){
        *h=1;
        return creerArbre(e);
    }
    else if (e.station < a->elmt.station){
    a->fg=insertionAVLAverage(a->fg, e, h);
        *h =-*h; 
    }
    else if(e.station > a->elmt.station){
        a->fd=insertionAVLAverage(a->fd, e, h);
        
    }
    else{
        a->elmt.height=a->elmt.height+e.height;
        a->elmt.average_increment=a->elmt.average_increment+1;
        *h=0;
        return a;
    }
    if (*h != 0){
        a->equilibre = a->equilibre + *h;
        a=equilibrerAVL(a);
        if (a->equilibre== 0){
            *h = 0;
        }
        else *h = 1;
    }
    
    return a;
    }
 

PAVL insertionAVLHeight(PAVL a,Data e, int* h){

    if (a== NULL){
        *h=1;
        return creerArbre(e);
    }
    else if (e.height < a->elmt.height){
    a->fg=insertionAVLHeight(a->fg, e, h);
        *h =-*h; 
    }
    else if(e.height > a->elmt.height){
        a->fd=insertionAVLHeight(a->fd, e, h);
        
    }
    else{
        if(e.station!=a->elmt.station){
            a->elmt.doublon=e.station;
        }
        *h=0;
        return a;
    }
    if (*h != 0){
        a->equilibre = a->equilibre + *h;
        a=equilibrerAVL(a);
        if (a->equilibre== 0){
            *h = 0;
        }
        else *h = 1;
    }
    
    return a;
    }


