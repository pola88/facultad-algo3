#ifndef __ITEM_H__
#define __ITEM_H__

#include "data.h"
#include "list.h"

typedef struct _Item {
    char* key; // key the elemento
    Data* value;
    LinkedList* linkList;
} Item;
/**@brief Funcion que inicia el item.
   @param item: Punntero al item que deceo iniciar.
   @param key: Puntero a la calve con la que quiero iniciar el item.
   @param vale: Puntero al valor con el que iniciar el item.
   @param size: Tama�o del item.**/
void item_init(Item* item, char* key, char* value, const size_t size);
/**@brief Funcion que inicia el valor de un item
   @param item: Puntero al item donde quiero iniciar el valor.
   @param value: Puntero al valor que quiero inicar.
   @param size: Tama�o del valor.**/
void item_setValue(Item* item, const char* value, const size_t size);
/**@brief Funcion que muestra el valor de un item por pantalla
   @param item: Punero a item que quiero mostrar por consola.**/
void item_showValue(Item* item);
/**@brief Funcion que agrega valor a un item.
   @param item: Puntero al item al cual yo quiero agregarle valor.
   @param value: Puntero al valor que quiero agregar.
   @param size: Tama�o del valor que quiero agregar.**/
int item_appendValue(Item* item, const char* value, const size_t size);
/**@brief Funcion que retorna el largo del valor de un item
   @param item: Puntero al item donde esta el valor a medir.
   @return largo del valor del item en int.**/
int item_getSize(Item* item);
/**@brief Funcion que libera la memoria alocada por el item que se le pasapor parametro.
   @param item: Puntero al item a liberar.**/
void item_free(Item* item);

/**@brief Funcion que inicia el item.
   @param item: Puntero al item que deceo iniciar.
   @param key: Puntero a la calve con la que quiero iniciar el item.
   @param vale: Puntero al valor con el que iniciar el item.
   @param linkList: Puntero a la lista donde se almacenan los valoras.
   @param size: Tama�o del item.**/
int item_initList(Item* item, char* key, char* value, const size_t size);

/**@brief Funcion que dada un Item y un dato, empuja el dato al frente de la lista desplasando
   el resto de los datos un posicion  para atras.
   @param Item: Puntero al item al que quiero hacer push.
   @param Data: Puntero al dato que quiero poner enfrente.
   @return Int: El largo total de la lista.*/
int item_push(Item* item, char* value, size_t size);
/**@brief Funcion que dado un Item retorna el primer elemento de su lista.
   @param item: Puntero al item donde se encuentra la lisa a hacer pop.
   @return Data: Puntero al elemento que se quito.*/
void item_pop(Item* item, Data* data);
/**@brief Funcion que dado un item retorna le largo de la lista que contiene.
   @param item: Puntero al itme donde se encuentra la lista a medir.
   @return Int: Largo de la lista que se midio.*/
int item_leng(Item* item);
/**@brief Funcion que dado un item muestra el contenido de su lista.
   @param item: Puntero al item donde esta la lista que quiero mostrar*/
void item_listGet(Item* item);

#endif
