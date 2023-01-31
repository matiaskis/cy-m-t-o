#ifndef AVL1_H
#define AVL1_H
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct data1{
    int station;
    float associated_Data1;
    int average_increment;
}Data1;

typedef struct avl1{
    Data1 elmt;
    struct avl1 * fg;
    struct avl1 * fd;
    int balance;
}AVL1;

typedef AVL1* PAVL1;

/*!
     * @brief                       this function is used to write all values needed in the output file                                            
     * @param  e                    current element written
     * @param  out                  pointer relative to ouput file
     * @return                      nothing
     */
void treat(Data1 e,FILE* out);

/*!
     * @brief                       this function is used to browse into  the tree                                            
     * @param  a                    pointer relative to the tree
     * @param  out                  pointer relative to ouput file
     * @return                      nothing
     */
void infixPath(PAVL1 a, FILE* out);

 /*!
     * @brief                       this function is used to browse into  the tree but in reverse                                           
     * @param  a                    pointer relative to the tree
     * @param  out                  pointer relative to ouput file
     * @return                      nothing
     */
void infixPathR(PAVL1 a, FILE* out);

 /*!
     * @brief                       this function is used to return the max of two integer value                                          
     * @param  a                    pointer relative to the tree
     * @param  out                  pointer relative to ouput file
     * @return                      integer value
     */
int max(int a, int b);

 /*!
     * @brief                       this function is used to return the min of two integer value                                           
     * @param  a                    pointer relative to the tree
     * @param  out                  pointer relative to ouput file
     * @return                      integer value
     */
int min(int a, int b);

/*!
     * @brief                       this function is used to create a new tree                                         
     * @param  e                    element you want to insert first in the tree
     * @return                      pointer relative to the tree
     */
PAVL1 createTree(Data1 e);

/*!
     * @brief                       this function is used to balance the tree                                         
     * @param  a                    pointer relative to the tree
     * @return                      pointer relative to the tree
     */
PAVL1 leftRotation(PAVL1 a);

/*!
     * @brief                       this function is used to balance the tree                                         
     * @param  a                    pointer relative to the tree
     * @return                      pointer relative to the tree
     */
PAVL1 rightRotation(PAVL1 a);

/*!
     * @brief                       this function is used to balance the tree                                         
     * @param  a                    pointer relative to the tree
     * @return                      pointer relative to the tree
     */
PAVL1 doubleLeftRotation(PAVL1 a);

/*!
     * @brief                       this function is used to balance the tree                                         
     * @param  a                    pointer relative to the tree
     * @return                      pointer relative to the tree
     */
PAVL1 doubleRightRotation(PAVL1 a);

/*!
     * @brief                       this function is used to balance the tree                                         
     * @param  a                    pointer relative to the tree
     * @return                      pointer relative to the tree
     */
PAVL1 balanceAVL1(PAVL1 a);

/*!
     * @brief                       this function is used to insert an element in the tree, keeping the max value of associated_data                                         
     * @param  a                    pointer relative to the tree
     * @param  e                    element to insert
     * @param h                     pointer relative to an integer value used to calculate the balance within th tree
     * @return                      pointer relative to the tree
     */
PAVL1 insertionAVL1Max(PAVL1 a,Data1 e, int* h);

/*!
     * @brief                       this function is used to insert an element in the tree, keeping the min value of associated_data                                         
     * @param  a                    pointer relative to the tree
     * @param  e                    element to insert
     * @param h                     pointer relative to an integer value used to calculate the balance within th tree
     * @return                      pointer relative to the tree
     */
PAVL1 insertionAVL1Min(PAVL1 a,Data1 e, int* h);

/*!
     * @brief                       this function is used to insert an element in the tree,keeping the the gross value of all associated_data                                       
     * @param  a                    pointer relative to the tree
     * @param  e                    element to insert
     * @param h                     pointer relative to an integer value used to calculate the balance within th tree
     * @return                      pointer relative to the tree
     */
PAVL1 insertionAVL1Average(PAVL1 a,Data1 e, int* h);

/*!
     * @brief                       this function is used to calculate the average of the associated data in each element of the tree                                         
     * @param  a                    pointer relative to the tree
     * @return                      nothing
     */
void calculateAverage(PAVL1 a);
#endif
