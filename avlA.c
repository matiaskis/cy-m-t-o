#include "avl1.h"
#include "avlA.h"

void treatA(DataA1 e,FILE* out) {
    fprintf(out,"%d ",e.station);
    fprintf(out,"%f ",e.associated_DataA1);
    fprintf(out,"%f ",e.associated_DataA2);
    fprintf(out,"%f ",e.latitude);
    fprintf(out,"%f\n",e.longitude);
}

void infixPathA(PAVLAA a, FILE* out) {
if (a!=NULL) {
    infixPathA(a->fg,out);
    treatA(a->elmt,out);
    free(a);
    infixPathA(a->fd,out);
}
}

void infixPathRA(PAVLAA a, FILE* out) {
if (a!=NULL) {
    infixPathRA(a->fd,out); 
    treatA(a->elmt,out);
    free(a);
    infixPathRA(a->fg,out);
}
}

PAVLAA createTreeA(DataA1 e){
    PAVLAA tree ;
    tree=malloc(sizeof(AVLAA));
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

PAVLAA LeftRotationA(PAVLAA a){
    PAVLAA pivot; 
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

    PAVLAA RightRotationA(PAVLAA a){
    PAVLAA pivot ;
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

PAVLAA doubleLeftRotationA(PAVLAA a){
    a->fd = RightRotationA(a->fd);
     return LeftRotationA(a);
}

PAVLAA doubleRightRotationA(PAVLAA a){
    a->fg = LeftRotationA(a->fg);
     return RightRotationA(a);
}

PAVLAA balanceAVLAA(PAVLAA a){

    if (a->balance >=  2){
        if (a->fd->balance >= 0){
            return LeftRotationA(a);
        }

        else return doubleLeftRotationA(a);
    }
    else if (a->balance  <=  -2){ 
        if (a->fg->balance <= 0){
            return RightRotationA(a);
        }

    

        else return doubleRightRotationA(a);
    }
    return a;
}

    
PAVLAA insertionAVLAAAverage(PAVLAA a,DataA1 e, int* h){

    if (a== NULL){
        *h=1;
        return createTreeA(e);
    }
    else if (e.station < a->elmt.station){
    a->fg=insertionAVLAAAverage(a->fg, e, h);
        *h =-*h; 
    }
    else if(e.station > a->elmt.station){
        a->fd=insertionAVLAAAverage(a->fd, e, h);
        
    }
    else{
        a->elmt.associated_DataA1=a->elmt.associated_DataA1+e.associated_DataA1;
        a->elmt.associated_DataA2=a->elmt.associated_DataA2+e.associated_DataA2;
        a->elmt.average_increment=a->elmt.average_increment+1;
        *h=0;
        return a;
    }
    if (*h != 0){
        a->balance = a->balance + *h;
        a=balanceAVLAA(a);
        if (a->balance== 0){
            *h = 0;
        }
        else *h = 1;
    }
    
    return a;
    }
 
void calculateAverageA(PAVLAA a){
    if (a!=NULL) {
    calculateAverageA(a->fg);
    a->elmt.associated_DataA1=a->elmt.associated_DataA1/a->elmt.average_increment;
    a->elmt.associated_DataA2=a->elmt.associated_DataA2/a->elmt.average_increment;
    calculateAverageA(a->fd);
    }
}


