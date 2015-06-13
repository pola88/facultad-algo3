#ifndef __DATA_H__
#define __DATA_H__

#define DEFAULT_LENGTH 4//por defecto, tiene una capacidad de 4

typedef struct _DATA {
    size_t size; //Es el tamaño del array
    int capacity; // cantidad de memoria disponible para usar
    char* value;
} Data ;
/**@brief Funcion que inicia la data con valor.
   @param data: Puntero a la data que quiero iniciar.
   @param value: Puntero a al valor con el que deceo inicializar.
   @param size: Tamaño del valor con el que deceo inicializar la data.*/
void dataInit(Data* d, const char* value, const size_t size);
/**@brief Funcion que imprime un dato en consola
   @param d:Puntero al dato que quiero imprimir*/
void printData(Data* d);
/**@brief Funcion que calcular el tamaño en memoria disponible para guardar un valor.
   @param size: tamaño del valor a guardar.
   @return tamaño en memoria disponible.**/
int calculateCapacitiy(const int size);
/**@brief Funcion que libera los recusos a locados en memoria por la data.
   @param data: Puntero a la data que quiero liberar.*/
void freeData(Data* d);
/**@brief Funcion que cualcula si hay espacio en memoria necesario en caso de que no ejecuta relloc.
   @param data: Puntero a la data donde creo que hay poco espacio.*/
void reallocIfNecesary(Data* data);
/**@brief Funcion para camiar el valor de la data.
   @param data: Puntero a la data donde esta el valor que deceo cambiar.
   @param value: Puntero al valor que deceo remplazar.
   @param size: Tamaño de del valor.*/
void setValue(Data* data, const char* value, const size_t size);
/**@brief Funcion que copia data.
   @param dst: Puntero a la data que recibe el valor copiado
   @param src: Puntero a la data de donde secopia el valor.*/
void copyData(Data* dst, Data* src);
/**@brief Funcion que concatena datas.
   @param dst: Puntero a data donde quiero concatenar.
   @param value: puntero al valor donde quiero concatenar.
   @param size: Tamaño de la data que quiero concatenar.
   @return El tamaño de la data concatenada en Int*/
int appendData(Data* dst, const char* value, const size_t size);
/**@brief Funcion que compra dos datos por el tamaño y lo imprime en consola.
   @param firstData: Puntero a data que quiero comparar.
   @param secondData: Puntero a data contra la que quiero comparar.*/
void compareData(Data* firstData, Data* secondData);
/**@brief Funcion que retorna el tamaño de la data
   @param data: Puntero a la data de la cual quiero saber el tamaño
   @return El tamaño de la data Int*/
int getDataSize(Data* data);

#endif
