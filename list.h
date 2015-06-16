#ifndef __LIST_H_
#define __LIST_H_

#include <stdlib.h>
#include "node.h"
#include "data.h"

// TODO: no se si con el back, querias poner
typedef struct _list{
    Node* front;
    Node* back;
    int nroCollection;
} LinkedList;

/**@brief Funcion que inicia la LinkedLista con un nodo con dato.
   @param LinkedList: Puntero a la lista que quiero iniciar.
   @param data: Puntero a la data que quiero iniciar.*/
int list_init(LinkedList* linkList, char* value, const size_t size);
/**@brief Funion que remueve un nodo que se le pasa por parametro.
   @param node: Puntero al nodo que quiero remover.*/
void list_removeNode(Node* node);
/**@brief Funcion que libera todo los recursos alocados en memoria de una lista.
   @param linklist: Punteor a la lista que quiero liberar.*/
void list_free(LinkedList* linklist);
/**@brief Funcion que dada una lista y un dato, crea un nuevo node con el dato
   empuja el resto una posicion para atras y colaca le nuevo node en la priemra
   posicion.
   @param linkList: Puntero a la lista a la que quiero hacer push.
   @param data: Puntero al dato que quiero poner enfrente.
   @return Int: El largo total de la lista.*/
int list_push(LinkedList* linkList, char* value, size_t size);
/**@brief Funcion que dada una lista le quita le perimer dato y lo retorna.
   @param linkList: Puntero a lalista que quiero hacer pop.
   @return Data: Puntero al elemento que se quito.*/
Data* list_pop(LinkedList* linkList);
/**@brief Funcion que dada una lista retorna el largo de la misma.
   @param linkList: Puntero a la lista que deceo medir.
   @return Int: Largo de la lista que se midio.*/
int list_leng(LinkedList* linkList);

#endif
