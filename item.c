#include <string.h> //para usar memcpy
#include <stdlib.h> //Para user malloc

#include "list.h"
#include "item.h"
#include "data.h"

void setKey(Item* item, char* key) {
  size_t keyLength = strlen(key) + 1;
  item->key = malloc(keyLength);//Pido memoria para guardar la key
  memcpy(item->key, key, keyLength);//copio la key
}

/**@brief Funcion que inicia el item.
   @param item: Puntero al item que deceo iniciar.
   @param key: Puntero a la calve con la que quiero iniciar el item.
   @param vale: Puntero al valor con el que iniciar el item.
   @param size: Tama�o del item.**/
void initItem(Item* item, char* key, char* value, const size_t size) {
  setKey(item, key);

  item->value = (Data*) malloc(sizeof(Data));//pido memoria para almacenar el struct en el heap y parse el puntero a que apunte al struct
  dataInit(item->value, value, size);
}
/**@brief Funcion que inicia el valor de un item
   @param item: Puntero al item donde quiero iniciar el valor.
   @param value: Puntero al valor que quiero inicar.
   @param size: Tama�o del valor.**/
void setItemValue(Item* item, const char* value, const size_t size) {
  setValue(item->value, value, size);
}
/**@brief Funcion que muestra el valor de un item por pantalla
   @param item: Punero a item que quiero mostrar por consola.**/
void showItemValue(Item* item) {
  printf("%s\n", item->key);
  printData(item->value);
}
/**@brief Funcion que agrega valor a un item.
   @param item: Puntero al item al cual yo quiero agregarle valor.
   @param value: Puntero al valor que quiero agregar.
   @param size: Tama�o del valor que quiero agregar.**/
int appendValueToItem(Item* item, const char* value, const size_t size) {
  return appendData(item->value, value, size);
}
/**@brief Funcion que retorna el largo del valor de un item
   @param item: Puntero al item donde esta el valor a medir.
   @return largo del valor del item en int.**/
int getSize(Item* item) {
  return getDataSize(item->value);
}

/**@brief Funcion que libera la memoria alocada por el item que se le pasapor parametro.
   @param item: Puntero al item a liberar.**/
void freeItem(Item* item){
  if (sizeof(item->value) > (sizeof(Data))){
    freeList((item->value));
  }
  else{
    freeData(item->value);
  }
  free(item->key);
  item->key = 0;
  free(item->value);
  item->value = 0;
}

//funciones agregadas por Ale FINAL

//Lo programo un tipo mas.
//TODO: lo cambie!
/**@brief Funcion que inicia el item con una lista.
   @param item: Puntero al item que deceo iniciar.
   @param key: Puntero a la calve con la que quiero iniciar el item.
   @param vale: Puntero al valor con el que iniciar el item.
   @param size: Tama�o del item.**/
int initListItem(Item* item, char* key, char* value, const size_t size){
  setKey(item, key);

  item->linkList = (LinkedList*)malloc(sizeof(LinkedList));//pido memoria para almacenar el struct en el heap y parse el puntero a que apunte al struct
  return initList(item->linkList, value, size);
}


//TODO: recibe el nuevo valor y el tamaño.
/**@brief Funcion que dada un Item y un dato, empuja el dato al frente de la lista desplasando
   el resto de los datos un posicion  para atras.
   @param Item: Puntero al item al que quiero hacer push.
   @param Data: Puntero al dato que quiero poner enfrente.
   @return Int: El largo total de la lista.*/
int Ipush(Item* item, char* value, size_t size){
    return push(item->linkList, value, size);
}
/**@brief Funcion que dado un Item retorna el primer elemento de su lista.
   @param item: Puntero al item donde se encuentra la lisa a hacer pop.
   @return Data: Puntero al elemento que se quito.*/
Data* Ipop(Item* item){
    return pop(item->linkList);
}
/**@brief Funcion que dado un item retorna le largo de la lista que contiene.
   @param item: Puntero al itme donde se encuentra la lista a medir.
   @return Int: Largo de la lista que se midio.*/
int Ileng(Item* item){
    return leng(item->linkList);
}
/**@brief Funcion que dado un item retorna su lista.
   @param item: Puntero al item donde esta kla lista que quiero obtener
   @return LinkedList:Retorna la lista del item.*/
LinkedList* IlistGet(Item* item){
    return item->linkList;
}
