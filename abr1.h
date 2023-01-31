#ifndef ABR1_H
#define ABR1_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct data1ABR{
    int station;
    float associated_data;
    int average_increment;
}Data1ABR;

typedef struct abr1{
    Data1ABR elmt;
    struct abr1 * fg;
    struct abr1 * fd;
}ABR1;

typedef ABR1* PABR1;

    /*!
     * @brief                       this function is used to write all values needed in the output file                                            
     * @param  e                    current element written
     * @param  out                  pointer relative to ouput file
     * @return                      nothing
     */
     void treat_abr1(Data1ABR e,FILE* out) ;

    /*!
     * @brief                       this function is used to browse into  the tree                                            
     * @param  a                    pointer relative to the tree
     * @param  out                  pointer relative to ouput file
     * @return                      nothing
     */
    void infixPath_abr1(PABR1 a, FILE* out);

    /*!
     * @brief                       this function is used to browse into  the tree but in reverse                                           
     * @param  a                    pointer relative to the tree
     * @param  out                  pointer relative to ouput file
     * @return                      nothing
     */
     void infixPathR_abr1(PABR1 a, FILE* out);

    /*!
     * @brief                       this function is used to create a new tree                                         
     * @param  e                    element you want to insert first in the tree
     * @return                      pointer relative to the tree
     */
    PABR1 createTree_abr1(Data1ABR e);

    /*!
     * @brief                       this function is used to insert a element in the tree, keeping the max value of associated_data                                         
     * @param  a                    pointer relative to the tree
     * @param  e                    element to insert
     * @return                      pointer relative to the tree
     */
    PABR1 insertionMax_abr1(PABR1 a,Data1ABR e);

    /*!
     * @brief                       this function is used to insert a element in the tree, keeping the min value of associated_data                                          
     * @param  a                    pointer relative to the tree
     * @param  e                    element to insert
     * @return                      pointer relative to the tree
     */
    PABR1 insertionMin_abr1(PABR1 a,Data1ABR e);

    /*!
     * @brief                       this function is used to insert a element in the tree, keeping the the gross value of all associated_data                                          
     * @param  a                    pointer relative to the tree
     * @param  e                    element to insert
     * @return                      pointer relative to the tree
     */
    PABR1 insertionAverage_abr1(PABR1 a, Data1ABR e);

    /*!
     * @brief                       this function is used to calculate the average of the associated data in each element of the tree                                         
     * @param  a                    pointer relative to the tree
     * @return                      nothing
     */
    void calculateAverage_abr1(PABR1 a);
#endif
