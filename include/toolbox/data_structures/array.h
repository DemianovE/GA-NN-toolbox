/**
* @file array.h
 * @brief Dynamic Array data structure public interface.
 *
 * This header defines the public interface for the Array data structure.
 * It includes type definitions and function declarations.
 */

/*
 * Created by egor on 13.06.25. :)
 * Please note, this DS is an implementation of the Dynamic array with the active size and index
 * This is made to avoid issue with the incorrect size sharing.
 *
 * But most of the functions in the toolbox always have the fixed size. So the Dynamic part is a precaution in case it will be necessary
 * For the same reason of very specific usage, the following Interface is not a full implementation of the Array logic, avoiding unnecessary functions
 */

#ifndef ARRAY_H
#define ARRAY_H
#include <stddef.h>

/**
 * @struct Array
 * @brief Internal definition of the Dynamic Array structure.
 * @ingroup Array
 * @details
 * This structure holds the necessary components for the dynamic array:
 * It contains the pointer to the dynamically allocated data buffer,
 * the current number of elements stored, and the total allocated capacity.
 *
 * @section ArrayStructDetails Detailed Structure Members
 * This section provides a detailed description of each member of the `Array` struct.
 *
 * @var float* Array::data
 * A pointer to the dynamically allocated block of `float` elements.
 * This buffer holds the actual elements of the array.
 *
 * @var size_t Array::length
 * The total allocated memory capacity of the array (number of elements).
 * This value determines how many elements the `data` buffer can currently hold
 * without requiring a reallocation.
 *
 * @var size_t Array::index
 * The current number of elements actually stored and used in the array.
 * This value represents the logical size of the array, indicating the next
 * available position for new elements.
 */
typedef struct Array {
  float *data; // the array itself
  size_t length; // the length og the array
  size_t index; // the index of the next free cell of the array (used for inner size calculations)
} Array;

/*!
 * @ingroup ArrayLifecycle
 * @brief Creates and initializes a new dynamic array.
 * @param length The desired length of the array.
 * @return A pointer to the new Array instance.
 */
Array* Array_Create(const size_t length);

/*!
 * @ingroup ArrayLifecycle
 * @brief Concatenates two arrays and initializes a new dynamic array.
 * @param array1 the array to be concatenated.
 * @param array2 the array to be concatenated.
 * @return A pointer to the new Array instance.
 */
Array* Array_Concat(const Array* array1, const Array* array2);

/*!
 * @ingroup ArrayManipulation
 * @brief Get and return a slice of the array data.
 * @param array the array from which slice is made.
 * @param start starting index of the slice.
 * @param numberOfElements number of elements in the slice.
 * @return A pointer to the new Array instance with the desired data.
 * @note this was created to make the Matrix function be able to get rows
 */
Array* Array_ReturnDataFromTo(const Array *array, const size_t start, const size_t numberOfElements);

/*!
 * @ingroup ArrayLifecycle
 * @brief Copy Array to a new Array pointer and return.
 * @param arrayFrom the array from which copy will be made.
 * @return A pointer to the new Array instance.
 */
Array* Array_MakeCopy(const Array *arrayFrom);

/*!
 * @ingroup ArrayQuery
 * @brief Return the specific index data from Array.
 * @param array the array from which indexed value will be retrieved.
 * @param index value of the index of desired value.
 * @return A float value of the index.
 */
float Array_GetCoordinate(const Array *array, const size_t index);

/*!
 * @ingroup ArrayManipulation
 * @brief Set the specific index of the Array to the provided value.
 * @param array the array which data will be altered.
 * @param index value of the index of desired placement.
 * @param value the value, which should be saved
 */
void Array_SetCoordinate(const Array *array, const size_t index, const float value);

/*!
 * @ingroup ArrayManipulation
 * @brief Set several new values at specified position.
 * @param array the array which will be manipulated.
 * @param start starting index of the slice.
 * @param numberOfElements number of elements in the slice.
 * @param values the float type pointer to the data to be added.
 */
void Array_SetDataFromTo(const Array *array, const size_t start, const size_t numberOfElements, const float *values);

/*!
 * @ingroup ArrayLifecycle
 * @brief Destroy the pointer of the struct Array.
 * @param array the array which will be destroyed.
 */
void Array_Destroy(Array *array);

/*!
 * @ingroup ArrayManipulation
 * @brief Append new value at the end of the Array.
 * @param array the array to which the value will be added.
 * @param value the value, which will be appended
 */
void Array_Append(Array *array, const float value);

/*!
 * @ingroup ArrayManipulation
 * @brief Append array of elmeents of type float to the Array.
 * @param array the array to which the values will be added.
 * @param values the pointer to array of float values, which will be appended
 * @param pointerLength the length of the given pointer of new values
 */
void Array_AppendPointer(Array *array, const float *values, const size_t pointerLength);

#endif //ARRAY_H


/**
* @defgroup Array Array
* @ingroup DataStructures
* @brief Functions of the Data Structure Array.
*/

/**
* @defgroup ArrayLifecycle Array Lifecycle
* @ingroup Array
* @brief Livsycle functions of the Array.
*
* This functions create/destroy/copy Array
*/

/**
* @defgroup ArrayQuery Array Query
* @ingroup Array
* @brief Query of the Data Structure Array.
*
* This functions make read-only operations on data
*/

/**
* @defgroup ArrayManipulation Array Manipulation
* @ingroup Array
* @brief Manipulation of the Data Structure Array.
*
* This functions make write operations on data
*/