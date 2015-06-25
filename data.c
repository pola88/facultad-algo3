#include "data.h"
#include <stdio.h>

#include <string.h> //para usar memcpy
#include <stdlib.h> //Para user malloc

//Calcula si necesita mas espacio para guardar el valor
/**@brief Funcion que calcular el tamaño en memoria disponible para guardar un valor.
   @param size: tamaño del valor a guardar.
   @return tamaño en memoria disponible.**/
int data_calculateCapacity(const size_t size) {
  if(size > DEFAULT_LENGTH) {
    //redondea para arriba
    return DEFAULT_LENGTH * ((size + DEFAULT_LENGTH - 1 ) / DEFAULT_LENGTH);
  } else {
    return DEFAULT_LENGTH;
  }
}
/**@brief Funcion que inicia la data con valor.
   @param data: Puntero a la data que quiero iniciar.
   @param value: Puntero a al valor con el que deceo inicializar.
   @param size: Tamaño del valor con el que deceo inicializar la data.*/
void data_init(Data* data, const char* value, const size_t size) {
  data->size = size; //Asigno el tamaño del objecto a guardar;
  data->capacity = data_calculateCapacity(data->size);//Cuanto memoria tiene para usar

  data->value = malloc(data->capacity);//Pido memoria para usar en el heap

  memcpy(data->value, value, data->capacity);
}
/**@brief Funcion para mostrar la data por consola.
   @param data: Puntero al adata que quiero mostrar.*/
void data_print(Data* data) {
  char* tmp = data->value;
  char* tmpSrc = data->value;

  while((tmp - tmpSrc) < data->size) {
    printf("0x%x ", *tmp++);
  }

  printf("\n");
}
/**@brief Funcion que libera los recusos a locados en memoria por la data.
   @param data: Puntero a la data que quiero liberar.*/
void data_free(Data* data) {
  free(data->value);
  data->value = 0;
}
/**@brief Funcion que cualcula si hay espacio en memoria necesario en caso de que no ejecuta relloc.
   @param data: Puntero a la data donde creo que hay poco espacio.*/
void data_reallocIfNecesary(Data* data) {
  int newCapacity = data_calculateCapacity(data->size);

  if(data->capacity != newCapacity) {
    data->capacity = newCapacity;
    data->value = realloc(data->value, data->capacity);
  }
}
/**@brief Funcion para camiar el valor de la data.
   @param data: Puntero a la data donde esta el valor que deceo cambiar.
   @param value: Puntero al valor que deceo remplazar.
   @param size: Tamaño de del valor.*/
void data_setValue(Data* data, const char* value, const size_t size) {
  data->size = size;
  data_reallocIfNecesary(data);
  memcpy(data->value, value, data->capacity - 1);
}
/**@brief Funcion que copia data.
   @param dst: Puntero a la data que recibe el valor copiado
   @param src: Puntero a la data de donde secopia el valor.*/
void data_copy(Data* dst, Data* src) {

  dst->size = src->size;
  data_reallocIfNecesary(dst);
  memcpy(dst->value, src->value, dst->capacity - 1);
}
/**@brief Funcion que concatena datas.
   @param dst: Puntero a data donde quiero concatenar.
   @param value: puntero al valor donde quiero concatenar.
   @param size: Tamaño de la data que quiero concatenar.
   @return El tamaño de la data concatenada en Int*/
int data_append(Data* dst, const char* value, const size_t size) {
  int oldSize = dst->size;

  dst->size = dst->size + size;
  data_reallocIfNecesary(dst);

  memcpy(dst->value + oldSize, value, size);

  return dst->size;
}
/**@brief Funcion que compra dos datos por el tamaño y lo imprime en consola.
   @param firstData: Puntero a data que quiero comparar.
   @param secondData: Puntero a data contra la que quiero comparar.*/
void data_compare(Data* firstData, Data* secondData) {
  size_t size;
  if(firstData->size < secondData->size) {
    size = secondData->size;
  } else {
    size = firstData->size;
  }

  int result = memcmp(firstData, secondData, size);

  if(result != 0) {
    printf("Son diferentes\n");
  } else {
    printf("Son iguales\n");
  }
}
/**@brief Funcion que retorna el tamaño de la data
   @param data: Puntero a la data de la cual quiero saber el tamaño
   @return El tamaño de la data Int*/
int data_getSize(Data* data) {
  return data->size;
}
