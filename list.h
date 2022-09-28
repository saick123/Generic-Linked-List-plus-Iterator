#ifndef LIST_H
#define LISTA_H

typedef struct list list;


typedef struct info info;

struct list{
    info* info;
    void (*insert)(list* l, void * elem);
    void* (*remove)(list* l, void * key , int (*cmp)(void* elem, void * key));
    void (*free)(list* l);
    void (*print)(list* l , void (*printElem)(void * elem));
};



list* init_lista(void);


#endif