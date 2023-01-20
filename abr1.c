#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct data{
    int station;
    float associated_data;
    int average_increment;
}Data;

typedef struct abr{
    Data elmt;
    struct abr * fg;
    struct abr * fd;
    int equilibre;
}ABR;

typedef ABR* PABR;

void traiter(Data e,FILE* out) {
    fprintf(out,"%d ",e.station);
    fprintf(out,"%f\n",e.associated_data);
}

void parcoursInfixe(PABR a, FILE* out) {
if (a!=NULL) {
    parcoursInfixe(a->fg,out);
    traiter(a->elmt,out);
    free(a);
    parcoursInfixe(a->fd,out);
}
}

void parcoursInfixeR(PABR a, FILE* out) {
if (a!=NULL) {
    parcoursInfixeR(a->fd,out); 
    traiter(a->elmt,out);
    free(a);
    parcoursInfixeR(a->fg,out);
}
}



PABR creerArbre(Data e){
    PABR noeud ;
    noeud=malloc(sizeof(ABR));
    if(noeud==NULL){
        exit(1);
    }
    noeud->elmt=e;
    noeud->fg= NULL;
    noeud->fd= NULL;
    noeud->elmt.average_increment=1;
    return noeud;
}



 

PABR insertionABRMax(PABR a,Data e){

    if (a== NULL){
        return creerArbre(e);
    }
    else if (e.station < a->elmt.station){
    a->fg=insertionABRMax(a->fg, e);

    }
    else if(e.station > a->elmt.station){
        a->fd=insertionABRMax(a->fd, e);
        
    }
    else{
        if(e.associated_data > a->elmt.associated_data){
            a->elmt=e;
        }
    
    }
    return a;
    }

PABR insertionABRMin(PABR a,Data e){

    if (a== NULL){

        return creerArbre(e);
    }
    else if (e.station < a->elmt.station){
    a->fg=insertionABRMin(a->fg, e);

    }
    else if(e.station > a->elmt.station){
        a->fd=insertionABRMin(a->fd, e);
        
    }
    else{
        if(e.associated_data < a->elmt.associated_data){
            a->elmt=e;
        }
     
       
    }
  
    
    return a;
    }
    
PABR insertionABRAverage(PABR a,Data e){

    if (a== NULL){
        return creerArbre(e);
    }
    else if (e.station < a->elmt.station){
        a->fg=insertionABRAverage(a->fg, e);
    }
    else if(e.station > a->elmt.station){
        a->fd=insertionABRAverage(a->fd, e);
        
    }
    else{
        a->elmt.associated_data=a->elmt.associated_data+e.associated_data;
        a->elmt.average_increment=a->elmt.average_increment+1;
    }
    return a;
    }
 
void calculateAverage(PABR a){
    if (a!=NULL) {
    calculateAverage(a->fg);
    a->elmt.associated_data=a->elmt.associated_data/a->elmt.average_increment;
    calculateAverage(a->fd);
    }
}



int main(int argc, char* argv[]){
    PABR a;
    int station;
    float associated_data;
    Data data;

    int sort_option=atoi(argv[3]);
    int display_option=atoi(argv[4]);

    FILE* data_file=fopen(argv[1],"r+");
    FILE* output_file=fopen(argv[2],"w");

    if(sort_option==1){
        while (fscanf(data_file,"%d;",&station) == 1){
            fscanf(data_file,"%f",&associated_data);
            data.station=station;
            data.associated_data=associated_data;
            a=insertionABRMax(a,data);
        }
    }
    else if(sort_option==2){
        while (fscanf(data_file,"%d;",&station) == 1){
            fscanf(data_file,"%f",&associated_data);
            data.station=station;
            data.associated_data=associated_data;
            a=insertionABRMin(a,data);
        }
    }
    else if(sort_option==3){
        while (fscanf(data_file,"%d;",&station) == 1){
            fscanf(data_file,"%f",&associated_data);
            data.station=station;
            data.associated_data=associated_data;
            a=insertionABRAverage(a,data);
        }
        calculateAverage(a);
    }
    if(display_option==1){
        parcoursInfixe(a,output_file);
    }
    else parcoursInfixeR(a,output_file);
    fclose(data_file);
    fclose(output_file);
    return 0;
}
