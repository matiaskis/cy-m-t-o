#include "avl1.h"
#include "avlM.h"



void treat_m(int count,Data_m e,FILE* out) {
    fprintf(out,"%d ",e.station);
    fprintf(out,"%f ",e.latitude);
    fprintf(out,"%f ",e.longitude);
    fprintf(out,"%d\n",e.moisture);
   
    for(int i=0; i < count; i++ ){
        fprintf(out,"%d ",(int)e.duplicates[i]);
        fprintf(out,"%f ",e.duplicatela[i]);
        fprintf(out,"%f ",e.duplicatelo[i]);
        fprintf(out,"%d\n",e.moisture);
    }
      
    
  
}
void treat_m2(Data_m e,FILE* out) {
    fprintf(out,"%d;",e.station);
    fprintf(out,"%d;",e.moisture);
    fprintf(out,"%f,",e.latitude);
    fprintf(out,"%f\n",e.longitude);
}
 

void infixPath_m(PAVL_m a, FILE* out) {
if (a!=NULL) {
    infixPath_m(a->fg,out);
    treat_m(a->elmt.counter,a->elmt,out);
    free(a);
    infixPath_m(a->fd,out);
}
}

void infixPathR_m(PAVL_m a, FILE* out) {
if (a!=NULL) {
    infixPathR_m(a->fd,out); 
    treat_m(a->elmt.counter,a->elmt,out);
    free(a);
    infixPathR_m(a->fg,out);
}
}

void infixPath_m2(PAVL_m a, FILE* out) {
if (a!=NULL) {
    infixPath_m2(a->fg,out);
    treat_m2(a->elmt,out);
    free(a);
    infixPath_m2(a->fd,out);
}
}

void infixPathR_m2(PAVL_m a, FILE* out) {
if (a!=NULL) {
    infixPathR_m2(a->fd,out); 
    treat_m2(a->elmt,out);
    free(a);
    infixPathR_m2(a->fg,out);
}
}




PAVL_m createTree_m(Data_m e){
    PAVL_m tree=NULL ;
    tree=malloc(sizeof(AVL_m));
    if(tree==NULL){
        exit(1);
    }
    tree->elmt=e;
    tree->elmt.counter=0;
    tree->fg= NULL;
    tree->fd= NULL;
    tree->balance= 0;
    return tree;
}


PAVL_m LeftRotation_m(PAVL_m a){

 

    PAVL_m pivot=NULL; 
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

 

    PAVL_m RightRotation_m(PAVL_m a){

 

    PAVL_m pivot=NULL ;
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

 

PAVL_m doubleLeftRotation_m(PAVL_m a){

 

    a->fd = RightRotation_m(a->fd);
     return LeftRotation_m(a);
}

 

PAVL_m doubleRightRotation_m(PAVL_m a){
    a->fg = LeftRotation_m(a->fg);
     return RightRotation_m(a);
}

 

PAVL_m balanceAVL_m(PAVL_m a){

 

if (a->balance >=  2){
    if (a->fd->balance >= 0){
        return LeftRotation_m(a);
    }

    else return doubleLeftRotation_m(a);
}
else if (a->balance  <=  -2){ 
    if (a->fg->balance <= 0){
         return RightRotation_m(a);
    }

 

    else return doubleRightRotation_m(a);
}
return a;
}


PAVL_m insertionAVLMMax(PAVL_m a,Data_m e, int* h){

    if (a== NULL){
        *h=1;
        return createTree_m(e);
    }
    else if (e.station < a->elmt.station){
    a->fg=insertionAVLMMax(a->fg, e, h);
        *h =-*h; 
    }
    else if(e.station > a->elmt.station){
        a->fd=insertionAVLMMax(a->fd, e, h);
        
    }
    else{
        if(e.moisture > a->elmt.moisture){
            a->elmt.moisture=e.moisture;
        }
        *h=0;
        return a;
    }
    if (*h != 0){
        a->balance = a->balance + *h;
        a=balanceAVL_m(a);
        if (a->balance== 0){
            *h = 0;
        }
        else *h = 1;
    }
    
    return a;
    }

PAVL_m insertionAVLM(PAVL_m a,Data_m e, int* h){

    if (a== NULL){
        *h=1;
       
        return createTree_m(e);
    }
    else if (e.moisture < a->elmt.moisture ){
    a->fg=insertionAVLM(a->fg, e, h);
        *h =-*h; 
    }
    else if(e.moisture > a->elmt.moisture ){
        a->fd=insertionAVLM(a->fd, e, h);
        
    }
    else{
        a->elmt.duplicates[a->elmt.counter]=e.station;
        a->elmt.duplicatela[a->elmt.counter]=e.latitude;
        a->elmt.duplicatelo[a->elmt.counter]=e.longitude;
        a->elmt.counter=a->elmt.counter+1;
                  
        
        *h=0;
        return a;


    }
    if (*h != 0){
        a->balance = a->balance + *h;
        a=balanceAVL_m(a);
        if (a->balance== 0){
            *h = 0;
        }
        else *h = 1;
    }
    
    return a;
    }


