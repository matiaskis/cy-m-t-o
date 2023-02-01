#ifndef ABR2_H
#define ABR2_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct data_abr2{
    long date;
    float associated_data;
    int average_increment;
}Data_abr2;

typedef struct abr2{
    Data_abr2 elmt;
    struct abr2 * fg;
    struct abr2 * fd;
}ABR2;

typedef ABR2* PABR2;

    /*!
     * @brief                       this function is used to write all values needed in the output file                                            
     * @param  e                    current element written
     * @param  out                  pointer relative to ouput file
     * @return                      nothing
     */
    void treat_abr2(Data_abr2 e,FILE* out) ;
    
    /*!
     * @brief                       this function is used to browse into  the tree                                            
     * @param  a                    pointer relative to the tree
     * @param  out                  pointer relative to ouput file
     * @return                      nothing
     */
    void infixPath_abr2(PABR2 a, FILE* out);

    /*!
     * @brief                       this function is used to browse into  the tree but in reverse                                           
     * @param  a                    pointer relative to the tree
     * @param  out                  pointer relative to ouput file
     * @return                      nothing
     */
    void infixPathR_abr2(PABR2 a, FILE* out);

    /*!
     * @brief                       this function is used to create a new tree                                         
     * @param  e                    element you want to insert first in the tree
     * @return                      pointer relative to the tree
     */
    PABR2 createTree_abr2(Data_abr2 e);
    
    /*!
     * @brief                       this function is used to insert an element in the tree, keeping the the gross value of all associated_data                                          
     * @param  a                    pointer relative to the tree
     * @param  e                    element to insert
     * @return                      pointer relative to the tree
     */
    PABR2 insertionAverage_abr2(PABR2 a, Data_abr2 e);
    
    /*!
     * @brief                       this function is used to calculate the average of the associated data in each element of the tree                                         
     * @param  a                    pointer relative to the tree
     * @return                      nothing
     */
    void calculateAverage_abr2(PABR2 a);
#endif
