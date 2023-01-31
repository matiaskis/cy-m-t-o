#ifndef AVLA_H
#define AVLA_H
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct dataa1{
    int station;
    float associated_DataA1;
    float associated_DataA2;
    int average_increment;
}DataA1;

typedef struct AVLAA{
    DataA1 elmt;
    struct AVLAA * fg;
    struct AVLAA * fd;
    int equilibre;
}AVLAA;

typedef AVLAA* PAVLAA;

/*!
     * @brief                       this function is used to write all values needed in the output file                                            
     * @param  e                    current element written
     * @param  out                  pointer relative to ouput file
     * @return                      nothing
     */
void treatA(DataA1 e,FILE* out);

/*!
     * @brief                       this function is used to browse into  the tree                                            
     * @param  a                    pointer relative to the tree
     * @param  out                  pointer relative to ouput file
     * @return                      nothing
     */
void infixPathA(PAVLAA a, FILE* out);

 /*!
     * @brief                       this function is used to browse into  the tree but in reverse                                           
     * @param  a                    pointer relative to the tree
     * @param  out                  pointer relative to ouput file
     * @return                      nothing
     */
void infixPathRA(PAVLAA a, FILE* out);

/*!
     * @brief                       this function is used to create a new tree                                         
     * @param  e                    element you want to insert first in the tree
     * @return                      pointer relative to the tree
     */
PAVLAA createTreeA(DataA1 e);

/*!
     * @brief                       this function is used to balance the tree                                         
     * @param  a                    pointer relative to the tree
     * @return                      pointer relative to the tree
     */
PAVLAA LeftRotationA(PAVLAA a);

/*!
     * @brief                       this function is used to balance the tree                                         
     * @param  a                    pointer relative to the tree
     * @return                      pointer relative to the tree
     */
PAVLAA RightRotationA(PAVLAA a);

/*!
     * @brief                       this function is used to balance the tree                                         
     * @param  a                    pointer relative to the tree
     * @return                      pointer relative to the tree
     */
PAVLAA doubleLeftRotationA(PAVLAA a);

/*!
     * @brief                       this function is used to balance the tree                                         
     * @param  a                    pointer relative to the tree
     * @return                      pointer relative to the tree
     */
PAVLAA doubleRightRotationA(PAVLAA a);

/*!
     * @brief                       this function is used to balance the tree                                         
     * @param  a                    pointer relative to the tree
     * @return                      pointer relative to the tree
     */
PAVLAA balanceAVLAA(PAVLAA a);

/*!
     * @brief                       this function is used to insert an element in the tree,keeping the the gross value of all associated_data                                       
     * @param  a                    pointer relative to the tree
     * @param  e                    element to insert
     * @param h                     pointer relative to an integer value used to calculate the balance within the tree
     * @return                      pointer relative to the tree
     */
PAVLAA insertionAVLAAAverage(PAVLAA a,DataA1 e, int* h);

/*!
     * @brief                       this function is used to calculate the average of the associated data in each element of the tree                                         
     * @param  a                    pointer relative to the tree
     * @return                      nothing
     */
void calculateAverageA(PAVLAA a);
#endif
