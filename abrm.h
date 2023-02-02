#ifndef ABRM_H
#define ABRM_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct data_abrm{
    int station;
    int moisture;
    float duplicates[61];
    float duplicatela[61];
    float duplicatelo[61];
    int counter;
    float latitude;
    float longitude;
}Data_abrm;

typedef struct abr_m{
    Data_abrm elmt;
    struct abr_m * fg;
    struct abr_m * fd;
}ABR_m;

typedef ABR_m* PABR_m;

    /*!
     * @brief                       this function is used to write all values needed in the output file                                            
     * @param  e                    current element written
     * @param  out                  pointer relative to ouput file
     * @return                      nothing
     */
    void treat_abrm(int count,Data_abrm e,FILE* out);

    /*!
     * @brief                       this function is used to write all values needed in the output file                                            
     * @param  e                    current element written
     * @param  out                  pointer relative to ouput file
     * @return                      nothing
     */
    void treat_abrm2(Data_abrm e,FILE* out);

/*!
     * @brief                       this function is used to browse into  the tree                                            
     * @param  a                    pointer relative to the tree
     * @param  out                  pointer relative to ouput file
     * @return                      nothing
     */
    void infixPath_abrm(PABR_m a, FILE* out);

/*!
     * @brief                       this function is used to browse into  the tree but in reverse                                           
     * @param  a                    pointer relative to the tree
     * @param  out                  pointer relative to ouput file
     * @return                      nothing
     */
    void infixPathR_abrm(PABR_m a, FILE* out);

/*!
     * @brief                       this function is used to browse into  the tree                                            
     * @param  a                    pointer relative to the tree
     * @param  out                  pointer relative to ouput file
     * @return                      nothing
     */
    void infixPath_abrm2(PABR_m a, FILE* out);

/*!
     * @brief                       this function is used to browse into  the tree but in reverse                                           
     * @param  a                    pointer relative to the tree
     * @param  out                  pointer relative to ouput file
     * @return                      nothing
     */
    void infixPathR_abrm2(PABR_m a, FILE* out);

/*!
     * @brief                       this function is used to create a new tree                                         
     * @param  e                    element you want to insert first in the tree
     * @return                      pointer relative to the tree
     */
    PABR_m creerArbre_abrm(Data_abrm e);

/*!
     * @brief                       this function is used to insert an element in the tree                                        
     * @param  a                    pointer relative to the tree
     * @param  e                    element to insert
     * @return                      pointer relative to the tree
     */
    PABR_m insertionABRM(PABR_m a,Data_abrm e);

/*!
     * @brief                       this function is used to insert an element in the tree, keeping the max value of associated_data                                         
     * @param  a                    pointer relative to the tree
     * @param  e                    element to insert
     * @return                      pointer relative to the tree
     */
    PABR_m insertionABRMMax(PABR_m a,Data_abrm e);

#endif

