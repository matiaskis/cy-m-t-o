
#include "avlh.h"
#include "avl1.h"
 

void treat_h(Data_h e,FILE* out) {
    fprintf(out,"%d ",e.station);
    fprintf(out,"%d ",e.height);
    fprintf(out,"%f ",e.latitude);
    fprintf(out,"%f\n",e.longitude);
    if(e.duplicate[0]!=0){
        fprintf(out,"%d ",(int)e.duplicate[0]);
        fprintf(out,"%d ",e.height);
        fprintf(out,"%f ",e.duplicate[1]);
        fprintf(out,"%f\n",e.duplicate[2]);
    }
    if(e.duplicate2[0] !=0 ){
        fprintf(out,"%d ",(int)e.duplicate2[0]);
        fprintf(out,"%d ",e.height);
        fprintf(out,"%f ",e.duplicate2[1]);
        fprintf(out,"%f\n",e.duplicate2[2]);
    }
}

 

void infixPath_h(PAVL_H a, FILE* out) {
if (a!=NULL) {
    infixPath_h(a->fg,out);
    treat_h(a->elmt,out);
    free(a);
    infixPath_h(a->fd,out);
}
}

void infixPathR_h(PAVL_H a, FILE* out) {
if (a!=NULL) {
    infixPathR_h(a->fd,out); 
    treat_h(a->elmt,out);
    free(a);
    infixPathR_h(a->fg,out);
}
}




PAVL_H createTree_h(Data_h e){
    PAVL_H tree=NULL ;
    tree=(AVL_H *)malloc(sizeof(AVL_H));
    if(tree==NULL){
        exit(1);
    }
    tree->elmt=e;
    tree->elmt.duplicate[0]=0;
    tree->elmt.duplicate[1]=0;
    tree->elmt.duplicate[2]=0;
    tree->elmt.duplicate2[0]=0;
    tree->elmt.duplicate2[1]=0;
    tree->elmt.duplicate2[2]=0;

  
    tree->fg= NULL;
    tree->fd= NULL;
    tree->balance= 0;
    return tree;
}


PAVL_H LeftRotation_h(PAVL_H a){

 

    PAVL_H pivot=NULL; 
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

 

    PAVL_H RightRotation_h(PAVL_H a){

 

    PAVL_H pivot=NULL ;
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

 

PAVL_H doubleLeftRotation_h(PAVL_H a){

 

    a->fd = RightRotation_h(a->fd);
     return LeftRotation_h(a);
}

 

PAVL_H doubleRightRotation_h(PAVL_H a){
    a->fg = LeftRotation_h(a->fg);
     return RightRotation_h(a);
}

 

PAVL_H balanceAVL_h(PAVL_H a){

 

if (a->balance >=  2){
    if (a->fd->balance >= 0){
        return LeftRotation_h(a);
    }

    else return doubleLeftRotation_h(a);
}
else if (a->balance  <=  -2){ 
    if (a->fg->balance <= 0){
         return RightRotation_h(a);
    }

 

    else return doubleRightRotation_h(a);
}
return a;
}


PAVL_H insertionAVLHeight(PAVL_H a,Data_h e, int* h){

    if (a== NULL){
        *h=1;
        return createTree_h(e);
    }
    else if (e.height < a->elmt.height){
    a->fg=insertionAVLHeight(a->fg, e, h);
        *h =-*h; 
    }
    else if(e.height > a->elmt.height){
        a->fd=insertionAVLHeight(a->fd, e, h);
        
    }
    else{
        if(e.station!=a->elmt.station){
            if(e.station != a->elmt.duplicate[0] && a->elmt.duplicate[0] != 0 ){
                a->elmt.duplicate2[0]=e.station;
                a->elmt.duplicate2[1]=e.latitude;
                a->elmt.duplicate2[2]=e.longitude;
            }
            else{ a->elmt.duplicate[0]=e.station;
                a->elmt.duplicate[1]=e.latitude;
                a->elmt.duplicate[2]=e.longitude;
            }
        }
        *h=0;
        return a;
    }
    if (*h != 0){
        a->balance = a->balance + *h;
        a=balanceAVL_h(a);
        if (a->balance== 0){
            *h = 0;
        }
        else *h = 1;
    }
    
    return a;
    }

