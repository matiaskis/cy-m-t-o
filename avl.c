#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>
#include <string.h>

 typedef struct data{
    int station;
    float associated_data;
    float average_increment;
 }Data;

typedef struct avl{
    Data elmt;
    struct avl * fg;
    struct avl * fd;
    int equilibre;
}AVL;

typedef struct davl{
    struct avl * elmt;
    struct avl * fg;
    struct avl * fd;
    int equilibre;
}DAVL;

typedef AVL* PAVL;
typedef DAVL* PDAVL;

void traiter(Data e) {
    printf("%d ",e.station);
    printf("%f ", e.associated_data);
}

 

void parcoursInfixe(PAVL a) {
if (a!=NULL) {
    parcoursInfixe(a->fg);
    traiter(a->elmt);
    parcoursInfixe(a->fd);
}
}


 


bool existeFilsDroit(PAVL a) {
    return(a->fd ? true : false);
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
        if(e.associated_data > a->elmt.associated_data){
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
        if(e.associated_data < a->elmt.associated_data){
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
        a->elmt.associated_data=a->elmt.associated_data+e.associated_data;
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
 
void calculateAverage(PAVL a){
    if (a!=NULL) {
    calculateAverage(a->fg);
    a->elmt.associated_data=a->elmt.associated_data/a->elmt.average_increment;
    calculateAverage(a->fd);
    }
}

int main(int argc, char* argv[]){
    PAVL a,b;
    int h;
    int station;
    float associated_data;
    int date;
    Data data;
    int argument=atoi(argv[2]);
    FILE* data_file=fopen(argv[1],"r+");
    if(argument==1){
        while (fscanf(data_file,"%d",&station) == 1){
            fscanf(data_file,"%f",&associated_data);
            data.station=station;
            data.associated_data=associated_data;
            a=insertionAVLMax(a,data,&h);
        }
    }
    else if(argument==2){
        while (fscanf(data_file,"%d",&station) == 1){
            fscanf(data_file,"%f",&associated_data);
            data.station=station;
            data.associated_data=associated_data;
            a=insertionAVLMin(a,data,&h);
        };
    }
    else if(argument==3){
        while (fscanf(data_file,"%d",&station) == 1){
            fscanf(data_file,"%f",&associated_data);
            data.station=station;
            data.associated_data=associated_data;
            a=insertionAVLAverage(a,data,&h);
        };
        calculateAverage(a);
    }
    else if(argument==4){
        while (fscanf(data_file,"%d",&date) == 1){
            fscanf(data_file,"%d",&station);
            fscanf(data_file,"%f",&associated_data);
            data.station=station;
            data.associated_data=associated_data;
            a=insertionAVLAverage(a,data,&h);
    }
    }
    parcoursInfixe(a);
    return 0;
}
