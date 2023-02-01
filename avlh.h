#ifndef AVLH_H
#define AVLH_H
#include <stdio.h>
#include <stdlib.h>
#include <string.h>


typedef struct data_h{
    int station;
    int height;
    //float latitude;
    //float longitude;
    int duplicate;
    int duplicate2;
}Data_h;

typedef struct avl_h{
    Data_h elmt;
    struct avl_h * fg;
    struct avl_h * fd;
    int balance;
}AVL_H;

typedef AVL_H* PAVL_H;

/*!
     * @brief                       this function is used to write all values needed in the output file                                            
     * @param  e                    current element written
     * @param  out                  pointer relative to ouput file
     * @return                      nothing
     */
void treat_h(Data_h e,FILE* out);

/*!
     * @brief                       this function is used to browse into  the tree                                            
     * @param  a                    pointer relative to the tree
     * @param  out                  pointer relative to ouput file
     * @return                      nothing
     */
void infixPath_h(PAVL_H a, FILE* out);

 /*!
     * @brief                       this function is used to browse into  the tree but in reverse                                           
     * @param  a                    pointer relative to the tree
     * @param  out                  pointer relative to ouput file
     * @return                      nothing
     */
void infixPathR_h(PAVL_H a, FILE* out);

/*!
     * @brief                       this function is used to create a new tree                                         
     * @param  e                    element you want to insert first in the tree
     * @return                      pointer relative to the tree
     */
PAVL_H createTree_h(Data_h e);

/*!
     * @brief                       this function is used to balance the tree                                         
     * @param  a                    pointer relative to the tree
     * @return                      pointer relative to the tree
     */
PAVL_H LeftRotation_h(PAVL_H a);

/*!
     * @brief                       this function is used to balance the tree                                         
     * @param  a                    pointer relative to the tree
     * @return                      pointer relative to the tree
     */
PAVL_H RigthRotation_h(PAVL_H a);

/*!
     * @brief                       this function is used to balance the tree                                         
     * @param  a                    pointer relative to the tree
     * @return                      pointer relative to the tree
     */
PAVL_H doubleLeftRotation_h(PAVL_H a);

/*!
     * @brief                       this function is used to balance the tree                                         
     * @param  a                    pointer relative to the tree
     * @return                      pointer relative to the tree
     */
PAVL_H doubleRigthRotation_h(PAVL_H a);

/*!
     * @brief                       this function is used to balance the tree                                         
     * @param  a                    pointer relative to the tree
     * @return                      pointer relative to the tree
     */
PAVL_H balanceAVL_h(PAVL_H a);

/*!
     * @brief                       this function is used to insert an element in the tree                                         
     * @param  a                    pointer relative to the tree
     * @param  e                    element to insert
     * @param h                     pointer relative to an integer value used to calculate the balance within the tree
     * @return                      pointer relative to the tree
     */
PAVL_H insertionAVLHeight(PAVL_H a,Data_h e, int* h);
#endif

