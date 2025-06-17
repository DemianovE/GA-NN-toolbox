//
// Created by egor on 13.06.25.
//

#include "array.h"

#include <assert.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "matrix.h"

/*!
 * @ingroup ArrayLifecycle
 * @brief Double the size of the array.
 * @param array the array to be doubled.
 */
static void Array_Double(Array *array){
  assert(array != NULL && "The array pointer can be NULL!");

  if (array->length == 0) {array->length = 1;}

  float *new_data_ptr = realloc(array->data, array->length * 2 * sizeof(float));
  if (new_data_ptr == NULL){ perror("realloc command failed"); Array_Destroy(array); exit(EXIT_FAILURE); }

  array->data = new_data_ptr;
  array->length = array->length * 2;

  for(size_t i = array->index; i < array->length; i++) array->data[i] = 0.0f;
}



//=============================================================================
//
//                     Array Lifecycle Management Functions
//
//=============================================================================

Array* Array_Create(const size_t length){
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

Array* Array_Concat(const Array* array1, const Array* array2){
  assert(array1 != NULL && "The array1 can be NULL!");
  assert(array2 != NULL && "The array2 can be NULL!");

  const size_t newLength = array1->index + array2->index;
  Array *newArray = Array_Create(newLength);

  if (array1->index > 0){ memcpy(newArray->data,                     array1->data, array1->index * sizeof(float)); }
  if (array2->index > 0){ memcpy(newArray->data + array1->index, array2->data, array2->index * sizeof(float)); }

  return newArray;
}

Array* Array_MakeCopy(const Array *arrayFrom){
  Array *output = Array_Create(arrayFrom->length);
  memcpy(output->data, arrayFrom->data, arrayFrom->index * sizeof(float));
  return output;
}

void ArrayDestroy(Array *array){
  if (array == NULL) { return; }
  free(array->data);
  free(array);
}



//=============================================================================
//
//                     Array Query Functions
//
//=============================================================================

float Array_GetCoordinate(const Array *array, const size_t index){
  return array->data[index];
}



//=============================================================================
//
//                     Array Manipulation Functions
//
//=============================================================================

Array* Array_ReturnDataFromTo(const Array *array, const size_t start, const size_t numberOfElements){
  Array* output = Array_Create(numberOfElements);
  float *data = malloc((numberOfElements) * sizeof(float));
  memcpy(data, array->data + start, numberOfElements * sizeof(float));

  Array_AppendPointer(output, data, numberOfElements);
  free(data);

  return output;
}

void Array_SetCoordinate(const Array *array, const size_t index, const float value){
  array->data[index] = value;
}

void Array_SetDataFromTo(const Array *array, const size_t start, const size_t numberOfElements, const float *values){
  assert(array != NULL && "The array pointer can be NULL!");
  assert(array->data != NULL && "The array data can be NULL!");
  assert(values != NULL && "The values can be NULL!");

  assert(numberOfElements > 0 && "Number of elements should more than 0!");
  assert(start + numberOfElements <= array->length && "Start index out of range!");

  memcpy(array->data + start, values, numberOfElements * sizeof(float));
}

void Array_Append(Array *array, const float value){
  assert(array != NULL && "The array can be NULL!");
  assert(array->data != NULL && "The array data can be NULL!");

  if (array->index + 1 >= array->length){ Array_Double(array); }
  for(size_t i = 0; i < array->length; i++) printf("%f ", array->data[i]);

  array->data[array->index] = value;
  array->index++;
}

void Array_AppendPointer(Array *array, const float *values, const size_t pointerLength){
  assert(array != NULL && "The array can be NULL!");
  assert(array->data != NULL && "The array data can be NULL!");
  assert(values != NULL && "The input can be NULL!");

  if (array->index + pointerLength - 1 >= array->length){ Array_Double(array); }

  memcpy(array->data + array->index, values, pointerLength * sizeof(float));
  array->index += pointerLength;
}

