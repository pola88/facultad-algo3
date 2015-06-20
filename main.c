#include <stdio.h>

#include "redis.h"

int main(int argc, char** argv) {
  Redis redis;
  redis_init(&redis);

  char buffer[] = { 1, 15, 129, 0x0, 205, 'a', 'z', 13, 10, 0x12};
  char newValue[] = { 1, 15};
  char secondValue[] = { 0x0, 0x20, 0x30};

  printf("Redis:\n");
  redis_set(&redis, "myKey", buffer, sizeof(buffer));
  redis_set(&redis, "myKey2", newValue, sizeof(newValue));
  redis_set(&redis, "myKey3", newValue, sizeof(newValue));
  redis_set(&redis, "myKey", secondValue, sizeof(secondValue));
  redis_show(&redis);

  printf("Agrego lista\n");

  int count = redis_lPush(&redis, "myList", buffer, sizeof(buffer));

  int lLeng = redis_lLeng(&redis, "myList");
  printf("Tamaño de la lista %i\n", lLeng);

  count = redis_lPush(&redis, "myList", newValue, sizeof(newValue));

  printf("Tamaño de la lista, dps de agregar un item %i\n", count);

  Data data;
  data_init(&data, "",0);
  redis_lPop(&redis, "myList", &data);
  data_print(&data);

  lLeng = redis_lLeng(&redis, "myList");
  printf("Tamaño de la lista, dps de quitar un item %i\n", lLeng);

  printf("Keys\n");
  redis_showKeys(&redis);

  printf("Liberar redis\n");

  redis_free(&redis);
  data_free(&data);

  printf("\n");
  printf("TODO CORRECTO\n");
  return 0;
}
