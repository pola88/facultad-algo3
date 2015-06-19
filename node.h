#ifndef __NODE_H_
#define __NODE_H_

#include "data.h"

typedef struct _node{
    void* in; // El nodo anterior
    void* out; // El nodo siquiente.
    Data* value;
} Node;
/**@brief Funcion que inicia el nodo
   @param node: Puntero al node que quiero inicializar.
   @param out: Puntero al nodo anterior
   @param in: Puntero al nodod que sique
   @param value: Punetro al data que almacena el nodo**/
void node_init(Node* node, Node* in, Node* out);
/**@brief Funcion que cambia el puntero a node por lo que se le pase por parametro
   @param node:Puntero al node donde queiro setiar.
   @param in: Puntero al node que quiero remplazar.**/
void node_setIn(Node* node, Node* in);
/**@brief Funcion que cambia el puntero al node siguiente por uno pasa por parametro
   @param Node: Puntero al node que quiero setiar.
   @param out: Puntero al node que queiro remplazar.**/
void node_setOut(Node* node, Node* out);
/**@brief Funcion que retorna el dato del nodo
   @param node: Puntero a node que tiene le dato que busco.
   @return data: el dato del nodo en caso de no tener dato retorna 0.**/
Data* node_getValue(Node* node);
/**@brief Funcion que retorna un puntero al node siquiente.
   @param node: Puntero a node actual donde estoy.
   @return node: Puntero al nodo siguiente, en caso de no haber 0.**/
Node* node_getNext(Node* node);
/**@brief Funcion que retorna un puntero al nodo anterior.
   @param node: Puntero al node donde estoy parado.
   @return node: Puntero al nodo anterior.**/
Node* node_getBack(Node* node);
/**@brief Funcion que libera los recursos alocados en memoria por el node.
   @param node: Puntero al node que quiero liberar.*/
void node_free(Node* node);

/**@brief Funcion que permite setear un valor a un nodo.
   @param node: Puntero al nodo al cual yo quiero darle le valor.
   @param value: Puntero al valor que quiero darle al nodo.
   @param size: tamaño del valor
*/
void node_setValue(Node* node,const char* value,const size_t size);
#endif // __NODE_H_
