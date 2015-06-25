#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#include "list.h"
#include "node.h"
#include "data.h"

#define NroCollectionDefault 1

/**@brief Funcion que inicia la LinkedLista con un nodo con dato.
   @param LinkedList: Puntero a la lista que quiero iniciar.
   @param data: Puntero a la data que quiero iniciar.*/
int list_init(LinkedList* linkList,const char* value,const size_t size){
  linkList->front = (Node*)malloc(sizeof(Node));

  node_init(linkList->front, 0, 0);
  node_setValue(linkList->front, value, size);
  linkList->back = linkList->front;

  linkList->nroCollection = NroCollectionDefault;

  return linkList->nroCollection;
}

/**@brief Funion que remueve un nodo que se le pasa por parametro.
   @param node: Puntero al nodo que quiero remover.*/
void list_removeNode(Node* node){

    Node* back = node->out;
    Node* front = node->in;

    node_free(node);

    node_setOut(front,back);
}

/**@brief Funcion que libera todo los recursos alocados en memoria de una lista.
   @param linklist: Punteor a la lista que quiero liberar.*/
void list_free(LinkedList* linklist){

    int size = linklist->nroCollection;
    int i;
    for(i=0; i < size; i++){
      Data aux;
      data_init(&aux, "",0);
      list_pop(linklist, &aux);
      data_free(&aux);
    }

    free(linklist->front);
    linklist->front = 0;
    free(linklist->back);
    linklist->back = 0;

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

    Node* front = linkList->front;

    node_setOut(front,newNode);

    linkList->front = newNode;

    linkList->nroCollection++;

    return linkList->nroCollection;
}

/**@brief Funcion que dada una lista le quita le perimer dato y lo retorna.
   @param linkList: Puntero a lalista que quiero hacer pop.
   @return Data: Puntero al elemento que se quito.*/
void list_pop(LinkedList* linkList, Data* data){

    if (linkList->nroCollection == 0) {
      data_init(data, "",0);
      return;
    }
    Node* oldFront = linkList->front;
    if(linkList->nroCollection > 1) {
      Node* newFront = node_getNext(oldFront);
      linkList->front = newFront;
      node_setIn(newFront,0);
    } else {
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

void list_get(LinkedList* linkList){
 if (linkList->nroCollection == 0) {
      printf("lista vacia");
    }else{
     Node* nodeAux = linkList->front;
     int nroCollectionAux = 0;
     while (nroCollectionAux < linkList->nroCollection) {
       Data* aux = node_getValue(nodeAux);
       printf("numero iteracion %i\n", nroCollectionAux);
       data_print(aux);
       nodeAux = node_getNext(nodeAux);
       nroCollectionAux++;
     }
    }

}
