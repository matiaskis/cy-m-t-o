#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "avl1.h"
#include "avlh.h"
#include "avl2.h"
#include "avl3.h"
#include "avlM.h"
#include "avlA.h"

int main(int argc, char* argv[]){
    
    int h;
    int station; // tous sauf avl2
    float associated_data,associated_data2; // tous
    int height, moisture; //avl1
    long date; //avl2 et 3
    int g;//avl3

    PAVL1 a1;
    PAVL_H ah;
    Data1 data1;
    Data2 data2;
    Data3 data3;
    PAVL2 a2;
    PAVL3 a3;
    Data_h data_h;
    PAVL_m am;
    Data_m data_m;
    PAVLAA aa;
    DataA1 dataA1;
    

    int sort_option=atoi(argv[3]);
    int sort_option2;

    int display_option=atoi(argv[4]);

    FILE* data_file=fopen(argv[1],"r+");
    FILE* output_file=fopen(argv[2],"w");

    if(sort_option==1){

        while (fscanf(data_file,"%d;",&station) == 1){
            fscanf(data_file,"%f",&associated_data);
            data1.station=station;
            data1.associated_Data1=associated_data; 
            a1=insertionAVL1Max(a1,data1,&h);
        }
        if(display_option==1){
        parcoursInfixe(a1,output_file);
        }
        else parcoursInfixeR(a1,output_file);
    }
    else if(sort_option==2){
  
        while (fscanf(data_file,"%d;",&station) == 1){
            fscanf(data_file,"%f",&associated_data);
            data1.station=station;
            data1.associated_Data1=associated_data;
            a1=insertionAVL1Min(a1,data1,&h);
        }
        if(display_option==1){
        parcoursInfixe(a1,output_file);
        }
        else parcoursInfixeR(a1,output_file);
        }
    else if(sort_option==3){

        while (fscanf(data_file,"%d;",&station) == 1){
            fscanf(data_file,"%f",&associated_data);
            data1.station=station;
            data1.associated_Data1=associated_data;
            a1=insertionAVL1Average(a1,data1,&h);
        }
        calculateAverage(a1);
        if(display_option==1){
        parcoursInfixe(a1,output_file);
        }
        else parcoursInfixeR(a1,output_file);
    }
    else if(sort_option==4){

        while(fscanf(data_file,"%d;",&station)==1){
            fscanf(data_file,"%d",&height);
            data_h.station=station;
            data_h.height=height;
            ah=insertionAVLHHeight(ah,data_h,&h);
        }
        if(display_option==1){
        parcoursInfixe_h(ah,output_file);
        }
        else parcoursInfixeR_h(ah,output_file);
    }
    else if(sort_option==5){

         while (fscanf(data_file,"%ld;",&date) == 1){
            fscanf(data_file,"%f",&associated_data);
            data2.date2=date;
            data2.associated_Data2=associated_data;
            a2=insertionAVLAverage2(a2,data2,&h);
        }

        if(display_option==1){
            parcoursInfixe2(a2,output_file);
        }
        else parcoursInfixeR2(a2,output_file);
    }
    else if(sort_option==6){
         while (fscanf(data_file,"%d;",&station) == 1){
            fscanf(data_file,"%ld;",&date);
            fscanf(data_file,"%f",&associated_data);
            data3.date3=date;
            data3.station=station;
            data3.associated_Data3=associated_data;
            a3=insertionAVL3date(a3,data3,&h,&g);
        }

        if(display_option==1){
            parcoursInfixe3(a3,output_file);
        }
        else parcoursInfixeR3(a3,output_file);
    }
    else if(sort_option==7){
        sort_option2=atoi(argv[5]);

        if(sort_option2 == 1){
            while (fscanf(data_file,"%d;",&station) == 1){
                fscanf(data_file,"%d",&moisture);
                data_m.station=station;
                data_m.moisture=moisture;
                am=insertionAVLMMax(am,data_m,&h);
            }
            if(display_option==1){
                parcoursInfixe_m2(am,output_file);
            }
            else parcoursInfixeR_m2(am,output_file);
        }
        else{
            while (fscanf(data_file,"%d;",&station) == 1){
                fscanf(data_file,"%d",&moisture);
                data_m.station=station;
                data_m.moisture=moisture;
                am=insertionAVLM(am,data_m,&h);

            }
            if(display_option==1){
                parcoursInfixe_m(am,output_file);
            }
            else parcoursInfixeR_m(am,output_file);
        }

        
       
    }
    else if(sort_option==8){
        while (fscanf(data_file,"%d;",&station) == 1){
            fscanf(data_file,"%f",&associated_data);
            fscanf(data_file,"%f",&associated_data2);
            dataA1.station=station;
            dataA1.associated_DataA1=associated_data;
            dataA1.associated_DataA2=associated_data2;
            aa=insertionAVLAAAverage(aa,dataA1,&h);
        }
        if(display_option==1){
            parcoursInfixeA(aa,output_file);
        }
        else parcoursInfixeRA(aa,output_file);
    }  

    fclose(data_file);
    fclose(output_file);
    return 0;
}
