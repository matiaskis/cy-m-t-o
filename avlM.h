#ifndef AVLM_H
#define AVLM_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct data_m{
    int station;
    int moisture;
    float duplicates[61];
    float duplicatela[61];
    float duplicatelo[61];
    int counter;
    float latitude;
    float longitude;
}Data_m;

typedef struct avl_m{
    Data_m elmt;
    struct avl_m * fg;
    struct avl_m * fd;
    int balance;
}AVL_m;

typedef AVL_m* PAVL_m;

/*!
     * @brief                       this function is used to write all values needed in the output file                                            
     * @param  e                    current element written
     * @param  out                  pointer relative to ouput file
     * @return                      nothing
     */
void treat_m(int count,Data_m e,FILE* out);

/*!
     * @brief                       this function is used to write all values needed in the output file                                            
     * @param  e                    current element written
     * @param  out                  pointer relative to ouput file
     * @return                      nothing
     */
void treat_m2(Data_m e,FILE* out);

/*!
     * @brief                       this function is used to browse into  the tree                                            
     * @param  a                    pointer relative to the tree
     * @param  out                  pointer relative to ouput file
     * @return                      nothing
     */
void infixPath_m(PAVL_m a, FILE* out);

 /*!
     * @brief                       this function is used to browse into  the tree but in reverse                                           
     * @param  a                    pointer relative to the tree
     * @param  out                  pointer relative to ouput file
     * @return                      nothing
     */
void infixPathR_m(PAVL_m a, FILE* out);

/*!
     * @brief                       this function is used to browse into  the tree                                            
     * @param  a                    pointer relative to the tree
     * @param  out                  pointer relative to ouput file
     * @return                      nothing
     */
void infixPath_m2(PAVL_m a, FILE* out);

 /*!
     * @brief                       this function is used to browse into  the tree but in reverse                                           
     * @param  a                    pointer relative to the tree
     * @param  out                  pointer relative to ouput file
     * @return                      nothing
     */
void infixPathR_m2(PAVL_m a, FILE* out);

/*!
     * @brief                       this function is used to create a new tree                                         
     * @param  e                    element you want to insert first in the tree
     * @return                      pointer relative to the tree
     */
PAVL_m createTree_m(Data_m e);

/*!
     * @brief                       this function is used to balance the tree                                         
     * @param  a                    pointer relative to the tree
     * @return                      pointer relative to the tree
     */
PAVL_m LeftRotation_m(PAVL_m a);

/*!
     * @brief                       this function is used to balance the tree                                         
     * @param  a                    pointer relative to the tree
     * @return                      pointer relative to the tree
     */
PAVL_m RightRotation_m(PAVL_m a);

/*!
     * @brief                       this function is used to balance the tree                                         
     * @param  a                    pointer relative to the tree
     * @return                      pointer relative to the tree
     */
PAVL_m doubleLeftRoation_m(PAVL_m a);

/*!
     * @brief                       this function is used to balance the tree                                         
     * @param  a                    pointer relative to the tree
     * @return                      pointer relative to the tree
     */
PAVL_m doubleRightRotation_m(PAVL_m a);

/*!
     * @brief                       this function is used to balance the tree                                         
     * @param  a                    pointer relative to the tree
     * @return                      pointer relative to the tree
     */
PAVL_m balanceAVL_m(PAVL_m a);

/*!
     * @brief                       this function is used to insert an element in the tree                                        
     * @param  a                    pointer relative to the tree
     * @param  e                    element to insert
     * @param h                     pointer relative to an integer value used to calculate the balance within the tree
     * @return                      pointer relative to the tree
     */
PAVL_m insertionAVLM(PAVL_m a,Data_m e, int* h);

/*!
     * @brief                       this function is used to insert an element in the tree, keeping the max value of associated_data                                         
     * @param  a                    pointer relative to the tree
     * @param  e                    element to insert
     * @param h                     pointer relative to an integer value used to calculate the balance within the tree
     * @return                      pointer relative to the tree
     */
PAVL_m insertionAVLMMax(PAVL_m a,Data_m e, int* h);

#endif


