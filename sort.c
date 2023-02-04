#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "avl1.h"
#include "avlh.h"
#include "avl2.h"
#include "avl3.h"
#include "avlM.h"
#include "avlA.h"
#include "abr1.h"
#include "abrh.h"
#include "abr2.h"
#include "abr3.h"
#include "abrm.h"
#include "abrA.h"
#include "sort.h"
#include "tab1.h"
#include "tabh.h"
#include "tabw.h"
#include "tabm.h"


void sort_tab(int sort_option,int sort_option2,FILE* data_file,FILE* output_file){
    
    int station;
    float wind1,wind2;
    float latitude,longitude;
    float temp;
    int height;
    int moisture;

    //sort T1 P1
    if (sort_option == 1){                   
        Data_tab1 e;
        LinkedList * pList=NULL;
   
        while(fscanf(data_file,"%d;",&station) == 1 ){
            fscanf(data_file,"%f",&temp);
            e.station=station;
            e.temp_ave=temp;
            e.temp_max=temp;
            e.temp_min=temp;
            
            pList=insertionTab1(pList,e);
            
        }
        
        calculateAverageTab1(pList);
        treatList(pList,output_file);
    }
    //sort wind
    else if(sort_option==2){

        LinkedListw * pList=NULL;
        Data_tabw e;
        
    
        while(fscanf(data_file,"%d;",&station) == 1 ){
            fscanf(data_file,"%f;",&wind1);
            fscanf(data_file,"%f;",&wind2);
            fscanf(data_file,"%f,",&latitude);
            fscanf(data_file,"%f",&longitude);
            e.station=station;
            e.wind1_ave=wind1;
            e.wind2_ave=wind2;
            e.latitude=latitude;
            e.longitude=longitude;
            
            pList=insertionTabw(pList,e);
            
        }
        
        calculateAverageTabw(pList);
        treatListw(pList,output_file);
    }
    //sort height
    else if(sort_option==3){         
        Data_tabh e;
        LinkedListh * pList=NULL;
        
        while(fscanf(data_file,"%d;",&station) == 1 ){          
            fscanf(data_file,"%f,",&latitude);
            fscanf(data_file,"%f;",&longitude);
            fscanf(data_file,"%d",&height);

            e.station=station;
            e.height=height;
            e.latitude=latitude;
            e.longitude=longitude;
            
            pList=insertionTabh(pList,e);
            
        }
        
        
        treatListh(pList,output_file);
    }
    //sort moisture
    else{
        Data_tabm e;
        LinkedListm * pList=NULL;

        if(sort_option2==1){   
            while(fscanf(data_file,"%d;",&station) == 1 ){
                fscanf(data_file,"%d;",&moisture);
                fscanf(data_file,"%f,",&latitude);
                fscanf(data_file,"%f",&longitude);

                e.station=station;
                e.moisture=moisture;
                e.latitude=latitude;
                e.longitude=longitude;
                
                pList=insertionTabMAXm(pList,e);
            
            }
            
            
            treat_tabm2(pList,output_file);

        }
        else {
            while(fscanf(data_file,"%d;",&station) == 1 ){
                fscanf(data_file,"%d;",&moisture);
                fscanf(data_file,"%f,",&latitude);
                fscanf(data_file,"%f",&longitude);

                e.station=station;
                e.moisture=moisture;
                e.latitude=latitude;
                e.longitude=longitude;
                
                pList=insertionTabm(pList,e);
            
            }
            
            
            treat_tabm(pList,output_file);

        }


    }

}
void sort_abr(int sort_option,int display_option,int sort_option2,FILE* data_file,FILE* output_file){

    int station; 
    float associated_data,associated_data2; 
    int height, moisture; 
    long date; 
    float latitude, longitude;
    //sort P1 T1
    if(sort_option==1){
        PABR1 a1=NULL;
        Data1ABR data1;

        while (fscanf(data_file,"%d;",&station) == 1){
            fscanf(data_file,"%f",&associated_data);
            data1.station=station;
            data1.associated_data=associated_data; 
            a1=insertionMax_abr1(a1,data1);
        }
        if(display_option==1){
        infixPath_abr1(a1,output_file);
        }
        else infixPathR_abr1(a1,output_file);
    }

    //sort P1 T1
    else if(sort_option==2){
        PABR1 a1=NULL;
        Data1ABR data1;

        while (fscanf(data_file,"%d;",&station) == 1){
            fscanf(data_file,"%f",&associated_data);
            data1.station=station;
            data1.associated_data=associated_data;
            a1=insertionMin_abr1(a1,data1);
        }
        if(display_option==1){
            infixPath_abr1(a1,output_file);
        }
        else infixPathR_abr1(a1,output_file);
    }

     //sort P1 T1
    else if(sort_option==3){
        PABR1 a1=NULL;
        Data1ABR data1;

        while (fscanf(data_file,"%d;",&station) == 1){
            fscanf(data_file,"%f",&associated_data);
            data1.station=station;
            data1.associated_data=associated_data;
            a1=insertionAverage_abr1(a1,data1);
        }
        calculateAverage_abr1(a1);
        if(display_option==1){
            infixPath_abr1(a1,output_file);
        }
        else infixPathR_abr1(a1,output_file);
    }

    //sort height
    else if(sort_option==4){
        PABR_H ah=NULL;
        Data_abrh data_h;

        while(fscanf(data_file,"%d;",&station)==1){
            fscanf(data_file,"%f,",&latitude);
            fscanf(data_file,"%f;",&longitude);
            fscanf(data_file,"%d",&height);
            data_h.station=station;
            data_h.height=height;
            data_h.latitude=latitude;
            data_h.longitude=longitude;
            ah=insertionABRHeight(ah,data_h);
        }
        if(display_option==1){
            infixPath_abrh(ah,output_file);
        }
        else infixPathR_abrh(ah,output_file);
    }

    //sort P2 T2
    else if(sort_option==5){
        PABR2 a2=NULL;
        Data_abr2 data2;

         while (fscanf(data_file,"%ld;",&date) == 1){
            fscanf(data_file,"%f",&associated_data);
            data2.date=date;
            data2.associated_data=associated_data;
            a2=insertionAverage_abr2(a2,data2);
        }
        calculateAverage_abr2(a2);
        if(display_option==1){
            infixPath_abr2(a2,output_file);
        }
        else infixPathR_abr2(a2,output_file);
    }

    //sort P3 T3
    else if(sort_option==6){
         PABR3 a3=NULL;
        Data_abr3 data3;

         while (fscanf(data_file,"%d;",&station ) == 1){
            fscanf(data_file,"%ld;",&date);
            fscanf(data_file,"%f",&associated_data);
            data3.date=date;
            data3.station=station;
            data3.associated_data=associated_data;
            a3=insertion_oabr3(a3,data3);
        }

        if(display_option==1){
            infixPath_abr3(a3,output_file);
        }
        else infixPathR_abr3(a3,output_file);
    }

    //sort moisture
    else if(sort_option==7){      
        PABR_m am=NULL;
        Data_abrm data_m;

        if(sort_option2 == 1){
            while (fscanf(data_file,"%d;",&station) == 1){
                fscanf(data_file,"%d;",&moisture);
                fscanf(data_file,"%f,",&latitude);
                fscanf(data_file,"%f",&longitude);
                data_m.station=station;
                data_m.moisture=moisture;
                data_m.latitude=latitude;
                data_m.longitude=longitude;
                am=insertionABRMMax(am,data_m);
            }
            if(display_option==1){
                infixPath_abrm2(am,output_file);
            }
            else infixPathR_abrm2(am,output_file);
        }
        else{
            while (fscanf(data_file,"%d;",&station) == 1){
                fscanf(data_file,"%d;",&moisture);
                fscanf(data_file,"%f,",&latitude);
                fscanf(data_file,"%f",&longitude);
                data_m.station=station;
                data_m.moisture=moisture;
                data_m.latitude=latitude;
                data_m.longitude=longitude;
                am=insertionABRM(am,data_m);

            }

            if(display_option==1){
                infixPath_abrm(am,output_file);
            }
            else infixPathR_abrm(am,output_file);
        }

        
       
    }

    //sort wind
    else if(sort_option==8){
         PABRAA aa=NULL;
        Data_abra dataA1;

        while (fscanf(data_file,"%d;",&station) == 1){
            fscanf(data_file,"%f;",&associated_data);
            fscanf(data_file,"%f;",&associated_data2);
            fscanf(data_file,"%f,",&latitude);
            fscanf(data_file,"%f",&longitude);
            dataA1.station=station;
            dataA1.associated_DataA1=associated_data;
            dataA1.associated_DataA2=associated_data2;
            dataA1.latitude=latitude;
            dataA1.longitude=longitude;
            aa=insertionAverage_abra(aa,dataA1);
        }
        calculateAverage_abra(aa);
        if(display_option==1){
            infixPath_abra(aa,output_file);
        }
        else infixPathR_abra(aa,output_file);
    }  


}
void sort_avl(int sort_option,int display_option,int sort_option2,FILE* data_file,FILE* output_file){

    int h;
    int station; 
    float associated_data,associated_data2; 
    int height, moisture; 
    long date; 
    int g;
    float latitude, longitude;

    //sort P1 T1
    if(sort_option==1){
        PAVL1 a1=NULL;
        Data1 data1;

        while (fscanf(data_file,"%d;",&station) == 1){
            fscanf(data_file,"%f",&associated_data);
            data1.station=station;
            data1.associated_Data1=associated_data; 
            a1=insertionAVL1Max(a1,data1,&h);
        }
        if(display_option==1){
        infixPath(a1,output_file);
        }
        else infixPathR(a1,output_file);
    }

    //sort P1 T1
    else if(sort_option==2){
        PAVL1 a1=NULL;
        Data1 data1;

        while (fscanf(data_file,"%d;",&station) == 1){
            fscanf(data_file,"%f",&associated_data);
            data1.station=station;
            data1.associated_Data1=associated_data;
            a1=insertionAVL1Min(a1,data1,&h);
        }
        if(display_option==1){
            infixPath(a1,output_file);
        }
        else infixPathR(a1,output_file);
        }

    //sort P1 T1
    else if(sort_option==3){
        PAVL1 a1=NULL;
        Data1 data1;

        while (fscanf(data_file,"%d;",&station) == 1){
            fscanf(data_file,"%f",&associated_data);
            data1.station=station;
            data1.associated_Data1=associated_data;
            a1=insertionAVL1Average(a1,data1,&h);
        }
        calculateAverage(a1);
        if(display_option==1){
            infixPath(a1,output_file);
        }
        else infixPathR(a1,output_file);
    }

    //sort height
    else if(sort_option==4){
        PAVL_H ah=NULL;
        Data_h data_h;

        while(fscanf(data_file,"%d;",&station)==1){
            fscanf(data_file,"%f,",&latitude);
            fscanf(data_file,"%f;",&longitude);
            fscanf(data_file,"%d",&height);
            data_h.station=station;
            data_h.height=height;
            data_h.latitude=latitude;
            data_h.longitude=longitude;
            ah=insertionAVLHeight(ah,data_h,&h);
        }
        if(display_option==1){
            infixPath_h(ah,output_file);
        }
        else infixPathR_h(ah,output_file);
    }

    //sort P2 T2
    else if(sort_option==5){
        PAVL2 a2=NULL;
        Data2 data2;

         while (fscanf(data_file,"%ld;",&date) == 1){
            fscanf(data_file,"%f",&associated_data);
            data2.date2=date;
            data2.associated_Data2=associated_data;
            a2=insertionAVLAverage2(a2,data2,&h);
        }
        calculateAverage2(a2);
        if(display_option==1){
            infixPath2(a2,output_file);
        }
        else infixPathR2(a2,output_file);
    }

    //sort P3 T3
    else if(sort_option==6){
        PAVL3 a3=NULL;
        Data3 data3;

         while (fscanf(data_file,"%d;",&station ) == 1){
            fscanf(data_file,"%ld;",&date);
            fscanf(data_file,"%f",&associated_data);
            data3.date3=date;
            data3.station=station;
            data3.associated_Data3=associated_data;
            a3=insertionAVL3date(a3,data3,&h,&g);
        }

        if(display_option==1){
            infixPath3(a3,output_file);
        }
        else infixPathR3(a3,output_file);
    }

    //sort moisture
    else if(sort_option==7){      
        PAVL_m am=NULL;
        Data_m data_m;

        if(sort_option2 == 1){
            while (fscanf(data_file,"%d;",&station) == 1){
                fscanf(data_file,"%d;",&moisture);
                fscanf(data_file,"%f,",&latitude);
                fscanf(data_file,"%f",&longitude);
                data_m.station=station;
                data_m.moisture=moisture;
                data_m.latitude=latitude;
                data_m.longitude=longitude;
                am=insertionAVLMMax(am,data_m,&h);
            }
            if(display_option==1){
                infixPath_m2(am,output_file);
            }
            else infixPathR_m2(am,output_file);
        }
        else{
            while (fscanf(data_file,"%d;",&station) == 1){
                fscanf(data_file,"%d;",&moisture);
                fscanf(data_file,"%f,",&latitude);
                fscanf(data_file,"%f",&longitude);
                data_m.station=station;
                data_m.moisture=moisture;
                data_m.latitude=latitude;
                data_m.longitude=longitude;
                am=insertionAVLM(am,data_m,&h);

            }

            if(display_option==1){
                infixPath_m(am,output_file);
            }
            else infixPathR_m(am,output_file);
        }              
    }

    //sort wind
    else if(sort_option==8){
        PAVLAA aa=NULL;
        DataA1 dataA1;

        while (fscanf(data_file,"%d;",&station) == 1){
            fscanf(data_file,"%f;",&associated_data);
            fscanf(data_file,"%f;",&associated_data2);
            fscanf(data_file,"%f,",&latitude);
            fscanf(data_file,"%f",&longitude);
            dataA1.station=station;
            dataA1.associated_DataA1=associated_data;
            dataA1.associated_DataA2=associated_data2;
            dataA1.latitude=latitude;
            dataA1.longitude=longitude;
            aa=insertionAVLAAAverage(aa,dataA1,&h);
        }
        calculateAverageA(aa);
        if(display_option==1){
            infixPathA(aa,output_file);
        }
        else infixPathRA(aa,output_file);
    }  

}
