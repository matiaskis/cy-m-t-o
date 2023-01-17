#include<stdio.h>
#include<stdlib.h>
#include "avl.h"

int main(int argc, char* argv[]){
    PAVL a;
    int h;
    int station;
    float associated_data;
    Data data;

    int sort_option=atoi(argv[3]);
    int display_option=atoi(argv[4]);

    FILE* data_file=fopen(argv[1],"r+");
    FILE* output_file=fopen(argv[2],"w");

    if(sort_option==1){
        while (fscanf(data_file,"%d,",&station) == 1){
            fscanf(data_file,"%f",&associated_data);
            data.station=station;
            data.associated_data=associated_data;
            a=insertionAVLMax(a,data,&h);
        }
    }
    else if(sort_option==2){
        while (fscanf(data_file,"%d,",&station) == 1){
            fscanf(data_file,"%f",&associated_data);
            data.station=station;
            data.associated_data=associated_data;
            a=insertionAVLMin(a,data,&h);
        }
    }
    else if(sort_option==3){
        while (fscanf(data_file,"%d,",&station) == 1){
            fscanf(data_file,"%f",&associated_data);
            data.station=station;
            data.associated_data=associated_data;
            a=insertionAVLAverage(a,data,&h);
        }
        calculateAverage(a);
    }
    else if(sort_option==4){
        while(fscanf(data_file,"%d,",&station)==1){
            fscanf(data_file,"%f",&associated_data);
            data.station=station;
            data.associated_data=associated_data;
            a=insertionAVLHeight(a,data,&h);
        }
    }
    
    if(display_option==1){
        parcoursInfixe(a,output_file);
    }
    else parcoursInfixeR(a,output_file);
    fclose(data_file);
    fclose(output_file);
    return 0;
}
