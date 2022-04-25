/*
 * dynamicArray.h
 *
 *  Created on: Jul 31, 2019
 *      Author: fernando
 */

#ifndef DYNAMICARRAY_H_
#define DYNAMICARRAY_H_

#include <stdio.h>
#include <stdlib.h>

#define START_ARRAY_CAPACITY 10

typedef struct{
	int capacity;
	int occupiedSize;
	int *data; //Array of int we're storing
} DynamicArray;

void dynamicArray_init(DynamicArray *array);

void dynamicArray_append(DynamicArray *array, int value);

int dynamicArray_get(DynamicArray *array, int index);

void dynamicArray_set(DynamicArray *array, int index, int value);

void dynamicArray_doubleSizeIfFull(DynamicArray *array);

void dynamicArray_free(DynamicArray *array);
#endif /* DYNAMICARRAY_H_ */
