#include <stdio.h>

#include "redis.c"
#include "redis.h"

int main(int argc, char** argv) {
    Redis redis;
    initRedis(&redis);

    char buffer[] = { 1, 15, 129, 0x0, 205, 'a', 'z', 13, 10, 0x12};
    char newValue[] = { 1, 15};
    char secondValue[] = { 0x0, 0x20, 0x30};

    printf("Redis:\n");
    //
    set(&redis, "myKey", buffer, sizeof(buffer));
    //
    set(&redis, "myKey2", newValue, sizeof(buffer));
    //
    set(&redis, "myKey", secondValue, sizeof(secondValue));

    show(&redis);

    printf("Exists\n");
    printf("%i\n", exists(&redis, "myKey"));
    printf("%i\n", exists(&redis, "fake"));
    printf("%i\n", exists(&redis, "myKey2"));

    printf("Sizes\n");
    redisStrlen(&redis, "myKey");
    redisStrlen(&redis, "fake");
    redisStrlen(&redis, "myKey2");

    printf("Append\n");
    printf("Nuevo Size: %d\n", append(&redis, "myKey", secondValue, sizeof(secondValue)));
    printf("Nuevo Size: %d\n", append(&redis, "myKey2", secondValue, sizeof(secondValue)));

    printf("Get: \n");
    Item* i = get(&redis, "myKey");
    printf("%s\n", i->key);

    freeRedis(&redis);
}
