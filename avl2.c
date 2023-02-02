#include "avl2.h"
#include "avl1.h"

void treat2(Data2 e,FILE* out) {
    long h,d,m,y;
    h=((e.date2%100));
    d=((e.date2%10000)-e.date2%100)/100;
    m=((e.date2%1000000)-e.date2%10000)/10000;
    y=((e.date2)-e.date2%1000000)/1000000;
    fprintf(out,"%ld/%ld/%ld %ld:00:00 ",d,m,y,h);
    fprintf(out,"%f\n",e.associated_Data2);
}

void infixPath2(PAVL2 a, FILE* out) {
if (a!=NULL) {
    infixPath2(a->fg,out);
    treat2(a->elmt,out);
    free(a);
    infixPath2(a->fd,out);
}
}

void infixPathR2(PAVL2 a, FILE* out) {
if (a!=NULL) {
    infixPathR2(a->fd,out); 
    treat2(a->elmt,out);
    free(a);
    infixPathR2(a->fg,out);
}
}



PAVL2 createTree2(Data2 e){
    PAVL2 tree=NULL ;
    tree=malloc(sizeof(AVL2));
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

PAVL2 LeftRotation2(PAVL2 a){
    PAVL2 pivot=NULL; 
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

    PAVL2 RightRotation2(PAVL2 a){
    PAVL2 pivot=NULL ;
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

PAVL2 doubleLeftRotation2(PAVL2 a){
    a->fd = RightRotation2(a->fd);
     return LeftRotation2(a);
}

PAVL2 doubleRightRotation2(PAVL2 a){
    a->fg = LeftRotation2(a->fg);
     return RightRotation2(a);
}

PAVL2 balanceAVL2(PAVL2 a){

    if (a->balance >=  2){
        if (a->fd->balance >= 0){
            return LeftRotation2(a);
        }

        else return doubleLeftRotation2(a);
    }
    else if (a->balance  <=  -2){ 
        if (a->fg->balance <= 0){
            return RightRotation2(a);
        }

    

        else return doubleRightRotation2(a);
    }
    return a;
}

 


    
PAVL2 insertionAVLAverage2(PAVL2 a,Data2 e, int* h){

    if (a== NULL){
        *h=1;
        return createTree2(e);
    }
    else if (e.date2 < a->elmt.date2){
    a->fg=insertionAVLAverage2(a->fg, e, h);
        *h =-*h; 
    }
    else if(e.date2 > a->elmt.date2){
        a->fd=insertionAVLAverage2(a->fd, e, h);
        
    }
    else{
        a->elmt.associated_Data2=a->elmt.associated_Data2+e.associated_Data2;
        a->elmt.average_increment=a->elmt.average_increment+1;
        *h=0;
        return a;
    }
    if (*h != 0){
        a->balance = a->balance + *h;
        a=balanceAVL2(a);
        if (a->balance== 0){
            *h = 0;
        }
        else *h = 1;
    }
    
    return a;
    }
 
void calculateAverage2(PAVL2 a){
    if (a!=NULL) {
    calculateAverage2(a->fg);
    a->elmt.associated_Data2=a->elmt.associated_Data2/a->elmt.average_increment;
    calculateAverage2(a->fd);
    }
}







