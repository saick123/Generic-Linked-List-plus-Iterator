#ifndef LIST_H
#define LISTA_H

typedef struct list list;
typedef struct ListIterator ListIterator;
typedef struct info info;

struct list{
    info* ListInfo;
    void (*insert)(list* l, void * elem);
    void* (*remove)(list* l, void * key , int (*cmp)(void* elem, void * key));
    void (*free)(list* l);
    void (*print)(list* l , void (*printElem)(void * elem));
    ListIterator* (*iter)(list* l);
};



list* init_lista(void);

int advanceListIterator(ListIterator* it, long int delta);
void * getListIterator(ListIterator* it );
void resetListIterator(ListIterator* it);
int itsEndListIterator(ListIterator* it);
int itsBeginListIterator(ListIterator* it);

#endif