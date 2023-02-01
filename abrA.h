#ifndef ABRA_H
#define ABRA_H
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct data_abra{
    int station;
    float associated_DataA1;
    float associated_DataA2;
    int average_increment;
}Data_abra;

typedef struct ABRAA{
    Data_abra elmt;
    struct ABRAA * fg;
    struct ABRAA * fd;
}ABRAA;

typedef ABRAA* PABRAA;

/*!
     * @brief                       this function is used to write all values needed in the output file                                            
     * @param  e                    current element written
     * @param  out                  pointer relative to ouput file
     * @return                      nothing
     */
void treat_abra(Data_abra e,FILE* out);

/*!
     * @brief                       this function is used to browse into  the tree                                            
     * @param  a                    pointer relative to the tree
     * @param  out                  pointer relative to ouput file
     * @return                      nothing
     */
void infixPath_abra(PABRAA a, FILE* out);

/*!
     * @brief                       this function is used to browse into  the tree but in reverse                                           
     * @param  a                    pointer relative to the tree
     * @param  out                  pointer relative to ouput file
     * @return                      nothing
     */
void infixPathR_abra(PABRAA a, FILE* out);

/*!
     * @brief                       this function is used to create a new tree                                         
     * @param  e                    element you want to insert first in the tree
     * @return                      pointer relative to the tree
     */
PABRAA createTree_abra(Data_abra e);

 /*!
     * @brief                       this function is used to insert an element in the tree, keeping the the gross value of all associated_data                                          
     * @param  a                    pointer relative to the tree
     * @param  e                    element to insert
     * @return                      pointer relative to the tree
     */
PABRAA insertionAverage_abra(PABRAA a,Data_abra e);

/*!
     * @brief                       this function is used to calculate the average of the associated data in each element of the tree                                         
     * @param  a                    pointer relative to the tree
     * @return                      nothing
     */
void calculateAverage_abra(PABRAA a);
#endif

