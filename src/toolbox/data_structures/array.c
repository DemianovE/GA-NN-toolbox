//
// Created by egor on 13.06.25.
//

#include "array.h"

#include <assert.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/*
 * This function is used to implement the size doubling. The famous Dynamic part of the interface
 * Input:
 *    Array *array - the array to be doubled
 * Output;
 *    The function has no return but manipulates a pointer
 */
static void ArrayDouble(Array *array){
  assert(array != NULL && "The array pointer can be NULL!");

  float* new_data_ptr = realloc(array->data, array->length * 2 * sizeof(float));

  array->data = new_data_ptr;
  array->length = array->length * 2;
}

Array* ArrayCreate(const size_t length){
  assert(length >= 0 && "The size of array should be positive");

  Array *array = NULL;
  array = malloc(sizeof(Array));
  if (array == NULL){ perror("Failed to allocate Array"); exit(EXIT_FAILURE); }

  array->data = NULL;
  array->length = length;
  array->index = 0;

  array->data = malloc(array->length * sizeof(float));
  if (array->data == NULL){ perror("Failed to allocate Array data"); free(array); exit(EXIT_FAILURE); }

  return array;
}

Array* ArrayConcat(const Array* array1, const Array* array2){
  assert(array1 != NULL && "The array1 can be NULL!");
  assert(array2 != NULL && "The array2 can be NULL!");

  const size_t newLength = array1->index + array2->index;
  Array *newArray = ArrayCreate(newLength);

  if (array1->index > 0){ memcpy(newArray->data,                     array1->data, array1->length*sizeof(float)); }
  if (array2->index > 0){ memcpy(newArray->data + array1->index, array2->data, array2->length*sizeof(float)); }

  return newArray;
}

void ArrayAppend(Array *array, const float input){
  assert(array != NULL && "The array can be NULL!");
  assert(array->data != NULL && "The array data can be NULL!");

  array->index++;
  if (array->index > array->length){ ArrayDouble(array); }
  array->data[array->index] = input;
}

void ArrayAppendPointer(Array *array, const float *input, const size_t pointerLength){
  assert(array != NULL && "The array can be NULL!");
  assert(array->data != NULL && "The array data can be NULL!");
  assert(input != NULL && "The input can be NULL!");

  if (array->index + pointerLength > array->length){ ArrayDouble(array); }

  memcpy(array->data + array->index, input, pointerLength * sizeof(float));
  array->index += pointerLength;
}

void ArrayDestroy(Array *array){
  if (array == NULL) { return; }
  free(array->data);
  free(array);
}