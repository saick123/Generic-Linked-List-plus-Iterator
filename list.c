#include <stdio.h>
#include <stdlib.h>

#include "list.h"

typedef struct node node;


// headers 

static void _insert(list* l ,void * elem);
static void* _remove(list * l, void * key, int (*cmp)(void * elem, void * key));
static void _free(list* l);
static void _print(list* l, void (*printElem)(void  * elem));
static ListIterator* _iter(list* l);

static void _cria_iterador(list* l);


struct node {
    void * info;
    node * prox;
    node * ant;
};


struct info{
    node * prim;
    node * ult;
    ListIterator* it;
    unsigned long long size;
};

struct ListIterator{
    list* l;
    node * atual;
};

struct funcs{
    void (*insert)(list* l, void * elem);
    void* (*remove)(list* l, void * key , int (*cmp)(void* elem, void * key));
    void (*free)(list* l);
    void (*print)(list* l , void (*printElem)(void * elem));
    ListIterator* (*iter)(list* l);
};



static void atribui_funcs(list* l){
    const static struct funcs  foos= {
        _insert,
        _remove,
        _free,
        _print,
        _iter,

    };

   
    l->insert = foos.insert;
    l->remove = foos.remove;
    l->free =foos.free;
    l->print = foos.print;
    l->iter = foos.iter;

    return;
}


list* init_lista(void){


    list* l = (list*)calloc(1,sizeof(list));
    info* i = (info*)calloc(1,sizeof(info));

    i->prim = NULL;
    i->size=0;
    i->ult = NULL;

    l->ListInfo = i;

    atribui_funcs(l);

    _cria_iterador(l);

    
    return l;

}


static void _insert(list* l ,void * elem){
    node * n = (node*)malloc(sizeof(node));
    n->info = elem;
    n->prox = l->ListInfo->prim;
    n->ant = NULL;

    if(l->ListInfo->ult == NULL){
        l->ListInfo->ult = n;
    }else{
        l->ListInfo->prim->ant = n;
    }

    l->ListInfo->prim = n;

    l->ListInfo->size++;

    return;

}

static void* _remove(list * l, void * key, int (*cmp)(void * elem, void * key)){

    if(l->ListInfo->size ==0 ){
        return NULL;
    }

    node * aux = l->ListInfo->prim, * ant = NULL;

    while(aux){
        if(cmp(aux->info, key) == 1 ){
            break;
        }
        ant = aux;
        aux = aux->prox;
    }

    if(aux == NULL){
        return NULL;
    }

    void * ret  = aux->info;
    node * substituto = NULL;

    if(aux == l->ListInfo->prim && aux == l->ListInfo->ult){

        l->ListInfo->prim = l->ListInfo->ult = NULL;

    } else if (aux == l->ListInfo->prim){

        l->ListInfo->prim = aux->prox;
        substituto = aux->prox;

    } else if (aux == l->ListInfo->ult){

        l->ListInfo->ult = ant;
        substituto = aux->ant;

    } else{

        ant->prox = aux->prox;
        substituto = aux->ant;
    }

    if(l->ListInfo->it->atual == aux){
        l->ListInfo->it->atual = substituto;
    }

    free(aux);

    l->ListInfo->size --;

    return ret; 

}


static void _free(list* l){
    node * aux = l->ListInfo->prim, * ant  = NULL;

    while(aux){
        ant = aux;
        aux = aux->prox;
        free(ant);
    }
    free(l->ListInfo->it);
    free(l->ListInfo);
    free(l);
    return;

}


static void _print(list* l, void (*printElem)(void  * elem)){
    printf("[ ");
    node * aux = l->ListInfo->prim;

    while(aux){
        printElem(aux->info);
        aux= aux->prox;
    }

    printf("]");

    return;

}

static ListIterator* _iter(list* l){
    if(l->ListInfo->it->atual == NULL)  l->ListInfo->it->atual = l->ListInfo->prim;
    return l->ListInfo->it;
}

static void _cria_iterador(list* l){
    ListIterator * it = (ListIterator*)malloc(sizeof(ListIterator));
    it->atual = NULL;
    it->l = l;
    l->ListInfo->it = it;
    return;
}


static int  avancaIterador(ListIterator* it){
    if(it->atual == it->l->ListInfo->ult || it->l->ListInfo->size == 0 ){
        return 1 ;
    }
    it->atual = it->atual->prox;
    return 0;
}

static int  retrocedeIterador(ListIterator* it){
    if(it->atual == it->l->ListInfo->prim || it->l->ListInfo->size == 0 ){
        return 1;
    }
    it->atual = it->atual->ant;
    return 0;
}

int advanceListIterator(ListIterator* it, long int delta){
    int (*foo)(ListIterator * it);
    if(it->atual == NULL) return -1;

    if(delta < 0){
        foo = retrocedeIterador;
    }else if (delta > 0){
        foo = avancaIterador;
    }else{
        return 1;
    }

    int result = 0;
    for(long int i =0; i < delta; i ++){
        if(foo(it) == 1){
            result =1;
            break;
        }
    }

    if(result) return -1;
    return 1;
}

void * getListIterator(ListIterator* it ){
    if(it->atual == NULL) return NULL;
    return it->atual->info;
}

void resetListIterator(ListIterator* it){
    it->atual = it->l->ListInfo->prim;
}
int itsEndListIterator(ListIterator* it){
    return (it->atual == it->l->ListInfo->ult) ? 1 : 0;
}
int itsBeginListIterator(ListIterator* it){
    return (it->atual == it->l->ListInfo->prim) ? 1 : 0;
}
