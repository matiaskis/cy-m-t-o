#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "sort.h"

int main(int argc, char* argv[]){
    
    int sort_option=atoi(argv[3]);
    int display_option=atoi(argv[4]);
    int sort_technique=atoi(argv[5]);
    int sort_option2;
    if(argv[6]!=NULL){
        sort_option2=atoi(argv[6]);
    }

    FILE* data_file=fopen(argv[1],"r+");
    if(data_file==NULL){
        return 2;
    }
    FILE* output_file=fopen(argv[2],"w");
    if(data_file==NULL){
        return 3;
    }
   
   
    if(sort_technique == 1){
        sort_avl(sort_option,display_option,sort_option2,data_file,output_file);
    }
    else if (sort_technique == 2){
        sort_abr(sort_option,display_option,sort_option2,data_file,output_file);
    }
    else sort_tab(sort_option,display_option,sort_option2,data_file,output_file);

    

    fclose(data_file);
    fclose(output_file);
    return 0;
}

