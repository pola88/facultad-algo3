#include <stdio.h>

#include "redis.h"
#include "item.h"
#include "list.h"

#include "string.h"

/**@brief Funcion para iniciar el Redis
   @param redis: Puntero al redis que deceo inicializar
   **/
void redis_init(Redis* redis) {
  redis->total = 0;
  redis->values = 0;
}

/**@brief Funcion que agrega un item al redis.
   @param redis: Puntero al redis donde quiero guardar el item.
   @param item: Puntero al item que deceo guardar.
*/
void redis_addItem(Redis* redis, Item* item) {
  int move = redis->total*sizeof(Item);//cuanto tengo q avanzar, para agregar el nuevo item
  redis->total++;
  redis->values = realloc(redis->values, sizeof(Item)*redis->total);//pido mas memoria para el nuevo item
  memcpy(redis->values+move, item, sizeof(Item));//agrego el item al array
}

/**@brief Funcion para crear un nuevo item dentro del Redis
   @param redis: Puntero al redis donde voy a guardar el Item
   @param key: Puntero a la clave que identifica al nuevo item
   @param value: Puntero al valor que contiene el item a crear
   @param size: Tamaño del nuevo item a crear
   **/
void redis_createItem(Redis* redis, char* key, char* value, const size_t size) {
  Item newItem;

  item_init(&newItem, key, value, size);
  redis_addItem(redis, &newItem);
}

/**@brief Funcion que crea un Item con una lista para almacenar valores y se lo agrega a Redis.
   @param redis: Puntero al redis donde quiero guardar la lista.
   @param key: Puntero a la key que accede a la lista.
   @param value: Puntero al primer valor que va a contener la lista.
   @param size: Tamaño del valor que va a contener.
   @return int: retorna la cantidad de valores dentro de la lista.
*/
int redis_createList(Redis* redis, char* key, char* value, const size_t size) {
  Item newItem;

  int count = item_initList(&newItem, key, value, size);
  redis_addItem(redis, &newItem);
  printf("contador de redis_creatlist: %d\n", count);
  return count;

}

/**@brief Funcion que inicia el valor de un Item.
   @param redis: Puntero al redis donde se encuentra el item.
   @param key: Puntero a la clave que accede al Item.
   @param valu: Puntero al valor que se decea iniciar en el item.
   @param size: Tamaño del valor que se decea iniciar en el item.
   **/
void redis_set(Redis* redis, char* key, char* value, const size_t size) {
  Item* currentItem = __redis_get(redis, key);
  if(!currentItem) {
    redis_createItem(redis, key, value, size);
  } else {
    item_setValue(currentItem, value, size);
  }
}

/**@brief Funcion que mediante una clave retorna.
   @return Item: El valor correspondiente a la clave.
   @return 0 si el redis es null o si la clave no existe
   @param redis: Puntero al redis donde esta el item a retornar.
   @param key: Puntero a la clave que accede al Item.
   **/
Item* __redis_get(Redis* redis, char* key) {
  if(redis->total == 0) {
    return 0;
  } else {
    void* tmp = redis->values;
    void* tmpSrc = redis->values;

    int totalSize = redis->total*sizeof(Item);
    while((tmp - tmpSrc) < totalSize && strcmp(((Item*)tmp)->key,key)) {
      tmp = tmp + sizeof(Item);
    }

    if(totalSize == (tmp - tmpSrc)) { //si el mismo valor, no encontro la key
      return 0;
    } else {
      return (Item*)tmp;
    }
  }
}

/**@brief Funcion comprueba la existencia de una clave.
   @param redis: Puntero a redis donde creeo que esta la clave
   @param key:Puntero a la clave que quiero probar.
   @return 0: Si no existe.
   @return 1: Si existe.
   **/
int redis_exists(Redis* redis, char* key) {
  Item* tmp = __redis_get(redis, key);

  if(tmp) {
    return 1;
  } else {
    return 0;
  }
}

/**@brief Funcion que imprime el largo de un valor encontrado por medio de una clave dada
   @param redis: Puntero al redis donde se encuentra el valor.
   @param key: Puntero a la clave que accede al valor.
   @return El largo de mi valor.
   **/
void redis_strlen(Redis* redis, char* key) {
  Item* tmp = __redis_get(redis, key);
  int length = 0;
  if(tmp) {
    length = item_getSize(tmp);
  }

  printf("%i\n", length);
}

/**@brief Funcion que concatena valor a un valor ya existente, si no existe lo crea.
   @param redis: Puntero al redis donde se encuentra el Item con el valor.
   @param key: Puntero a la calve que accede al valor.
   @param value: Puntero al valor que deceo concatenar.
   @param size: Tamaño de mi valor.
   @return El largo de mi valor.
    **/
int redis_append(Redis* redis, char* key, char* value, const size_t size) {
  Item* currentItem = __redis_get(redis, key);
  if(!currentItem) {
    redis_createItem(redis, key, value, size);
    return size;
  } else {
    return item_appendValue(currentItem, value, size);
  }
}

/**@brief Funcion que muestra las keys de un redis por pantalla.
   @param redis: Puntero al redis que contiene las keys que deceo ver.
*/
void redis_showKeys(Redis* redis) {
  void* tmp = redis->values;
  void* tmpSrc = redis->values;

  while((tmp - tmpSrc) < redis->total*sizeof(Item)) {
    Item* aux = tmp;
    printf("%s\n", aux->key);
    tmp = tmp + sizeof(Item);
  }

  printf("\n");
}

/**@brief Funcion para liberar la memoria alocada por todos los recursos que utiliza el objeto
          redis que se le pasa por parametro.
    @param redis: Puntero a redis que quiero liberar de la memoria.
**/
void redis_free(Redis* redis){
  void* tmp = redis->values;
  void* tmpSrc = redis->values;
  int num = 0;
  while((tmp - tmpSrc) < redis->total*sizeof(Item)) {
    item_free((Item*) tmp);
    tmp = tmp + sizeof(Item);
    num++;
  }
  free(redis->values);
  redis->values = 0;
  redis->total = 0;
  tmp = NULL;
  tmpSrc = NULL;
}

/**@brief Funcion que muestra el contenido de los redis en consola.
    @param redis: Puntero a redis con el contenido que deseo ver en consola.
**/
void redis_show(Redis* redis) {
  void* tmp = redis->values;
  void* tmpSrc = redis->values;


  while((tmp - tmpSrc) < redis->total*sizeof(Item)) {
    item_showValue((Item*)tmp);
    tmp = tmp + sizeof(Item);
  }

  printf("\n");
}

//Funciones para la lista.
/**@brief Funcion que dado una calve, crea un nuevo nodo y empujar el resto para atras,
    dejando a ese nodo primero y luego le inserta a ese nodo nuevo el valor de la clave.
    @param redis: Puntero a redis donde esta el valor a empujar.
    @param key: Puntero a la clave que accede al valor.
    @param value: Puntero al valor que contiene el item a crear
    @param size: Tamaño del nuevo item a crear
    @return El largo total de la lista.*/
int redis_lPush(Redis* redis, char* key, char* value, const size_t size){
    Item* item = __redis_get(redis,key);
    if(!item) {
      return redis_createList(redis, key, value, size);
    } else {
      return item_push(item, value, size);
    }
}

/**@brief Funcion que dada una lista le quita el primer elemento y lo devuelve.
   @param redis: Puntero al redis donde se encuentra la lista.
   @param key: Puntero a que accede al itemque contiene la lista.
   @return data: Puntero al ddato que se quito de la lista.*/
void redis_lPop(Redis* redis, char* key, Data* data){
    Item* item = __redis_get(redis,key);

    if(item) {
      item_pop(item, data);
    } else {
      data = 0;
    }
}

/**@brief Fucnion que retorna el largo e la lista.
   @param redis: Punteor al redis donde se encuentra la lista que quiero medir.
   @param key: Clave que accede a la lista que deceo medir.
   @return Int: Largo de la lista medida.*/
int redis_lLeng(Redis* redis, char* key){
    Item* item = __redis_get(redis,key);
    if(item) {
      return item_leng(item);
    } else {
      return 0;
    }
}

/**@brief Funcion que dada una clave retorna todo los datos de la lista a la que accede.
   @param redis: Puntero a redis donde se encuentra la lista que quiero iterar.
   @param key: Puntero a la clave que haccede a la lista.
   @return LinkedList: Puntero a la lista donde se encuentran los datos de la clave.*/
LinkedList* redis_lGet(Redis* redis, char* key){
    Item* item = __redis_get(redis,key);
    if(item) {
      return item_listGet(item);
    } else {
      return 0;
    }
}

/**@brief Funcion que mediante una clave muestra el contenido en pantalla.
   @param redis: Puntero al redis donde esta el item a mostrar.
   @param key: Puntero a la clave que accede al Item.
   **/
void redis_get(Redis* redis, char* key){
 if(redis->total != 0) {
    void* tmp = redis->values;
    void* tmpSrc = redis->values;
    int totalSize = redis->total*sizeof(Item);
    while((tmp - tmpSrc) < totalSize && strcmp(((Item*)tmp)->key,key)) {
      tmp = tmp + sizeof(Item);
    }
    if(totalSize != (tmp - tmpSrc)) { //si el mismo valor, no encontro la key
     item_showValue((Item*)tmp);
    }
  }
}
