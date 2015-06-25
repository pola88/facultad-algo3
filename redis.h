#ifndef __REDIS_H__
#define __REDIS_H__

#include "item.h"
#include "list.h"

typedef struct _Redis {
    int total;
    void* values;
} Redis;

/**@brief Funcion para iniciar el Redis
   @param redis: Puntero al redis que deceo inicializar
   **/
void redis_init(Redis* redis);

/**@brief Funcion para crear un nuevo item dentro del Redis
   @param redis: Puntero al redis donde voy a guardar el Item
   @param key: Puntero a la clave que identifica al nuevo item
   @param value: Puntero al valor que contiene el item a crear
   @param size: Tama�o del nuevo item a crear
   **/
void redis_createItem(Redis* redis, char* key, char* value, const size_t size);

/**@brief Funcion que inicia el valor de un Item.
   @param redis: Puntero al redis donde se encuentra el item.
   @param key: Puntero a la clave que accede al Item.
   @param valu: Puntero al valor que se decea iniciar en el item.
   @param size: Tama�o del valor que se decea iniciar en el item.
   **/
void redis_set(Redis* redis, char* key, char* value, const size_t size);

/**@brief Funcion que mediante una clave retorna.
   @return Item: El valor correspondiente a la clave.
   @return 0 si el redis es null o si la clave no existe
   @param redis: Puntero al redis donde esta el item a retornar.
   @param key: Puntero a la clave que accede al Item.
   **/
Item* __redis_get(Redis* redis, char* key);

/**@brief Funcion comprueba la existencia de una clave.
   @param redis: Puntero a redis donde creeo que esta la clave
   @param key:Puntero a la clave que quiero probar.
   @return 0: Si no existe.
   @return 1: Si existe.
   **/
int redis_exists(Redis* redis, char* key);

/**@brief Funcion que imprime el largo de un valor encontrado por medio de una clave dada
   @param redis: Puntero al redis donde se encuentra el valor.
   @param key: Puntero a la clave que accede al valor.
   **/
void redis_strlen(Redis* redis, char* key);

/**@brief Funcion que concatena valor a un valor ya existente, si no existe lo crea.
   @param redis: Puntero al redis donde se encuentra el Item con el valor.
   @param key: Puntero a la calve que accede al valor.
   @param value: Puntero al valor que deceo concatenar.
   @param size: Tama�o de mi valor.
   @return El largo de mi valor.
    **/
int redis_append(Redis* redis, char* key, char* value, const size_t size);

/**@brief Funcion para liberar la memoria alocada por todos los recursos que utiliza el objeto
          redis que se le pasa por parametro.
    @param redis: Puntero a redis que quiero liberar de la memoria.
**/
void redis_free(Redis* redis);

/**@brief Funcion que muestra el contenido de los redis en consola.
    @param redis: Puntero a redis con el contenido que deseo ver en consola.
**/
void redis_addItem(Redis* redis, Item* item);

/**@brief Funcion que muestra las keys de un redis por pantalla.
   @param redis: Puntero al redis que contiene las keys que deceo ver.
*/
void redis_show(Redis* redis);

/**@brief Funcion que dado una calve, crea un nuevo nodo y empujar el resto para atras,
    dejando a ese nodo primero y luego le inserta a ese nodo nuevo el valor de la clave.
    @param redis: Puntero a redis donde esta el valor a empujar.
    @param key: Puntero a la clave que accede al valor.
    @return El largo total de la lista.*/
int redis_lPush(Redis* redis, char* key, char* value, size_t size);

/**@brief Funcion que dada una lista le quita el primer elemento y lo devuelve.
   @param redis: Puntero al redis donde se encuentra la lista.
   @param key: Puntero a que accede al itemque contiene la lista.
   @return data: Puntero al ddato que se quito de la lista.*/
void redis_lPop(Redis* redis, char* key, Data* data);

/**@brief Fucnion que retorna el largo e la lista.
   @param redis: Punteor al redis donde se encuentra la lista que quiero medir.
   @param key: Clave que accede a la lista que deceo medir.
   @return Int: Largo de la lista medida.*/
int redis_lLeng(Redis* redis, char* key);

/**@brief Funcion que dada una clave muestra todo los datos de la lista a la que accede.
   @param redis: Puntero a redis donde se encuentra la lista que quiero iterar.
   @param key: Puntero a la clave que haccede a la lista.*/
void redis_lGet(Redis* redis, char* key);

/**@brief Funcion que crea un Item con una lista para almacenar valores y se lo agrega a Redis.
   @param redis: Puntero al redis donde quiero guardar la lista.
   @param key: Puntero a la key que accede a la lista.
   @param value: Puntero al primer valor que va a contener la lista.
   @param size: Tamaño del valor que va a contener.
   @return int: retorna la cantidad de valores dentro de la lista.
*/
int redis_createList(Redis* redis, char* key, char* value, const size_t size);

/**@brief Funcion que muestra las keys de un redis por pantalla.
   @param redis: Puntero al redis que contiene las keys que deceo ver.
*/
void redis_showKeys(Redis* redis);

/**@brief Funcion que mediante una clave muestra el contenido en pantalla.
   @param redis: Puntero al redis donde esta el item a mostrar.
   @param key: Puntero a la clave que accede al Item.
   **/
void redis_get(Redis* redis, char* key);
#endif
