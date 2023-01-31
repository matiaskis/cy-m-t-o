#include "avl1.h"

void treat(Data1 e,FILE* out) {
    fprintf(out,"%d ",e.station);
    fprintf(out,"%f\n",e.associated_Data1);
}

void infixePath(PAVL1 a, FILE* out) {
if (a!=NULL) {
    infixePath(a->fg,out);
    treat(a->elmt,out);
    free(a);
    infixePath(a->fd,out);
}
}

void infixePathR(PAVL1 a, FILE* out) {
if (a!=NULL) {
    infixePathR(a->fd,out); 
    treat(a->elmt,out);
    free(a);
    infixePathR(a->fg,out);
}
}

int max(int a, int b) {
    return(a<b ? b : a);
}

int min(int a, int b) {
    return(a < b ? a : b);
}

PAVL1 createTree(Data1 e){
    PAVL1 tree ;
    tree=malloc(sizeof(AVL1));
    if(tree==NULL){
        exit(1);
    }
    tree->elmt=e;
    tree->fg= NULL;
    tree->fd= NULL;
    tree->balance= 0;
    tree->elmt.average_increment=1;
    return tree;
}

PAVL1 leftRotation(PAVL1 a){
    PAVL1 pivot; 
    float eq_a, eq_p;

    pivot = a->fd;
    a->fd = pivot->fg;
    pivot->fg = a;
    eq_a = a->balance;
    eq_p = pivot->balance;
    a->balance = eq_a - max(eq_p, 0) - 1;
    pivot->balance = min(min( eq_a-2, eq_a+eq_p-2), eq_p-1 );
    a = pivot;
    return a;
    }

    PAVL1 rightRotation(PAVL1 a){
    PAVL1 pivot ;
    float eq_a, eq_p;

    pivot = a->fg;
    a->fg = pivot->fd;
    pivot->fd = a;
    eq_a = a->balance;
    eq_p = pivot->balance;
    a->balance = eq_a - min(eq_p, 0) + 1;
    pivot->balance = max(max( eq_a+2, eq_a+eq_p+2), eq_p+1 );
    a = pivot;
    return a;
}

PAVL1 doubleleftRotation(PAVL1 a){
    a->fd = rightRotation(a->fd);
     return leftRotation(a);
}

PAVL1 doublerightRotation(PAVL1 a){
    a->fg = leftRotation(a->fg);
     return rightRotation(a);
}

PAVL1 balanceAVL1(PAVL1 a){

    if (a->balance >=  2){
        if (a->fd->balance >= 0){
            return leftRotation(a);
        }

        else return doubleleftRotation(a);
    }
    else if (a->balance  <=  -2){ 
        if (a->fg->balance <= 0){
            return rightRotation(a);
        }

    

        else return doublerightRotation(a);
    }
    return a;
}

 

PAVL1 insertionAVL1Max(PAVL1 a,Data1 e, int* h){

    if (a== NULL){
        *h=1;
        return createTree(e);
    }
    else if (e.station < a->elmt.station){
    a->fg=insertionAVL1Max(a->fg, e, h);
        *h =-*h; 
    }
    else if(e.station > a->elmt.station){
        a->fd=insertionAVL1Max(a->fd, e, h);
        
    }
    else{
        if(e.associated_Data1 > a->elmt.associated_Data1){
            a->elmt=e;
        }
        *h=0;
        return a;
    }
    if (*h != 0){
        a->balance = a->balance + *h;
        a=balanceAVL1(a);
        if (a->balance== 0){
            *h = 0;
        }
        else *h = 1;
    }
    
    return a;
    }

PAVL1 insertionAVL1Min(PAVL1 a,Data1 e, int* h){

    if (a== NULL){
        *h=1;
        return createTree(e);
    }
    else if (e.station < a->elmt.station){
    a->fg=insertionAVL1Min(a->fg, e, h);
        *h =-*h; 
    }
    else if(e.station > a->elmt.station){
        a->fd=insertionAVL1Min(a->fd, e, h);
        
    }
    else{
        if(e.associated_Data1 < a->elmt.associated_Data1){
            a->elmt=e;
        }
        *h=0;
        return a;
    }
    if (*h != 0){
        a->balance = a->balance + *h;
        a=balanceAVL1(a);
        if (a->balance== 0){
            *h = 0;
        }
        else *h = 1;
    }
    
    return a;
    }
    
PAVL1 insertionAVL1Average(PAVL1 a,Data1 e, int* h){

    if (a== NULL){
        *h=1;
        return createTree(e);
    }
    else if (e.station < a->elmt.station){
    a->fg=insertionAVL1Average(a->fg, e, h);
        *h =-*h; 
    }
    else if(e.station > a->elmt.station){
        a->fd=insertionAVL1Average(a->fd, e, h);
        
    }
    else{
        a->elmt.associated_Data1=a->elmt.associated_Data1+e.associated_Data1;
        a->elmt.average_increment=a->elmt.average_increment+1;
        *h=0;
        return a;
    }
    if (*h != 0){
        a->balance = a->balance + *h;
        a=balanceAVL1(a);
        if (a->balance== 0){
            *h = 0;
        }
        else *h = 1;
    }
    
    return a;
    }
 
void calculateAverage(PAVL1 a){
    if (a!=NULL) {
    calculateAverage(a->fg);
    a->elmt.associated_Data1=a->elmt.associated_Data1/a->elmt.average_increment;
    calculateAverage(a->fd);
    }
}
