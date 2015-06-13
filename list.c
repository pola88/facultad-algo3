#include <stdlib.h>
#include "list.h"
#include "node.h"
#include "data.h"

#define NroCollectionDefault 1

//TODO: lo cambie, no recibe el dato..sino inicialia los punteros, el item le asigna el dato
//nose si el back deberia ser 0, o el mismo node;
/**@brief Funcion que inicia la LinkedLista con un nodo con dato.
   @param LinkedList: Puntero a la lista que quiero iniciar.
   @param data: Puntero a la data que quiero iniciar.*/
int initList(LinkedList* linkList, char* value, size_t size){
  // linkList->front = newNode(linkList->front,linkList->back);
  linkList->front = (Node*)malloc(sizeof(Node));
  // linkList->back = (Node*)malloc(sizeof(Node));

  initNode(linkList->front, 0, 0);
  setValueToNode(linkList->front, value, size);

  //el prinicpio es el fin
  linkList->back = linkList->front;

  linkList->nroCollection = NroCollectionDefault;

  return linkList->nroCollection;
}

//TODO: Lo borre, no me convence la idea de que la lista, inicialice el valor.
// Data* newData(const char* value, const size_t size){
//
//     return data;
// }

//TODO: No creo q lo necesitemos, esto seria el initNode
//
/**@brief Funcion que creo un nuevo nodo con un dato que se le pasa por parametro.
   @param data: Puntero al dato con el que queiro inciar el node.
   @return Un puntero al nodo nuevo.*/
// Node* newNode(Node* in, Node* out){
//     Node node;
//     Node* pNode = node;
//
//     pNode->in = in;
//     pNode->out = out;
//     pNode->value = (Data*)malloc(sizeof(Data));//pido memoria para almacenar el struct en el heap y parse el puntero a que apunte al struct
//     // pNode->value = malloc(data->size);
//     // memccpy(pNode->value,data,data->size);
//
//     return pNode;
// }
/**@brief Funion que remueve un nodo que se le pasa por parametro.
   @param node: Puntero al nodo que quiero remover.*/
void removeNode(Node* node){
    //Tomo los puntero que rodean al node.
    Node* back = node->out;
    Node* front = node->in;
    //libero la memoria del node que quiero eliminar.
    freeNode(node);
    //conecto los node que se conectavan con el viejo node eliminado.
    setOut(front,back);
}
/**@brief Funcion que libera todo los recursos alocados en memoria de una lista.
   @param linklist: Punteor a la lista que quiero liberar.*/
void freeList(LinkedList* linklist){
    int siez = linklist->nroCollection;
    int i;
    for(i=0;i<siez;i++){
        freeData((Data*) pop(linklist));
    }
    free(linklist->front);
}

//TODO: lo inicializo con el initNode y le asigno el valor.
/**@brief Funcion que dada una lista y un dato, crea un nuevo node con el dato
   empuja el resto una posicion para atras y colaca le nuevo node en la priemra
   posicion.
   @param linkList: Puntero a la lista a la que quiero hacer push.
   @param data: Puntero al dato que quiero poner enfrente.
   @return Int: El largo total de la lista.*/
int push(LinkedList* linkList, char* value, size_t size){
    //creo el nuevo nodo con la data que se me especifica
    // Node* newNode = newNode(data);

    Node* newNode = (Node*) malloc(sizeof(Node));
    initNode(newNode,0, linkList->front);
    setValueToNode(newNode, value, size);

    //tomo el primer nodo de la lista.
    Node* front = linkList->front;
    //le asigno el nuevo nodo que creo enfrente.
    setIn(front,newNode);
    //al frente de la lista le asigno el nuevo nodo
    linkList->front = newNode;
    //aumento la cantidad de nodos en la lista y lo retorno.
    linkList->nroCollection++;

    return linkList->nroCollection;
}
/**@brief Funcion que dada una lista le quita le perimer dato y lo retorna.
   @param linkList: Puntero a lalista que quiero hacer pop.
   @return Data: Puntero al elemento que se quito.*/
Data* pop(LinkedList* linkList){
    Node* oldFront = linkList->front;
    Node* newFront = getNext(linkList->front);
    linkList->front = newFront;
    setIn(newFront,NULL);
    linkList->nroCollection--;
    //al devolver Data, descarto el Nodo.
    Data* aux = (Data*) malloc(sizeof(Data));
    aux = getValue(oldFront);
    freeNode(oldFront);
    return aux;
}
/**@brief Funcion que dada una lista retorna el largo de la misma.
   @param linkList: Puntero a la lista que deceo medir.
   @return Int: Largo de la lista que se midio.*/
int leng(LinkedList* linkList){
  return linkList->nroCollection;
}
