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

struct Array {
  void *data; // the array itself
  size_t capacity; // the capacity of the array
  size_t index; // the index of the next free cell of the array (used for inner size calculations)
  size_t item_size; // the size of the saved items
};


static void Array_SetItemSize(Array *array, size_t item_size);
static void Array_SetIndex(Array *array, size_t index);
static void Array_SetCapacity(Array *array, size_t capacity);
static void Array_SetArray(Array *array, float *data);
static void* Array_GetValueIndex(const Array *array, const size_t index);
static void Array_SetValuesInArray(const Array *array, const size_t index, const void *newValue, const size_t size);

//=============================================================================
//
//                     Array Lifecycle Management Functions
//
//=============================================================================

Array* Array_Create(const size_t capacity, const size_t item_size){
  assert(capacity >= 0 && "The size of array should be positive");

  Array *array = NULL;
  array = malloc(sizeof(Array));
  if (array == NULL) { perror("Failed to allocate Array"); exit(EXIT_FAILURE); }

  // set basic variables
  Array_SetCapacity(array, capacity);
  Array_SetIndex(array, 0);
  Array_SetItemSize(array, item_size);

  // make the main void array with the size usage of one item
  Array_SetArray(array, NULL);
  Array_SetArray(array, malloc(Array_GetCapacity(array) * Array_GetItemSize(array)));
  if (Array_GetArray(array) == NULL) { perror("Failed to allocate Array data"); free(array); exit(EXIT_FAILURE); }

  // set all values to 0/False/NULL for the void array
  memset(Array_GetArray(array), 0, Array_GetCapacity(array) * Array_GetItemSize(array));
  return array;
}

Array* Array_Concat(const Array *array1, const Array *array2){
  assert(array1 != NULL && "The array1 can be NULL!");
  assert(array2 != NULL && "The array2 can be NULL!");

  // define new capacity and new array
  const size_t newCapacity = Array_GetIndex(array1) + Array_GetIndex(array2);
  Array *newArray = Array_Create(newCapacity, Array_GetItemSize(array1));

  // copy the values knowing that the size of item is custom

  if (Array_GetIndex(array1) > 0) { Array_SetValuesInArray(newArray, 0,                 Array_GetArray(array1), Array_GetIndex(array1) * Array_GetItemSize(array1)); }
  if (Array_GetIndex(array2) > 0) { Array_SetValuesInArray(newArray, Array_GetIndex(array1), Array_GetArray(array2), Array_GetIndex(array2) * Array_GetItemSize(array2)); }

  return newArray;
}

Array* Array_MakeCopy(const Array *arrayFrom){
  assert(arrayFrom != NULL && "The array can be NULL!");

  // make a new array with the same variables, copy values to it with custom item size
  Array *output = Array_Create(Array_GetCapacity(arrayFrom), Array_GetItemSize(arrayFrom));

  Array_SetValuesInArray(output, 0, Array_GetArray(arrayFrom), Array_GetIndex(arrayFrom) * Array_GetItemSize(arrayFrom));

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

void* Array_GetValue(const Array *array, const size_t index){
  // the value is justa memory pointer to the actual value which should be cast
  return Array_GetValueIndex(array, index);
}

void* Array_GetArray(const Array *array) { return array->data; }

size_t Array_GetItemSize(const Array *array) { return array->item_size; }

size_t Array_GetIndex(const Array *array) { return array->index; }

size_t Array_GetCapacity(const Array *array) { return array->capacity; }

/*!
 * @ingroup ArrayQuery
 * @brief Set the specified partition of an array to the desired data.
 * @param array the array which data will be altered.
 * @param index the shift of elements
 * @param newValue the pointer to new values of the array
 * @param size the size of the partition
 *
 * @warning The function is meant to be the sole memory source in the interface, to make memory related issues not an issue
 */
static void Array_SetValuesInArray(const Array *array, const size_t index, const void* newValue, const size_t size) { memcpy(Array_GetValueIndex(array, index), newValue, size); }


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

  if (Array_GetCapacity(array) == 0) Array_SetCapacity(array, 1);

  // make a new data pointer and copy all data to it
  void *new_data_ptr = realloc(Array_GetArray(array), Array_GetCapacity(array) * 2 * Array_GetItemSize(array));
  if (new_data_ptr == NULL) { perror("realloc command failed"); Array_Destroy(array); exit(EXIT_FAILURE); }

  // assign the new array pointer and reset capacity
  Array_SetArray(array, new_data_ptr);
  Array_SetCapacity(array, Array_GetCapacity(array) * 2);

  // set the new portion of the pointer to 0/False/NULL
  char* start_of_new_area = Array_GetValueIndex(array, Array_GetIndex(array));
  const size_t bytes_to_zero = (Array_GetCapacity(array) - Array_GetIndex(array)) * Array_GetItemSize(array);
  memset(start_of_new_area, 0, bytes_to_zero);
}

Array* Array_ReturnDataFromTo(const Array *array, const size_t start, const size_t numberOfElements){
  Array* output = Array_Create(numberOfElements, Array_GetItemSize(array));
  float *data = malloc((numberOfElements) * Array_GetItemSize(array));
  memcpy(data, Array_GetValueIndex(array, start), numberOfElements * Array_GetItemSize(array));

  Array_AppendPointer(output, data, numberOfElements);
  free(data);

  return output;
}

void Array_SetCoordinate(const Array *array, const size_t index, const void* newValue) { Array_SetValuesInArray(array, index, newValue, Array_GetItemSize(array)); }

/*!
 * @ingroup ArrayManipulation
 * @brief Set the item_size value of the Array.
 * @param array the array which data will be altered.
 * @param item_size value of the item_size.
 */
static void Array_SetItemSize(Array *array, const size_t item_size) { array->item_size = item_size; }

/*!
 * @ingroup ArrayManipulation
 * @brief Set the index value of the Array.
 * @param array the array which data will be altered.
 * @param index value of the index.
 */
static void Array_SetIndex(Array *array, const size_t index) { array->index = index; }

/*!
 * @ingroup ArrayManipulation
 * @brief Set the length value of the Array.
 * @param array the array which data will be altered.
 * @param capacity value of the capacity.
 */
static void Array_SetCapacity(Array *array, const size_t capacity) { array->capacity = capacity; }

/*!
 * @ingroup ArrayManipulation
 * @brief Set the data values of the Array.
 * @param array the array which data will be altered.
 * @param data new float type pointer.
 */
static void Array_SetArray(Array *array, float *data) { array->data = data; }

void Array_SetDataFromTo(const Array *array, const size_t index, const size_t numberOfElements, const void *newValues){
  assert(array != NULL && "The array pointer can be NULL!");

  assert(Array_GetArray(array) != NULL && "The array data can be NULL!");

  assert(numberOfElements > 0 && "Number of elements should more than 0!");
  assert(index + numberOfElements <= Array_GetCapacity(array) && "Start index out of range!");

  Array_SetValuesInArray(array, index, newValues, numberOfElements * Array_GetItemSize(array));
}

void Array_Append(Array *array, const void *value){
  assert(array != NULL && "The array can be NULL!");

  assert(Array_GetArray(array) != NULL && "The array data can be NULL!");

  if (Array_GetIndex(array) + 1 >= Array_GetCapacity(array)) { Array_Double(array); }

  Array_SetCoordinate(array, Array_GetIndex(array), value);
  Array_SetIndex(array, Array_GetIndex(array) + 1);
}

void Array_AppendPointer(Array *array, const void *values, const size_t pointerLength){
  assert(array != NULL && "The array can be NULL!");
  assert(values != NULL && "The input can be NULL!");

  assert(Array_GetArray(array) != NULL && "The array data can be NULL!");

  if (Array_GetIndex(array) + pointerLength - 1 >= Array_GetCapacity(array)) { Array_Double(array); }

  Array_SetDataFromTo(array, Array_GetIndex(array), pointerLength, values);
  Array_SetIndex(array, Array_GetIndex(array) + pointerLength);
}



//=============================================================================
//
//                     Array Utility Helper Functions
//

//=============================================================================

/*!
 * @ingroup ArrayUtilityHelper
 * @brief Make the data pointer based on index in an array.
 * @param array the array which data will be altered.
 * @param index the shift of elements
 */
static void* Array_GetValueIndex(const Array *array, const size_t index){
  return (char*)Array_GetArray(array) + (index * Array_GetItemSize(array));
}