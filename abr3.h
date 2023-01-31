#ifndef ABR3_H
#define ABR3_H
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct data_abr3{
    int station;
    float associated_data;
    long date;
}Data_abr3;

typedef struct abr3{
    Data_abr3 elmt;
    struct abr3 * secondTree;
    struct abr3 * fg;
    struct abr3 * fd;
}ABR3;

typedef ABR3* PABR3;


    /*!
     * @brief                       this function is used to write all values needed in the output file                                            
     * @param  e                    current element written
     * @param  out                  pointer relative to ouput file
     * @return                      nothing
     */
    void treat_abr3(Data_abr3 e,FILE* out);

    /*!
     * @brief                       this function is used to browse into the second tree used to sort all the associated data                                       
     * @param  a                    pointer relative to the tree
     * @param  out                  pointer relative to ouput file
     * @return                      nothing
     */
    void secondInfixPath(PABR3 a,FILE * out);

    /*!
     * @brief                       this function is used to browse into the tree                                        
     * @param  a                    pointer relative to the tree
     * @param  out                  pointer relative to ouput file
     * @return                      nothing
     */
    void infixPath_abr3(PABR3 a, FILE* out) ;
    
    /*!
     * @brief                       this function is used to browse into the second tree used to sort all the associated data but in reverse                                      
     * @param  a                    pointer relative to the tree
     * @param  out                  pointer relative to ouput file
     * @return                      nothing
     */
    void secondinfixPathR_abr3(PABR3 a,FILE * out);
    
    /*!
     * @brief                       this function is used to browse into the tree in reverse                                       
     * @param  a                    pointer relative to the tree
     * @param  out                  pointer relative to ouput file
     * @return                      nothing
     */
    void infixPathR_abr3(PABR3 a, FILE* out) ;
    
     /*!
     * @brief                       this function is used to create the root of each second tree                                       
     * @param  e                    element to insert
     * @return                      pointer relative to the tree
     */
    PABR3 createTree_abr3(Data_abr3 e);
    
    /*!
     * @brief                       this function is used to create a new tree                                       
     * @param  e                    element to insert
     * @return                      pointer relative to the tree
     */
    PABR3 createTree_oabr3(Data_abr3 e);
    
    /*!
     * @brief                       this function is used to insert an element in the second tree                                      
     * @param  a                    pointer relative to the tree
     * @param  e                    element to insert
     * @return                      pointer relative to the tree
     */
    PABR3 insertionABR3SecondTree(PABR3 a,Data_abr3 e);
    
    /*!
     * @brief                       this function is used to insert an element in the first tree                                      
     * @param  a                    pointer relative to the tree
     * @param  e                    element to insert
     * @return                      pointer relative to the tree
     */
    PABR3 insertionABR_oabr3(PABR3 a,Data_abr3 e);
#endif
