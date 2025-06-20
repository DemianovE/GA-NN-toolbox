/**
 * @file array.c
 * @brief Dynamic Array data structure public interface implementation.
 *
 * This file defines all implementations of the Array public interface
 */

#include "array.h"

#include <assert.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

static void Array_SetIndex(Array *array, size_t index);
static void Array_SetLength(Array *array, size_t length);
static void Array_SetArray(Array *array, float *data);

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

  Array_SetLength(array, length);
  Array_SetIndex(array, 0);

  Array_SetArray(array, NULL);
  Array_SetArray(array, malloc(Array_GetLength(array) * sizeof(float)));
  if (Array_GetArray(array) == NULL){ perror("Failed to allocate Array data"); free(array); exit(EXIT_FAILURE); }

  return array;
}

Array* Array_Concat(const Array* array1, const Array* array2){
  assert(array1 != NULL && "The array1 can be NULL!");
  assert(array2 != NULL && "The array2 can be NULL!");

  const size_t newLength = Array_GetIndex(array1) + Array_GetIndex(array2);
  Array *newArray = Array_Create(newLength);

  if (Array_GetIndex(array1) > 0){ memcpy(Array_GetArray(newArray),                          Array_GetArray(array1), Array_GetIndex(array1) * sizeof(float)); }
  if (Array_GetIndex(array2) > 0){ memcpy(Array_GetArray(newArray) + Array_GetIndex(array1), Array_GetArray(array2), Array_GetIndex(array2) * sizeof(float)); }

  return newArray;
}

Array* Array_MakeCopy(const Array *arrayFrom){
  Array *output = Array_Create(Array_GetLength(arrayFrom));
  memcpy(Array_GetArray(output), Array_GetArray(arrayFrom), Array_GetIndex(arrayFrom) * sizeof(float));

  Array_SetLength(output, Array_GetLength(arrayFrom));
  Array_SetIndex(output, Array_GetIndex(arrayFrom));
  return output;
}

void Array_Destroy(Array *array){
  if (array == NULL) { return; }
  free(Array_GetArray(array));
  free(array);
}



//=============================================================================
//
//                     Array Query Functions
//
//=============================================================================

float Array_GetValue(const Array *array, const size_t index){
  return Array_GetArray(array)[index];
}

float* Array_GetArray(const Array *array){
  return array->data;
}

size_t Array_GetIndex(const Array *array){
  return array->index;
}

size_t Array_GetLength(const Array *array){
  return array->length;
}



//=============================================================================
//
//                     Array Manipulation Functions
//
//=============================================================================

/*!
 * @ingroup ArrayManipulation
 * @brief Double the size of the array.
 * @param array the array to be doubled.
 */
static void Array_Double(Array *array){
  assert(array != NULL && "The array pointer can be NULL!");

  if (Array_GetLength(array) == 0) Array_SetLength(array, 1);

  float *new_data_ptr = realloc(Array_GetArray(array), Array_GetLength(array) * 2 * sizeof(float));
  if (new_data_ptr == NULL){ perror("realloc command failed"); Array_Destroy(array); exit(EXIT_FAILURE); }

  Array_SetArray(array, new_data_ptr);
  Array_SetLength(array, Array_GetLength(array) * 2);

  for(size_t i = Array_GetIndex(array); i < Array_GetLength(array); i++) Array_SetCoordinate(array, i, 0.0f);
}

Array* Array_ReturnDataFromTo(const Array *array, const size_t start, const size_t numberOfElements){
  Array* output = Array_Create(numberOfElements);
  float *data = malloc((numberOfElements) * sizeof(float));
  memcpy(data, Array_GetArray(array) + start, numberOfElements * sizeof(float));

  Array_AppendPointer(output, data, numberOfElements);
  free(data);

  return output;
}

void Array_SetCoordinate(const Array *array, const size_t index, const float value){
  array->data[index] = value;
}

/*!
 * @ingroup ArrayManipulation
 * @brief Set the index value of the Array.
 * @param array the array which data will be altered.
 * @param index value of the index.
 */
static void Array_SetIndex(Array *array, const size_t index){
  array->index = index;
}

/*!
 * @ingroup ArrayManipulation
 * @brief Set the length value of the Array.
 * @param array the array which data will be altered.
 * @param length value of the length.
 */
static void Array_SetLength(Array *array, const size_t length){
  array->length = length;
}

/*!
 * @ingroup ArrayManipulation
 * @brief Set the data values of the Array.
 * @param array the array which data will be altered.
 * @param data new float type pointer.
 */
static void Array_SetArray(Array *array, float *data){
  array->data = data;
}

void Array_SetDataFromTo(const Array *array, const size_t start, const size_t numberOfElements, const float *values){
  assert(array != NULL && "The array pointer can be NULL!");
  assert(values != NULL && "The values can be NULL!");

  assert(Array_GetArray(array) != NULL && "The array data can be NULL!");

  assert(numberOfElements > 0 && "Number of elements should more than 0!");
  assert(start + numberOfElements <= Array_GetLength(array) && "Start index out of range!");

  memcpy(Array_GetArray(array) + start, values, numberOfElements * sizeof(float));
}

void Array_Append(Array *array, const float value){
  assert(array != NULL && "The array can be NULL!");

  assert(Array_GetArray(array) != NULL && "The array data can be NULL!");

  if (Array_GetIndex(array) + 1 >= Array_GetLength(array)){ Array_Double(array); }
  for(size_t i = 0; i < Array_GetLength(array); i++) printf("%f ", array->data[i]);

  Array_SetCoordinate(array, Array_GetIndex(array), value);
  Array_SetIndex(array, Array_GetIndex(array) + 1);
}

void Array_AppendPointer(Array *array, const float *values, const size_t pointerLength){
  assert(array != NULL && "The array can be NULL!");
  assert(values != NULL && "The input can be NULL!");

  assert(Array_GetArray(array) != NULL && "The array data can be NULL!");

  if (Array_GetIndex(array) + pointerLength - 1 >= Array_GetLength(array)){ Array_Double(array); }

  memcpy(Array_GetArray(array) + Array_GetIndex(array), values, pointerLength * sizeof(float));
  Array_SetIndex(array, Array_GetIndex(array) + pointerLength);
}



//=============================================================================
//
//                     Array Utility Helper Functions
//
//=============================================================================

int Array_CheckEqual(const Array *arrayOne, const Array *arrayTwo){
  if (Array_GetIndex(arrayOne)  != Array_GetIndex(arrayTwo))  return 0;
  if (Array_GetLength(arrayOne) != Array_GetLength(arrayTwo)) return 0;

  for (size_t i=0; i<Array_GetLength(arrayOne); i++){
    if (Array_GetValue(arrayOne, i) != Array_GetValue(arrayTwo, i)) return 0;
  }
  return 1;
}