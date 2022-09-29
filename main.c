#include <stdio.h>
#include <stdlib.h>
#include "list.h"

void insere_inteiro(list * l, int n ){
    int * i = (int*)malloc(sizeof(int));
    *i = n;
    l->insert(l, (void*)i);
    return;
}

int remove_inteiro(list* l, int key , int (*cmp)(void* elem, void * key)){

    int * ptr = (int*)l->remove(l, &key, cmp);
    int retorno = *ptr; 
    free(ptr);
    
    return retorno;
}

void printa_inteiro(void * elem){
    printf("%d ",  *((int*)elem));
}

int compara_inteiro(void * key, void * elem){
    return (*((int*)(key)) == *((int*)elem)) ? 1 : -1;
}


#define TAM 5

int main(void){
    list* l = init_lista();

    for(int i =0; i< TAM; i ++){
        insere_inteiro(l, i + 1 );
    }
    l->print(l, printa_inteiro);

    ListIterator * it = l->iter(l);

    for(resetListIterator(it); itsEndListIterator(it) == 0; advanceListIterator(it, 1 )){
        printa_inteiro((int*)getListIterator(it));
    }
   
    
    remove_inteiro(l, 1, compara_inteiro );
    remove_inteiro(l, 3, compara_inteiro );
    remove_inteiro(l, 5, compara_inteiro );
    remove_inteiro(l, 2, compara_inteiro );
    remove_inteiro(l, 4, compara_inteiro );

    l->free(l);
   
    return 0;
}