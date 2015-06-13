#include "redis.h"
#include "item.h"
#include "item.c"
#include "list.h"

/**@brief Funcion para iniciar el Redis
   @param redis: Puntero al redis que deceo inicializar
   **/
void initRedis(Redis* redis) {
  redis->total = 0;
  redis->values = malloc(sizeof(Item));
}

void addItem(Redis* redis, Item* item) {
  int move = sizeof(Item)*(redis->total- 1);//cuanto tengo q avanzar, para agregar el nuevo item
  redis->values = realloc(redis->values, sizeof(Item)*redis->total);//pido mas memoria para el nuevo item
  memcpy(redis->values+move, item, sizeof(Item));//agrego el item al array
}

/**@brief Funcion para crear un nuevo item dentro del Redis
   @param redis: Puntero al redis donde voy a guardar el Item
   @param key: Puntero a la clave que identifica al nuevo item
   @param value: Puntero al valor que contiene el item a crear
   @param size: Tamaño del nuevo item a crear
   **/
void createItem(Redis* redis, char* key, char* value, const size_t size) {
  redis->total++;
  Item newItem;

  initItem(&newItem, key, value, size);
  addItem(redis, &newItem);
}

int createList(Redis* redis, char* key, char* value, const size_t size) {
  redis->total++;
  Item newItem;

  int count = initListItem(&newItem, key, value, size);
  addItem(redis, &newItem);

  return count;
}

/**@brief Funcion que inicia el valor de un Item.
   @param redis: Puntero al redis donde se encuentra el item.
   @param key: Puntero a la clave que accede al Item.
   @param valu: Puntero al valor que se decea iniciar en el item.
   @param size: Tamaño del valor que se decea iniciar en el item.
   **/
void set(Redis* redis, char* key, char* value, const size_t size) {
  Item* currentItem = get(redis, key);
  if(!currentItem) {
    createItem(redis, key, value, size);
  } else {
    setItemValue(currentItem, value, size);
  }
}

/**@brief Funcion que mediante una clave retorna.
   @return Item: El valor correspondiente a la clave.
   @return 0 si el redis es null o si la clave no existe
   @param redis: Puntero al redis donde esta el item a retornar.
   @param key: Puntero a la clave que accede al Item.
   **/
Item* get(Redis* redis, char* key) {
  if(redis->total == 0) {
    return 0;
  } else {
    Item* tmp = redis->values;
    Item* tmpSrc = redis->values;

    int totalSize = redis->total*sizeof(Item);

    while((tmp - tmpSrc) < totalSize && strcmp(tmp->key,key)) {
      tmp = tmp + sizeof(Item);
    }

    if(totalSize == (tmp - tmpSrc)) { //si el mismo valor, no encontro la key
      return 0;
    } else {
      return tmp;
    }
  }
}
/**@brief Funcion comprueba la existencia de una clave.
   @param redis: Puntero a redis donde creeo que esta la clave
   @param key:Puntero a la clave que quiero probar.
   @return 0: Si no existe.
   @return 1: Si existe.
   **/
int exists(Redis* redis, char* key) {
  Item* tmp = get(redis, key);

  if(tmp) {
    return 1;
  } else {
    return 0;
  }
}

/**@brief Funcion que imprime el largo de un valor encontrado por medio de una clave dada
   @param redis: Puntero al redis donde se encuentra el valor.
   @param key: Puntero a la clave que accede al valor.
   **/
void redisStrlen(Redis* redis, char* key) {
  Item* tmp = get(redis, key);
  int length = 0;
  if(tmp) {
    length = getSize(tmp);
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
int append(Redis* redis, char* key, char* value, const size_t size) {
  Item* currentItem = get(redis, key);
  if(!currentItem) {
    createItem(redis, key, value, size);
    return size;
  } else {
    return appendValueToItem(currentItem, value, size);
  }
}

//funciones agregadas por Ale COMIENZO
/**@brief Funcion para liberar la memoria alocada por todos los recursos que utiliza el objeto
          redis que se le pasa por parametro.
    @param redis: Puntero a redis que quiero liberar de la memoria.
**/
void freeRedis(Redis* redis){
  Item* tmp = redis->values;
  Item* tmpSrc = redis->values;
  //recorro redis->values liberando item a item
  while((tmp - tmpSrc) < redis->total*sizeof(Item)) {
    freeItem(tmp);
    tmp = tmp + sizeof(Item);
  }
  free(redis->values);
  redis->values = 0;
}

//funciones agregadas por Ale FINAL
/**@brief Funcion que muestra el contenido de los redis en consola.
    @param redis: Puntero a redis con el contenido que deseo ver en consola.
**/
void show(Redis* redis) {
  Item* tmp = redis->values;
  Item* tmpSrc = redis->values;

  //imprimo hasta el tamaño de la palabra
  while((tmp - tmpSrc) < redis->total*sizeof(Item)) {
    showItemValue(tmp);
    tmp = tmp + sizeof(Item);
  }

  printf("\n");
}

//Funciones para la lista.
//Lo programo un tipo mas.
//TODO: lo cambie, la key lo recibo como char*, y siempre q hago el get, veo si existe, sino siempre devuelvo 0

/**@brief Funcion que dado una calve, crea un nuevo nodo y empujar el resto para atras,
    dejando a ese nodo primero y luego le inserta a ese nodo nuevo el valor de la clave.
    @param redis: Puntero a redis donde esta el valor a empujar.
    @param key: Puntero a la clave que accede al valor.
    @param value: Puntero al valor que contiene el item a crear
    @param size: Tamaño del nuevo item a crear
    @return El largo total de la lista.*/
int Lpush(Redis* redis, char* key, char* value, const size_t size){
    Item* item = get(redis,key);
    if(!item) {
      return createList(redis, key, value, size);
    } else {
      return Ipush(item, value, size);
    }

}
/**@brief Funcion que dada una lista le quita el primer elemento y lo devuelve.
   @param redis: Puntero al redis donde se encuentra la lista.
   @param key: Puntero a que accede al itemque contiene la lista.
   @return data: Puntero al ddato que se quito de la lista.*/
Data* Lpop(Redis* redis, char* key){
    Item* item = get(redis,key);

    if(item) {
      return Ipop(item);
    } else {
      return 0;
    }

}
/**@brief Fucnion que retorna el largo e la lista.
   @param redis: Punteor al redis donde se encuentra la lista que quiero medir.
   @param key: Clave que accede a la lista que deceo medir.
   @return Int: Largo de la lista medida.*/
int Lleng(Redis* redis, char* key){
    Item* item = get(redis,key);
    if(item) {
      return Ileng(item);
    } else {
      return 0;
    }
}

// TODO: esta definido?
/**@brief Funcion que dada una clave retorna todo los datos de la lista a la que accede.
   @param redis: Puntero a redis donde se encuentra la lista que quiero iterar.
   @param key: Puntero a la clave que haccede a la lista.
   @return LinkedList: Puntero a la lista donde se encuentran los datos de la clave.*/
LinkedList* Lget(Redis* redis, char* key){
    Item* item = get(redis,key);
    if(item) {
      // return Ileng(item);
      return 0;
    } else {
      return 0;
    }
}
