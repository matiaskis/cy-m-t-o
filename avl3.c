#include "avl3.h"
#include "avl1.h"

void treat3(Data3 e,FILE* out){
    long h,d,m,y;
    h=((e.date3%100));
    d=((e.date3%10000)-e.date3%100)/100;
    m=((e.date3%1000000)-e.date3%10000)/10000;
    y=((e.date3)-e.date3%1000000)/1000000;
    fprintf(out,"%ld/%ld/%ld %ld:00:00 ",d,m,y,h);
    fprintf(out,"%d ",e.station);
    fprintf(out,"%f\n",e.associated_Data3);    
}

void secondInfixPath3(PAVL3 a,FILE * out){
    if (a!=NULL) {
        secondInfixPath3(a->fg,out);
        treat3(a->elmt,out);
        free(a);
        secondInfixPath3(a->fd,out);
}
}

void infixPath3(PAVL3 a, FILE* out) {
if (a!=NULL) {
    infixPath3(a->fg,out);
    secondInfixPath3(a->secondTree,out);
    infixPath3(a->fd,out);
}
}

void secondInfixPathR3(PAVL3 a,FILE * out){
    if (a!=NULL) {
        secondInfixPathR3(a->fd,out);
        treat3(a->elmt,out);
        free(a);
        secondInfixPathR3(a->fg,out);
}
}

void infixPathR3(PAVL3 a, FILE* out) {
if (a!=NULL) {
    infixPathR3(a->fd,out); 
    secondInfixPathR3(a->secondTree,out);
    infixPathR3(a->fg,out);
}
}



PAVL3 createTree3(Data3 e){
    PAVL3 tree ;
    tree=malloc(sizeof(AVL3));
    if(tree==NULL){
        exit(1);
    }
    tree->elmt=e;
    tree->fg= NULL;
    tree->fd= NULL;
    tree->balance= 0;
    return tree;
}

PAVL3 createTreeAVL3(Data3 e){
    PAVL3 tree ;
    tree=malloc(sizeof(AVL3));
    if(tree==NULL){
        exit(1);
    }
    tree->elmt=e;
    tree->fg= NULL;
    tree->fd= NULL;
    tree->secondTree=createTree3(e);
    tree->balance= 0;
    return tree;
}

PAVL3 LeftRotation3(PAVL3 a){
    PAVL3 pivot; 
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

    PAVL3 RightRotation3(PAVL3 a){
    PAVL3 pivot ;
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

PAVL3 doubleLeftRotation3(PAVL3 a){
    a->fd = RightRotation3(a->fd);
     return LeftRotation3(a);
}

PAVL3 doubleRightRotation3(PAVL3 a){
    a->fg = LeftRotation3(a->fg);
     return RightRotation3(a);
}

PAVL3 balanceAVL3(PAVL3 a){

    if (a->balance >=  2){
        if (a->fd->balance >= 0){
            return LeftRotation3(a);
        }

        else return doubleLeftRotation3(a);
    }
    else if (a->balance  <=  -2){ 
        if (a->fg->balance <= 0){
            return RightRotation3(a);
        }

    

        else return doubleRightRotation3(a);
    }
    return a;
}

PAVL3 insertionAVL3SecondTree(PAVL3 a,Data3 e, int* h){

    if (a== NULL){
        *h=1;
        return createTree3(e);
    }
    else if (e.station < a->elmt.station){
    a->fg=insertionAVL3SecondTree(a->fg, e, h);
        *h =-*h; 
    }
    else if(e.station > a->elmt.station){
        a->fd=insertionAVL3SecondTree(a->fd, e, h);
        
    }
    else{
    
        *h=0;
        return a;
    }
    if (*h != 0){
        a->balance = a->balance + *h;
        a=balanceAVL3(a);
        if (a->balance== 0){
            *h = 0;
        }
        else *h = 1;
    }
    
    return a;
}

PAVL3 insertionAVL3date(PAVL3 a,Data3 e, int* h,int * g){

    if (a== NULL){
        *h=1;
        return createTreeAVL3(e);
    }
    else if (e.date3 < a->elmt.date3){
        a->fg=insertionAVL3date(a->fg, e, h,g);
        *h =-*h; 

    }
    else if(e.date3 > a->elmt.date3){
        a->fd=insertionAVL3date(a->fd, e, h,g);
    }
    else{
        a->secondTree=insertionAVL3SecondTree(a->secondTree,e,g);
        *h=0;
        return a;
    }
    if (*h != 0){
        a->balance = a->balance + *h;
        a=balanceAVL3(a);
        if (a->balance== 0){
            *h = 0;
        }
        else *h = 1;
    }
    
    return a;
    }
    

    
