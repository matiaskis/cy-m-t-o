#ifndef AVL2_H
#define AVL2_H
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct data2{
    long date2;
    float associated_Data2;
    int average_increment;
}Data2;

typedef struct avl2{
    Data2 elmt;
    struct avl2 * fg;
    struct avl2 * fd;
    int balance;
}AVL2;

typedef AVL2* PAVL2;

/*!
     * @brief                       this function is used to write all values needed in the output file                                            
     * @param  e                    current element written
     * @param  out                  pointer relative to ouput file
     * @return                      nothing
     */
void treat2(Data2 e,FILE* out);

/*!
     * @brief                       this function is used to browse into  the tree                                            
     * @param  a                    pointer relative to the tree
     * @param  out                  pointer relative to ouput file
     * @return                      nothing
     */
void infixPath2(PAVL2 a, FILE* out);

 /*!
     * @brief                       this function is used to browse into  the tree but in reverse                                           
     * @param  a                    pointer relative to the tree
     * @param  out                  pointer relative to ouput file
     * @return                      nothing
     */
void infixPathR2(PAVL2 a, FILE* out);

/*!
     * @brief                       this function is used to create a new tree                                         
     * @param  e                    element you want to insert first in the tree
     * @return                      pointer relative to the tree
     */
PAVL2 createTree2(Data2 e);

/*!
     * @brief                       this function is used to balance the tree                                         
     * @param  a                    pointer relative to the tree
     * @return                      pointer relative to the tree
     */
PAVL2 LeftRotation2(PAVL2 a);

/*!
     * @brief                       this function is used to balance the tree                                         
     * @param  a                    pointer relative to the tree
     * @return                      pointer relative to the tree
     */
PAVL2 RightRotation2(PAVL2 a);

/*!
     * @brief                       this function is used to balance the tree                                         
     * @param  a                    pointer relative to the tree
     * @return                      pointer relative to the tree
     */
PAVL2 doubleLeftRotation2(PAVL2 a);

/*!
     * @brief                       this function is used to balance the tree                                         
     * @param  a                    pointer relative to the tree
     * @return                      pointer relative to the tree
     */
PAVL2 doubleRightRotation2(PAVL2 a);

/*!
     * @brief                       this function is used to balance the tree                                         
     * @param  a                    pointer relative to the tree
     * @return                      pointer relative to the tree
     */
PAVL2 balanceAVL2(PAVL2 a);

/*!
     * @brief                       this function is used to insert an element in the tree,keeping the the gross value of all associated_data                                       
     * @param  a                    pointer relative to the tree
     * @param  e                    element to insert
     * @param h                     pointer relative to an integer value used to calculate the balance within the tree
     * @return                      pointer relative to the tree
     */
PAVL2 insertionAVLAverage2(PAVL2 a,Data2 e, int* h);

/*!
     * @brief                       this function is used to calculate the average of the associated data in each element of the tree                                         
     * @param  a                    pointer relative to the tree
     * @return                      nothing
     */
void calculateAverage2(PAVL2 a);
#endif

