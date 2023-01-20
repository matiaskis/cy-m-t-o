#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct data{
    long date;
    float associated_data;
    int average_increment;
}Data;

typedef struct avl{
    Data elmt;
    struct avl * fg;
    struct avl * fd;
    int equilibre;
}AVL;

typedef AVL* PAVL;

void traiter(Data e,FILE* out) {
    long h,d,m,y;
    h=((e.date%100));
    d=((e.date%10000)-e.date%100)/100;
    m=((e.date%1000000)-e.date%10000)/10000;
    y=((e.date)-e.date%1000000)/1000000;
    fprintf(out,"%ld/%ld/%ld %ld:00:00 ",d,m,y,h);
    fprintf(out,"%f\n",e.associated_data);
}

void parcoursInfixe(PAVL a, FILE* out) {
if (a!=NULL) {
    parcoursInfixe(a->fg,out);
    traiter(a->elmt,out);
    free(a);
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

 


    
PAVL insertionAVLAverage(PAVL a,Data e, int* h){

    if (a== NULL){
        *h=1;
        return creerArbre(e);
    }
    else if (e.date < a->elmt.date){
    a->fg=insertionAVLAverage(a->fg, e, h);
        *h =-*h; 
    }
    else if(e.date > a->elmt.date){
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
    PAVL a;
    int h;
    long date;
    float associated_data;
    Data data;

    int display_option=atoi(argv[3]);

    FILE* data_file=fopen(argv[1],"r+");
    FILE* output_file=fopen(argv[2],"w");


    while (fscanf(data_file,"%ld,",&date) == 1){
            fscanf(data_file,"%f",&associated_data);
            data.date=date;
            data.associated_data=associated_data;
            a=insertionAVLAverage(a,data,&h);
        }

    if(display_option==1){
        parcoursInfixe(a,output_file);
    }
    else parcoursInfixeR(a,output_file);
    fclose(data_file);
    fclose(output_file);
    return 0;
}
