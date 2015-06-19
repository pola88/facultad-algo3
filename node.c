#include "node.h"
#include "data.h"

#include <stdlib.h>
#include <string.h>

/**@brief Funcion que inicia el nodo
   @param node: Puntero al node que quiero inicializar.
   @param out: Puntero al nodo anterior
   @param in: Puntero al nodod que sique
**/
void node_init(Node* node,Node* in, Node* out){
    node_setIn(node, in);
    node_setOut(node, out);
    node->value = (Data*) malloc(sizeof(Data));
}

/**@brief Funcion que permite setear un valor a un nodo.
   @param node: Puntero al nodo al cual yo quiero darle le valor.
   @param value: Puntero al valor que quiero darle al nodo.
   @param size: tamaño del valor
*/
void node_setValue(Node* node,const char* value,const size_t size) {
  data_init(node->value, value, size);
}

/**@brief Funcion que cambia el puntero a node por lo que se le pase por parametro
   @param node:Puntero al node donde queiro setiar.
   @param in: Puntero al node que quiero remplazar.**/
void node_setIn(Node* node, Node* in){
    node->in = in;
}
/**@brief Funcion que cambia el puntero al node siguiente por uno pasa por parametro
   @param Node: Puntero al node que quiero setiar.
   @param out: Puntero al node que queiro remplazar.**/
void node_setOut(Node* node, Node* out){
    node->out = out;
}

/**@brief Funcion que retorna el dato del nodo
   @param node: Puntero a node que tiene le dato que busco.
   @return data: el dato del nodo en caso de no tener dato retorna 0.**/
Data* node_getValue(Node* node){
    return node->value;
}
/**@brief Funcion que retorna un puntero al node siquiente.
   @param node: Puntero a node actual donde estoy.
   @return node: Puntero al nodo siguiente, en caso de no haber 0.**/
Node* node_getNext(Node* node){
    return (Node*)node->out;
}
/**@brief Funcion que retorna un puntero al nodo anterior.
   @param node: Puntero al node donde estoy parado.
   @return node: Puntero al nodo anterior.**/
Node* node_getBack(Node* node){
    return (Node*)node->in;
}

/**@brief Funcion que libera los recursos alocados en memoria de un nodo.
   @param node: Puntero al nodo qeu deceo liberar de la memoria.
*/
void node_free(Node* node) {
  data_free(node->value);
  node->in = NULL;
  node->out = NULL;
  free(node->value);
  node->value = 0;
}
