#include <stdio.h>
#include <stdlib.h>

#include "list.h"

typedef struct node node;

struct node {
    void * info;
    node * prox;
};


struct info{
    node * prim;
    node * ult;
    unsigned long long size;
};

struct funcs{
    void (*insert)(list* l, void * elem);
    void* (*remove)(list* l, void * key , int (*cmp)(void* elem, void * key));
    void (*free)(list* l);
    void (*print)(list* l , void (*printElem)(void * elem));
};



static void atribui_funcs(list* l){
    static const struct funcs;

   
}


list* init_lista(void){


    list* l = (list*)calloc(1,sizeof(list));
    info* i = (info*)calloc(1,sizeof(info));

    i->prim = NULL;
    i->size=0;
    i->ult = NULL;

    l->info = i;


}





