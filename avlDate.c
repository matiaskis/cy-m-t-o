#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

typedef struct avl{
    Data elmt;
    struct avl * fg;
    struct avl * fd;
    int equilibre;
}AVL;

typedef struct data{
    char date[100];
    time_t timestamp;
    int average_increment;
}Data;

typedef AVL* PAVL;

void traiter(Data e,FILE* out, struct tm date) {
    int i;
    fprintf(outputfile,"0%d/0%d/%d %d:00 ",myDate.tm_mday,myDate.tm_mon,myDate.tm_year+1900,myDate.tm_hour);
    i=26;
    while(date[i]!=0){
    fprintf(outputfile,"%c",date[i]);
    i++;
    }
}

void parcoursInfixe(PAVL a, FILE* out) {
if (a!=NULL) {
    parcoursInfixe(a->fg,out);
    traiter(a->elmt,out);
    parcoursInfixe(a->fd,out);
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
    else if (e.timestamp < a->elmt.timestamp){
    a->fg=insertionAVLAverage(a->fg, e, h);
        *h =-*h; 
    }
    else if(e.timestamp > a->elmt.timestamp){
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
    char date[100];
    float associated_data;
    struct tm myDate;
    time_t timestamp;

    FILE* data_file=fopen(argv[1],"r+");
    FILE* output_file=fopen(argv[2],"w");

    while(fgets(date,100,inputfile)!=NULL){
   
  
    
        myDate.tm_mday = (atoi(&date[8])); 
        myDate.tm_mon =(atoi(&date[5]));  
        myDate.tm_year =110+atoi(&date[3]);   
        myDate.tm_hour = (atoi(&date[11]))+atoi(&date[21])-1;    
        timestamp = mktime( & myDate );
        data.timestamp=timestamp;
        a=insertionAVLAverage(a,data,&h,myDate);
    }
    parcoursInfixe(a);
    fclose(data_file);
    fclose(output_file);
    return 0;
}
