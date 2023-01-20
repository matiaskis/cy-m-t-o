#include "avl2.h"
#include "avl1.h"

void traiter2(Data2 e,FILE* out) {
    long h,d,m,y;
    h=((e.date2%100));
    d=((e.date2%10000)-e.date2%100)/100;
    m=((e.date2%1000000)-e.date2%10000)/10000;
    y=((e.date2)-e.date2%1000000)/1000000;
    fprintf(out,"%ld/%ld/%ld %ld:00:00 ",d,m,y,h);
    fprintf(out,"%f\n",e.associated_Data2);
}

void parcoursInfixe2(PAVL2 a, FILE* out) {
if (a!=NULL) {
    parcoursInfixe2(a->fg,out);
    traiter2(a->elmt,out);
    free(a);
    parcoursInfixe2(a->fd,out);
}
}

void parcoursInfixeR2(PAVL2 a, FILE* out) {
if (a!=NULL) {
    parcoursInfixeR2(a->fd,out); 
    traiter2(a->elmt,out);
    parcoursInfixeR2(a->fg,out);
}
}



PAVL2 creerArbre2(Data2 e){
    PAVL2 noeud ;
    noeud=malloc(sizeof(AVL2));
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

PAVL2 rotationGauche2(PAVL2 a){
    PAVL2 pivot; 
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

    PAVL2 rotationDroite2(PAVL2 a){
    PAVL2 pivot ;
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

PAVL2 doubleRotationGauche2(PAVL2 a){
    a->fd = rotationDroite2(a->fd);
     return rotationGauche2(a);
}

PAVL2 doubleRotationDroite2(PAVL2 a){
    a->fg = rotationGauche2(a->fg);
     return rotationDroite2(a);
}

PAVL2 equilibrerAVL2(PAVL2 a){

    if (a->equilibre >=  2){
        if (a->fd->equilibre >= 0){
            return rotationGauche2(a);
        }

        else return doubleRotationGauche2(a);
    }
    else if (a->equilibre  <=  -2){ 
        if (a->fg->equilibre <= 0){
            return rotationDroite2(a);
        }

    

        else return doubleRotationDroite2(a);
    }
    return a;
}

 


    
PAVL2 insertionAVLAverage2(PAVL2 a,Data2 e, int* h){

    if (a== NULL){
        *h=1;
        return creerArbre2(e);
    }
    else if (e.date2 < a->elmt.date2){
    a->fg=insertionAVLAverage2(a->fg, e, h);
        *h =-*h; 
    }
    else if(e.date2 > a->elmt.date2){
        a->fd=insertionAVLAverage2(a->fd, e, h);
        
    }
    else{
        a->elmt.associated_Data2=a->elmt.associated_Data2+e.associated_Data2;
        a->elmt.average_increment=a->elmt.average_increment+1;
        *h=0;
        return a;
    }
    if (*h != 0){
        a->equilibre = a->equilibre + *h;
        a=equilibrerAVL2(a);
        if (a->equilibre== 0){
            *h = 0;
        }
        else *h = 1;
    }
    
    return a;
    }
 
void calculateAverage2(PAVL2 a){
    if (a!=NULL) {
    calculateAverage2(a->fg);
    a->elmt.associated_Data2=a->elmt.associated_Data2/a->elmt.average_increment;
    calculateAverage2(a->fd);
    }
}



