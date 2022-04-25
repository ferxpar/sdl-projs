/*
 * dynamicArray.c
 *
 *  Created on: Jul 31, 2019
 *      Author: fernando
 */

#include "dynamicArray.h"

void dynamicArray_init(DynamicArray *array){
	array->capacity = START_ARRAY_CAPACITY;
	array->occupiedSize = 0;
	array->data = malloc(sizeof(int) * array->capacity);
}

void dynamicArray_append(DynamicArray *array, int value){
	dynamicArray_doubleSizeIfFull(array);

	array->data[array->occupiedSize] = value;
	array->occupiedSize++;
}

int dynamicArray_get(DynamicArray *array, int index){
	if(index > 0 && array->occupiedSize <= index){
		printf("Trying to GET index out of bounds in dynamic array, value was %d, array size is %d\n", index, array->occupiedSize);
		exit(0);
	}
	return array->data[index];
}

void dynamicArray_set(DynamicArray *array, int index, int value){
	if(index < 0 || array->occupiedSize < index){
		printf("Trying to SET index out of bounds in dynamic array, value was %d, array size is %d\n", index, array->occupiedSize);
		exit(0);
	} else {
		array->data[index] = value;
	}
}

void dynamicArray_doubleSizeIfFull(DynamicArray *array){
	if(array->occupiedSize >= array->capacity){
		array->capacity *= 2;
		array->data = realloc(array->data, sizeof(int) * array->capacity);
	}
}

void dynamicArray_free(DynamicArray *array){
	free(array->data);
}
