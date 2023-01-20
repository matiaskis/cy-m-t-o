#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct data{
    int station;
    float associated_data;
    long date;
}Data;

typedef struct avl{
    Data elmt;
    struct avl * secondTree;
    struct avl * fg;
    struct avl * fd;
    int equilibre;
}AVL;


typedef AVL* PAVL;

void Traiter(Data e,FILE* out){
    long h,d,m,y;
    h=((e.date%100));
    d=((e.date%10000)-e.date%100)/100;
    m=((e.date%1000000)-e.date%10000)/10000;
    y=((e.date)-e.date%1000000)/1000000;
    fprintf(out,"%ld/%ld/%ld %ld:00:00 ",d,m,y,h);
    fprintf(out,"%d ",e.station);
    fprintf(out,"%f\n",e.associated_data);    
}

void sousParcoursInfixe(PAVL a,FILE * out){
    if (a!=NULL) {
        sousParcoursInfixe(a->fg,out);
        Traiter(a->elmt,out);
        free(a);
        sousParcoursInfixe(a->fd,out);
}
}

void parcoursInfixe(PAVL a, FILE* out) {
if (a!=NULL) {
    parcoursInfixe(a->fg,out);
    sousParcoursInfixe(a->secondTree,out);
    parcoursInfixe(a->fd,out);
}
}

void sousParcoursInfixeR(PAVL a,FILE * out){
    if (a!=NULL) {
        sousParcoursInfixeR(a->fd,out);
        Traiter(a->elmt,out);
        free(a);
        sousParcoursInfixeR(a->fg,out);
}
}

void parcoursInfixeR(PAVL a, FILE* out) {
if (a!=NULL) {
    parcoursInfixeR(a->fd,out); 
    sousParcoursInfixeR(a->secondTree,out);
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
    return noeud;
}

PAVL creerArbreAVL(Data e){
    PAVL noeud ;
    noeud=malloc(sizeof(AVL));
    if(noeud==NULL){
        exit(1);
    }
    noeud->elmt=e;
    noeud->fg= NULL;
    noeud->fd= NULL;
    noeud->secondTree=creerArbre(e);
    noeud->equilibre= 0;
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

PAVL insertionAVLSecondTree(PAVL a,Data e, int* h){

    if (a== NULL){
        *h=1;
        return creerArbre(e);
    }
    else if (e.station < a->elmt.station){
    a->fg=insertionAVLSecondTree(a->fg, e, h);
        *h =-*h; 
    }
    else if(e.station > a->elmt.station){
        a->fd=insertionAVLSecondTree(a->fd, e, h);
        
    }
    else{
    
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

PAVL insertionAVLDate(PAVL a,Data e, int* h,int * g){

    if (a== NULL){
        *h=1;
        return creerArbreAVL(e);
    }
    else if (e.date < a->elmt.date){
        a->fg=insertionAVLDate(a->fg, e, h,g);
        *h =-*h; 

    }
    else if(e.date > a->elmt.date){
        a->fd=insertionAVLDate(a->fd, e, h,g);
    }
    else{
        a->secondTree=insertionAVLSecondTree(a->secondTree,e,g);
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
    
int main(int argc, char* argv[]){
    PAVL a;
    int h;
    int g;
    int station;
    float associated_data;
    long date;
    Data data;
    int display_option=atoi(argv[3]);

    FILE* data_file=fopen(argv[1],"r+");
    FILE* output_file=fopen(argv[2],"w");


        while (fscanf(data_file,"%ld,",&date) == 1){
            fscanf(data_file,"%d,",&station);
            fscanf(data_file,"%f",&associated_data);
            data.date=date;
            data.station=station;
            data.associated_data=associated_data;
            a=insertionAVLDate(a,data,&h,&g);
        }

    if(display_option==1){
        parcoursInfixe(a,output_file);
    }
    else parcoursInfixeR(a,output_file);
    fclose(data_file);
    fclose(output_file);
    return 0;
}
