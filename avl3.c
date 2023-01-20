#include "avl3.h"
#include "avl1.h"

void Traiter3(Data3 e,FILE* out){
    long h,d,m,y;
    h=((e.date3%100));
    d=((e.date3%10000)-e.date3%100)/100;
    m=((e.date3%1000000)-e.date3%10000)/10000;
    y=((e.date3)-e.date3%1000000)/1000000;
    fprintf(out,"%ld/%ld/%ld %ld:00:00 ",d,m,y,h);
    fprintf(out,"%d ",e.station);
    fprintf(out,"%f\n",e.associated_Data3);    
}

void sousParcoursInfixe3(PAVL3 a,FILE * out){
    if (a!=NULL) {
        sousParcoursInfixe3(a->fg,out);
        Traiter3(a->elmt,out);
        free(a);
        sousParcoursInfixe3(a->fd,out);
}
}

void parcoursInfixe3(PAVL3 a, FILE* out) {
if (a!=NULL) {
    parcoursInfixe3(a->fg,out);
    sousParcoursInfixe3(a->secondTree,out);
    parcoursInfixe3(a->fd,out);
}
}

void sousParcoursInfixeR3(PAVL3 a,FILE * out){
    if (a!=NULL) {
        sousParcoursInfixeR3(a->fd,out);
        Traiter3(a->elmt,out);
        free(a);
        sousParcoursInfixeR3(a->fg,out);
}
}

void parcoursInfixeR3(PAVL3 a, FILE* out) {
if (a!=NULL) {
    parcoursInfixeR3(a->fd,out); 
    sousParcoursInfixeR3(a->secondTree,out);
    parcoursInfixeR3(a->fg,out);
}
}



PAVL3 creerArbre3(Data3 e){
    PAVL3 noeud ;
    noeud=malloc(sizeof(AVL3));
    if(noeud==NULL){
        exit(1);
    }
    noeud->elmt=e;
    noeud->fg= NULL;
    noeud->fd= NULL;
    noeud->equilibre= 0;
    return noeud;
}

PAVL3 creerArbreAVL3(Data3 e){
    PAVL3 noeud ;
    noeud=malloc(sizeof(AVL3));
    if(noeud==NULL){
        exit(1);
    }
    noeud->elmt=e;
    noeud->fg= NULL;
    noeud->fd= NULL;
    noeud->secondTree=creerArbre3(e);
    noeud->equilibre= 0;
    return noeud;
}

PAVL3 rotationGauche3(PAVL3 a){
    PAVL3 pivot; 
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

    PAVL3 rotationDroite3(PAVL3 a){
    PAVL3 pivot ;
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

PAVL3 doubleRotationGauche3(PAVL3 a){
    a->fd = rotationDroite3(a->fd);
     return rotationGauche3(a);
}

PAVL3 doubleRotationDroite3(PAVL3 a){
    a->fg = rotationGauche3(a->fg);
     return rotationDroite3(a);
}

PAVL3 equilibrerAVL3(PAVL3 a){

    if (a->equilibre >=  2){
        if (a->fd->equilibre >= 0){
            return rotationGauche3(a);
        }

        else return doubleRotationGauche3(a);
    }
    else if (a->equilibre  <=  -2){ 
        if (a->fg->equilibre <= 0){
            return rotationDroite3(a);
        }

    

        else return doubleRotationDroite3(a);
    }
    return a;
}

PAVL3 insertionAVL3SecondTree(PAVL3 a,Data3 e, int* h){

    if (a== NULL){
        *h=1;
        return creerArbre3(e);
    }
    else if (e.station < a->elmt.station){
    a->fg=insertionAVL3SecondTree(a->fg, e, h);
        *h =-*h; 
    }
    else if(e.station > a->elmt.station){
        a->fd=insertionAVL3SecondTree(a->fd, e, h);
        
    }
    else{
    
        *h=0;
        return a;
    }
    if (*h != 0){
        a->equilibre = a->equilibre + *h;
        a=equilibrerAVL3(a);
        if (a->equilibre== 0){
            *h = 0;
        }
        else *h = 1;
    }
    
    return a;
}

PAVL3 insertionAVL3date(PAVL3 a,Data3 e, int* h,int * g){

    if (a== NULL){
        *h=1;
        return creerArbreAVL3(e);
    }
    else if (e.date3 < a->elmt.date3){
        a->fg=insertionAVL3date(a->fg, e, h,g);
        *h =-*h; 

    }
    else if(e.date3 > a->elmt.date3){
        a->fd=insertionAVL3date(a->fd, e, h,g);
    }
    else{
        a->secondTree=insertionAVL3SecondTree(a->secondTree,e,g);
        *h=0;
        return a;
    }
    if (*h != 0){
        a->equilibre = a->equilibre + *h;
        a=equilibrerAVL3(a);
        if (a->equilibre== 0){
            *h = 0;
        }
        else *h = 1;
    }
    
    return a;
    }
    
