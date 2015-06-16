#include <string.h> //para usar memcpy
#include <stdlib.h> //Para user malloc
#include <stdio.h>

#include "list.h"
#include "item.h"
#include "data.h"

void item_setKey(Item* item, char* key) {
  size_t keyLength = strlen(key) + 1;
  item->key = malloc(keyLength);//Pido memoria para guardar la key
  memcpy(item->key, key, keyLength);//copio la key
}

/**@brief Funcion que inicia el item.
   @param item: Puntero al item que deceo iniciar.
   @param key: Puntero a la calve con la que quiero iniciar el item.
   @param vale: Puntero al valor con el que iniciar el item.
   @param size: Tama�o del item.**/
void item_init(Item* item, char* key, char* value, const size_t size) {
  item_setKey(item, key);

  item->value = (Data*) malloc(sizeof(Data));//pido memoria para almacenar el struct en el heap y parse el puntero a que apunte al struct
  data_init(item->value, value, size);
  item->linkList = 0;
}
/**@brief Funcion que inicia el valor de un item
   @param item: Puntero al item donde quiero iniciar el valor.
   @param value: Puntero al valor que quiero inicar.
   @param size: Tama�o del valor.**/
void item_setValue(Item* item, const char* value, const size_t size) {
  data_setValue(item->value, value, size);
}
/**@brief Funcion que muestra el valor de un item por pantalla
   @param item: Punero a item que quiero mostrar por consola.**/
void item_showValue(Item* item) {
  data_print(item->value);
}
/**@brief Funcion que agrega valor a un item.
   @param item: Puntero al item al cual yo quiero agregarle valor.
   @param value: Puntero al valor que quiero agregar.
   @param size: Tama�o del valor que quiero agregar.**/
int item_appendValue(Item* item, const char* value, const size_t size) {
  return data_append(item->value, value, size);
}
/**@brief Funcion que retorna el largo del valor de un item
   @param item: Puntero al item donde esta el valor a medir.
   @return largo del valor del item en int.**/
int item_getSize(Item* item) {
  return data_getSize(item->value);
}
/**@brief Funcion que libera la memoria alocada por el item que se le pasapor parametro.
   @param item: Puntero al item a liberar.**/
void item_free(Item* item){

  if(item->linkList){
    list_free(item->linkList);//revisar.
    free(item->linkList);
    item->linkList = 0;
  }

 else{
    data_free(item->value);
    free(item->value);
    item->value = 0;
  }
  printf("%s\n", item->key);
  free(item->key);
  item->key = 0;
}
/**@brief Funcion que inicia el item con una lista.
   @param item: Puntero al item que deceo iniciar.
   @param key: Puntero a la calve con la que quiero iniciar el item.
   @param vale: Puntero al valor con el que iniciar el item.
   @param size: Tama�o del item.**/
int item_initList(Item* item, char* key, char* value, const size_t size){
  item_setKey(item, key);

  item->linkList = (LinkedList*)malloc(sizeof(LinkedList));//pido memoria para almacenar el struct en el heap y parse el puntero a que apunte al struct
  item->value = 0;

  return list_init(item->linkList, value, size);
}
/**@brief Funcion que dada un Item y un dato, empuja el dato al frente de la lista desplasando
   el resto de los datos un posicion  para atras.
   @param Item: Puntero al item al que quiero hacer push.
   @param Data: Puntero al dato que quiero poner enfrente.
   @return Int: El largo total de la lista.*/
int item_push(Item* item, char* value, size_t size){
    return list_push(item->linkList, value, size);
}
/**@brief Funcion que dado un Item retorna el primer elemento de su lista.
   @param item: Puntero al item donde se encuentra la lisa a hacer pop.
   @return Data: Puntero al elemento que se quito.*/
void item_pop(Item* item, Data* data){
  list_pop(item->linkList, data);
}
/**@brief Funcion que dado un item retorna le largo de la lista que contiene.
   @param item: Puntero al itme donde se encuentra la lista a medir.
   @return Int: Largo de la lista que se midio.*/
int item_leng(Item* item){
    return list_leng(item->linkList);
}
/**@brief Funcion que dado un item retorna su lista.
   @param item: Puntero al item donde esta kla lista que quiero obtener
   @return LinkedList:Retorna la lista del item.*/
LinkedList* item_listGet(Item* item){
    return item->linkList;
}
