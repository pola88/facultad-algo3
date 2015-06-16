#include <stdlib.h>
#include <stdio.h>

#include "list.h"
#include "node.h"
#include "data.h"

#define NroCollectionDefault 1

//nose si el back deberia ser 0, o el mismo node;
/**@brief Funcion que inicia la LinkedLista con un nodo con dato.
   @param LinkedList: Puntero a la lista que quiero iniciar.
   @param data: Puntero a la data que quiero iniciar.*/
int list_init(LinkedList* linkList,const char* value,const size_t size){
  linkList->front = (Node*)malloc(sizeof(Node));

  node_init(linkList->front, 0, 0);
  node_setValue(linkList->front, value, size);
  //el prinicpio es el fin
  linkList->back = linkList->front;

  linkList->nroCollection = NroCollectionDefault;

  return linkList->nroCollection;
}

/**@brief Funion que remueve un nodo que se le pasa por parametro.
   @param node: Puntero al nodo que quiero remover.*/
void list_removeNode(Node* node){
    //Tomo los puntero que rodean al node.
    Node* back = node->out;
    Node* front = node->in;
    //libero la memoria del node que quiero eliminar.
    node_free(node);
    //conecto los node que se conectavan con el viejo node eliminado.
    node_setOut(front,back);
}
/**@brief Funcion que libera todo los recursos alocados en memoria de una lista.
   @param linklist: Punteor a la lista que quiero liberar.*/
void list_free(LinkedList* linklist){
    int size = linklist->nroCollection;
    int i;
    //TODO: change this
    for(i=0; i < (size-1); i++){
      Data* aux = NULL;
      list_pop(linklist, aux);
      data_print(aux);
      data_free(aux);
    }

    free(linklist->front);
    linklist->front = 0;
}

/**@brief Funcion que dada una lista y un dato, crea un nuevo node con el dato
   empuja el resto una posicion para atras y colaca le nuevo node en la priemra
   posicion.
   @param linkList: Puntero a la lista a la que quiero hacer push.
   @param data: Puntero al dato que quiero poner enfrente.
   @return Int: El largo total de la lista.*/
int list_push(LinkedList* linkList, const char* value, const size_t size){
    Node* newNode = (Node*)malloc(sizeof(Node));

    node_init(newNode,0, linkList->front);
    node_setValue(newNode, value, size);

    //tomo el primer nodo de la lista.
    Node* front = linkList->front;
    //le asigno el nuevo nodo que creo enfrente.
    node_setOut(front,newNode);

    //al frente de la lista le asigno el nuevo nodo
    linkList->front = newNode;
    //aumento la cantidad de nodos en la lista y lo retorno.
    linkList->nroCollection++;

    return linkList->nroCollection;
}
/**@brief Funcion que dada una lista le quita le perimer dato y lo retorna.
   @param linkList: Puntero a lalista que quiero hacer pop.
   @return Data: Puntero al elemento que se quito.*/
void list_pop(LinkedList* linkList, Data* data){
    Node* oldFront = linkList->front;

    //Si tiene un solo elemento, no hay q setear el nuevo front.
    if(linkList->nroCollection > 1) {
      Node* newFront = node_getNext(oldFront);
      linkList->front = newFront;
      node_setIn(newFront, 0);
    } else {
      //No se si hay q liberarla
      linkList->front = 0;
    }

    Data* aux = node_getValue(oldFront);
    data_copy(data, aux);
    node_free(oldFront);

    linkList->nroCollection--;
}
/**@brief Funcion que dada una lista retorna el largo de la misma.
   @param linkList: Puntero a la lista que deceo medir.
   @return Int: Largo de la lista que se midio.*/
int list_leng(LinkedList* linkList){
  return linkList->nroCollection;
}
