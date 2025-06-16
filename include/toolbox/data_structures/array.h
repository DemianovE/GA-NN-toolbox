/*
 * Created by egor on 13.06.25. :)
 * Please note, this DS is an implementation of the Dynamic array with the active size and index
 * THis is made to avoid issue with the incorrect size sharing.
 *
 * But most of the functions in the toolbox always have the fixed size. So the Dynamic part is a precaution in case it will be necessary
 * For the same reason of very specific usage, the following Interface is not a full implementation of the Array logic, avoiding unnecessary functions
 */

#ifndef ARRAY_H
#define ARRAY_H
#include <stddef.h>

typedef struct Array {
  float *data; // the array itself
  size_t length; // the length og the array
  size_t index; // the index of the next free cell of the array (used for inner size calculations)
} Array;

/*
 * This function is used to create new array
 * Input:
 *    const size_t length - the number of elements in the array
 * Output;
 *    The function returns the pointer to the structure of type Array
 */
Array* ArrayCreate(const size_t length);

/*
 * This is used to concatenate two arrays
 * Input:
 *    const Array* array1 - the array to eb concatenated first
 *    const Array* array2 - the array to eb concatenated second
 * Output;
 *    The function returns the pointer to the structure of type Array
 */
Array* ArrayConcat(const Array* array1, const Array* array2);

/*
 * This is used to destroy the struct Array
 * Input:
 *    Array *array - the array to be destroyed
 * Output;
 *    The function has no returns but manipulates a given pointer
 */
void ArrayDestroy(Array *array);

/*
 * This is used to append new item to the array
 * Input:
 *    Array *array - the array to be destroyed
 * Output;
 *    The function has no returns but manipulates a given pointer
 */
void ArrayAppend(Array *array, const float input);

/*
 * This is used to append a list of items to the array
 * Input:
 *    Array *array - the array to be destroyed
 *    const float *input - the items to be appended
 *    const size_t pointerLength - size of the new data
 * Output;
 *    The function has no returns but manipulates a given pointer
 */
void ArrayAppendPointer(Array *array, const float *input, const size_t pointerLength);

#endif //ARRAY_H
