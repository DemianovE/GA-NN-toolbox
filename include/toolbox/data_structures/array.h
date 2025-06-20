/**
 * @file array.h
 * @brief Dynamic Array data structure public interface.
 *
 * This header defines the public interface for the Array data structure.
 * It includes type definitions and function declarations.
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




//=============================================================================
//
//                     Array Lifecycle Management Functions
//
//=============================================================================

/*!
 * @ingroup ArrayLifecycle
 * @brief Creates and initializes a new dynamic array.
 * @param length the desired length of the array.
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
 * @ingroup ArrayLifecycle
 * @brief Copy Array to a new Array pointer and return.
 * @param arrayFrom the array from which copy will be made.
 * @return A pointer to the new Array instance.
 */
Array* Array_MakeCopy(const Array *arrayFrom);

/*!
 * @ingroup ArrayLifecycle
 * @brief Destroy the pointer of the struct Array.
 * @param array the array which will be destroyed.
 */
void Array_Destroy(Array *array);



//=============================================================================
//
//                     Array Query Functions
//
//=============================================================================

/*!
 * @ingroup ArrayQuery
 * @brief Return the specific index data from Array.
 * @param array the array from which indexed value will be retrieved.
 * @param index value of the index of desired value.
 * @return A float value of the index.
 */
float Array_GetValue(const Array *array, const size_t index);

/*!
 * @ingroup ArrayQuery
 * @brief Return the array itself from Array.
 * @param array the array from which values will be retrieved.
 * @return A float type pointer array of values.
 */
float* Array_GetArray(const Array *array);

/*!
 * @ingroup ArrayQuery
 * @brief Return the array index from Array.
 * @param array the array from which value will be retrieved.
 * @return A size_t index value.
 */
size_t Array_GetIndex(const Array *array);

/*!
 * @ingroup ArrayQuery
 * @brief Return the array length from Array.
 * @param array the array from which value will be retrieved.
 * @return A size_t length value.
 */
size_t Array_GetLength(const Array *array);


//=============================================================================
//
//                     Array Manipulation Functions
//
//=============================================================================

/*!
 * @ingroup ArrayManipulation
 * @brief Get and return a slice of the array data.
 * @param array the array from which slice is made.
 * @param start starting index of the slice.
 * @param numberOfElements number of elements in the slice.
 * @return A pointer to the new Array instance with the desired data.
 * @note this was created to make the Matrix function be able to get rows.
 */
Array* Array_ReturnDataFromTo(const Array *array, const size_t start, const size_t numberOfElements);

/*!
 * @ingroup ArrayManipulation
 * @brief Set the specific index of the Array to the provided value.
 * @param array the array which data will be altered.
 * @param index value of the index of desired placement.
 * @param value the value, which should be saved.
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
 * @ingroup ArrayManipulation
 * @brief Append new value at the end of the Array.
 * @param array the array to which the value will be added.
 * @param value the value, which will be appended.
 */
void Array_Append(Array *array, const float value);

/*!
 * @ingroup ArrayManipulation
 * @brief Append the array of elements of type float to the Array.
 * @param array the array to which the values will be added.
 * @param values the pointer to array of float values, which will be appended.
 * @param pointerLength the length of the given pointer of new values.
 */
void Array_AppendPointer(Array *array, const float *values, const size_t pointerLength);



//=============================================================================
//
//                     Array Utility Helper Functions
//
//=============================================================================

/*!
 * @ingroup ArrayUtilityHelper
 * @brief Check if two arrays are equal.
 * @param arrayOne the first array to compare.
 * @param arrayTwo the second array to compare.
 */
int Array_CheckEqual(const Array *arrayOne, const Array *arrayTwo);

#endif //ARRAY_H

/**
* @defgroup Array Array
* @ingroup DataStructures
* @brief Functions of the Data Structure Array.
*/

/**
* @defgroup ArrayLifecycle Array Lifecycle
* @ingroup Array
* @brief Lifecycle functions of the Array.
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

/**
* @defgroup ArrayUtilityHelper Array Utility Helper
* @ingroup Array
* @brief Inner utility functions.
*
* This functions perform logics which can't be mapped to other groups and is static.
*
* @note this will be seperated into a separate file as it is not directly interface operations
*/