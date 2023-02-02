#ifndef ABRH_H
#define ABRH_H
#include <stdio.h>
#include <stdlib.h>
#include <string.h>


typedef struct data_abrh{
    int station;
    int height;
    float latitude;
    float longitude;
    float duplicate[3];
    float duplicate2[3];
}Data_abrh;

typedef struct abr_h{
    Data_abrh elmt;
    struct abr_h * fg;
    struct abr_h * fd;
}ABR_H;

typedef ABR_H* PABR_H;

    /*!
     * @brief                       this function is used to write all values needed in the output file                                            
     * @param  e                    current element written
     * @param  out                  pointer relative to ouput file
     * @return                      nothing
     */
    void treat_abrh(Data_abrh e,FILE* out);
    
    /*!
     * @brief                       this function is used to browse into  the tree                                            
     * @param  a                    pointer relative to the tree
     * @param  out                  pointer relative to ouput file
     * @return                      nothing
     */
    void infixPath_abrh(PABR_H a, FILE* out);
    
    /*!
     * @brief                       this function is used to browse into  the tree but in reverse                                           
     * @param  a                    pointer relative to the tree
     * @param  out                  pointer relative to ouput file
     * @return                      nothing
     */
    void infixPathR_abrh(PABR_H a, FILE* out);
    
    /*!
     * @brief                       this function is used to create a new tree                                         
     * @param  e                    element you want to insert first in the tree
     * @return                      pointer relative to the tree
     */
    PABR_H createTree_abrh(Data_abrh e);
    
    /*!
     * @brief                       this function is used to insert an element in the tree                                       
     * @param  a                    pointer relative to the tree
     * @param  e                    element to insert
     * @return                      pointer relative to the tree
     */
    PABR_H insertionABRHeight(PABR_H a,Data_abrh e);
#endif

