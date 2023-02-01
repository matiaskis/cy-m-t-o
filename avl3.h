#ifndef AVL3_H
#define AVL3_H
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct data3{
    int station;
    float associated_Data3;
    long date3;
}Data3;

typedef struct avl3{
    Data3 elmt;
    struct avl3 * secondTree;
    struct avl3 * fg;
    struct avl3 * fd;
    int balance;
}AVL3;


typedef AVL3* PAVL3;

/*!
     * @brief                       this function is used to write all values needed in the output file                                            
     * @param  e                    current element written
     * @param  out                  pointer relative to ouput file
     * @return                      nothing
     */
void treat3(Data3 e,FILE* out);

/*!
     * @brief                       this function is used to browse into the second tree                                            
     * @param  a                    pointer relative to the tree
     * @param  out                  pointer relative to ouput file
     * @return                      nothing
     */
void secondInfixPath3(PAVL3 a,FILE * out);

/*!
     * @brief                       this function is used to browse into  the first tree                                            
     * @param  a                    pointer relative to the tree
     * @param  out                  pointer relative to ouput file
     * @return                      nothing
     */
void infixPath3(PAVL3 a, FILE* out);

 /*!
     * @brief                       this function is used to browse into  the second tree but in reverse                                           
     * @param  a                    pointer relative to the tree
     * @param  out                  pointer relative to ouput file
     * @return                      nothing
     */
void secondInfixPathR3(PAVL3 a,FILE * out);

 /*!
     * @brief                       this function is used to browse into  the first tree but in reverse                                           
     * @param  a                    pointer relative to the tree
     * @param  out                  pointer relative to ouput file
     * @return                      nothing
     */
void infixPathR3(PAVL3 a, FILE* out);

/*!
     * @brief                       this function is used to create the root of a new second tree                                         
     * @param  e                    element you want to insert first in the tree
     * @return                      pointer relative to the tree
     */
PAVL3 createTree3(Data3 e);

/*!
     * @brief                       this function is used to create a new tree                                         
     * @param  e                    element you want to insert first in the tree
     * @return                      pointer relative to the tree
     */
PAVL3 createTreeAVL3(Data3 e);

/*!
     * @brief                       this function is used to balance the tree                                         
     * @param  a                    pointer relative to the tree
     * @return                      pointer relative to the tree
     */
PAVL3 LeftRotation3(PAVL3 a);

/*!
     * @brief                       this function is used to balance the tree                                         
     * @param  a                    pointer relative to the tree
     * @return                      pointer relative to the tree
     */
PAVL3 RightRotation3(PAVL3 a);

/*!
     * @brief                       this function is used to balance the tree                                         
     * @param  a                    pointer relative to the tree
     * @return                      pointer relative to the tree
     */
PAVL3 doubleLeftRotation3(PAVL3 a);

/*!
     * @brief                       this function is used to balance the tree                                         
     * @param  a                    pointer relative to the tree
     * @return                      pointer relative to the tree
     */
PAVL3 doubleRightRotation3(PAVL3 a);

/*!
     * @brief                       this function is used to balance the tree                                         
     * @param  a                    pointer relative to the tree
     * @return                      pointer relative to the tree
     */
PAVL3 balanceAVL3(PAVL3 a);

/*!
     * @brief                       this function is used to insert an element in the second tree                                      
     * @param  a                    pointer relative to the tree
     * @param  e                    element to insert
     * @param h                     pointer relative to an integer value used to calculate the balance within the tree
     * @param g                     pointer relative to an integer value used to calculate the balance within the second tree
     * @return                      pointer relative to the tree
     */
PAVL3 insertionAVL3SecondTree(PAVL3 a,Data3 e, int* h);

/*!
     * @brief                       this function is used to insert an element in the first tree                                      
     * @param  a                    pointer relative to the tree
     * @param  e                    element to insert
     * @param h                     pointer relative to an integer value used to calculate the balance within the tree
     * @param g                     pointer relative to an integer value used to calculate the balance within the second tree
     * @return                      pointer relative to the tree
     */
PAVL3 insertionAVL3date(PAVL3 a,Data3 e, int* h,int * g);
#endif

