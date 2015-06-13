#include "node.h"
#include "data.h"


#include <stdlib.h>
#include <string.h>

/**@brief Funcion que inicia el nodo
   @param node: Puntero al node que quiero inicializar.
   @param out: Puntero al nodo anterior
   @param in: Puntero al nodod que sique
**/
void initNode(Node* node,Node* out,Node* in){
    setIn(node, in);
    setOut(node, out);
    node->value = (Data*) malloc(sizeof(Data));
}

//TODO: se encarga de setear el valor al node
void setValueToNode(Node* node, char* value, size_t size) {
  dataInit(node->value, value, size);
}

/**@brief Funcion que cambia el puntero a node por lo que se le pase por parametro
   @param node:Puntero al node donde queiro setiar.
   @param in: Puntero al node que quiero remplazar.**/
void setIn(Node* node, Node* in){
    node->in = in;
}
/**@brief Funcion que cambia el puntero al node siguiente por uno pasa por parametro
   @param Node: Puntero al node que quiero setiar.
   @param out: Puntero al node que queiro remplazar.**/
void setOut(Node* node, Node* out){
    node->out = out;
}

// TODO: debe retornar el Data
/**@brief Funcion que retorna el dato del nodo
   @param node: Puntero a node que tiene le dato que busco.
   @return data: el dato del nodo en caso de no tener dato retorna 0.**/
Data* getValue(Node* node){
    return node->value;
}
/**@brief Funcion que retorna un puntero al node siquiente.
   @param node: Puntero a node actual donde estoy.
   @return node: Puntero al nodo siguiente, en caso de no haber 0.**/
Node* getNext(Node* node){
    return node->out;
}
/**@brief Funcion que retorna un puntero al nodo anterior.
   @param node: Puntero al node donde estoy parado.
   @return node: Puntero al nodo anterior.**/
Node* getBack(Node* node){
    return node->in;
}

//TODO: hacer algo!!
void freeNode(Node* node) {
  freeData(node->value);
  free(node->value);
  node->value = 0;
}

