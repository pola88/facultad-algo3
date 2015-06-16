#include <stdio.h>

#include "redis.h"

int main(int argc, char** argv) {
    Redis redis;
    redis_init(&redis);

    char buffer[] = { 1, 15, 129, 0x0, 205, 'a', 'z', 13, 10, 0x12};
    char newValue[] = { 1, 15};
    char secondValue[] = { 0x0, 0x20, 0x30};

    printf("Redis:\n");
    //
    redis_set(&redis, "myKey", buffer, sizeof(buffer));
    //
    redis_set(&redis, "myKey2", newValue, sizeof(newValue));

    redis_set(&redis, "myKey3", newValue, sizeof(newValue));

    redis_set(&redis, "myKey", secondValue, sizeof(secondValue));

    redis_show(&redis);
    //
    // printf("Exists\n");
    // printf("%i\n", redis_exists(&redis, "myKey"));
    // printf("%i\n", redis_exists(&redis, "fake"));
    // printf("%i\n", redis_exists(&redis, "myKey2"));
    //
    // printf("Sizes\n");
    // redis_strlen(&redis, "myKey");
    // redis_strlen(&redis, "fake");
    // redis_strlen(&redis, "myKey2");
    //
    // printf("Append\n");
    // printf("Nuevo Size: %d\n", redis_append(&redis, "myKey", secondValue, sizeof(secondValue)));
    // printf("Nuevo Size: %d\n", redis_append(&redis, "myKey2", secondValue, sizeof(secondValue)));

    // printf("Get: \n");
    // Item* i = redis_get(&redis, "myKey");
    // printf("%s\n", i->key);


    printf("Agrego lista\n");
    int count = redis_lPush(&redis, "myList", buffer, sizeof(buffer));
    count = redis_lPush(&redis, "myList", newValue, sizeof(newValue));
    printf("Tamaño de la lista %i\n", count);

    printf("Keys\n");
    redis_showKeys(&redis); //TODO: remove it

    printf("Liberar redis\n");
    redis_free(&redis);
}
