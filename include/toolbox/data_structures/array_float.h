/**
 * @file array_float.h
 * @brief Dynamic Array data structure public interface with Float type cast.
 *
 * This header defines the public interface for the float type generic Array
 * It includes type definitions and function declarations.
 * This interface is a wrap on top of the @ref array.h generic array
 */

#ifndef ARRAY_FLOAT_H
#define ARRAY_FLOAT_H
#include "array.h"

//=============================================================================
//
//                     Array Lifecycle Management Functions
//
//=============================================================================

/*!
 * @ingroup ArrayFloatLifecycle
 * @brief Creates and initializes a new dynamic array with type float.
 * @param capacity the desired capacity of the array.
 * @return A pointer to the new Array instance.
 */
static inline Array* ArrayFloat_Create(const size_t capacity) { return Array_Create(capacity, sizeof(float)); }

/*!
 * @ingroup ArrayFloatLifecycle
 * @brief Concatenates two arrays and initializes a new dynamic array.
 * @param array1 the array to be concatenated.
 * @param array2 the array to be concatenated.
 * @return A pointer to the new Array instance.
 */
static inline Array* ArrayFloat_Concat(const Array* array1, const Array* array2) { return Array_Concat(array1, array2); }

/*!
 * @ingroup ArrayFloatLifecycle
 * @brief Copy Array to a new Array pointer and return.
 * @param arrayFrom the array from which copy will be made.
 * @return A pointer to the new Array instance.
 */
static inline Array* ArrayFloat_MakeCopy(const Array *arrayFrom) { return Array_MakeCopy(arrayFrom); }

/*!
 * @ingroup ArrayFloatLifecycle
 * @brief Destroy the pointer of the struct Array.
 * @param array the array which will be destroyed.
 */
static inline void ArrayFloat_Destroy(Array *array) { Array_Destroy(array); }

//=============================================================================
//
//                     Array Query Functions
//
//=============================================================================

/*!
 * @ingroup ArrayFloatQuery
 * @brief Return the specific index data from Array and make float cast.
 * @param array the array from which indexed value will be retrieved.
 * @param index value of the index of desired value.
 * @return A float value.
 */
float ArrayFloat_GetValue(const Array *array, const size_t index);

/*!
 * @ingroup ArrayFloatQuery
 * @brief Return the array itself from Array and make float cast.
 * @param array the array from which values will be retrieved.
 * @return A float ype array pointer.
 */
static inline float* ArrayFloat_GetArray(const Array *array) { return (float*)Array_GetArray(array); }

/*!
 * @ingroup ArrayFloatQuery
 * @brief Return the array item size from Array.
 * @param array the array from which value will be retrieved.
 * @return A size_t item size value.
 */
static inline size_t ArrayFloat_GetItemSize(const Array *array) { return Array_GetItemSize(array); }

/*!
 * @ingroup ArrayFloatQuery
 * @brief Return the array index from Array.
 * @param array the array from which value will be retrieved.
 * @return A size_t index value.
 */
static inline size_t ArrayFloat_GetIndex(const Array *array) { return Array_GetIndex(array); }

/*!
 * @ingroup ArrayFloatQuery
 * @brief Return the array capacity from Array.
 * @param array the array from which value will be retrieved.
 * @return A size_t capacity value.
 */
static inline size_t ArrayFloat_GetCapacity(const Array *array) { return Array_GetCapacity(array); }

//=============================================================================
//
//                     Array Manipulation Functions
//
//=============================================================================

/*!
 * @ingroup ArrayFloatManipulation
 * @brief Get and return a slice of the array data.
 * @param array the array from which slice is made.
 * @param start starting index of the slice.
 * @param numberOfElements number of elements in the slice.
 * @return A pointer to the new Array instance with the desired data.
 * @note this was created to make the Matrix function be able to get rows.
 */
static inline Array* ArrayFloat_ReturnDataFromTo(const Array *array, const size_t start, const size_t numberOfElements) { return Array_ReturnDataFromTo(array, start, numberOfElements); }

/*!
 * @ingroup ArrayFloatManipulation
 * @brief Set the specific index of the Array to the provided value.
 * @param array the array which data will be altered.
 * @param index value of the index of desired placement.
 * @param value the value, which should be saved.
 */
static inline void ArrayFloat_SetCoordinate(const Array *array, const size_t index, const float value) { Array_SetCoordinate(array, index, &value); }

/*!
 * @ingroup ArrayFloatManipulation
 * @brief Set several new values at specified position.
 * @param array the array which will be manipulated.
 * @param start starting index of the slice.
 * @param numberOfElements number of elements in the slice.
 * @param values the float type pointer to the data to be added.
 */
static inline void ArrayFloat_SetDataFromTo(const Array *array, const size_t start, const size_t numberOfElements, const float *values) { Array_SetDataFromTo(array, start, numberOfElements, values); }

/*!
 * @ingroup ArrayFloatManipulation
 * @brief Append new value at the end of the Array.
 * @param array the array to which the value will be added.
 * @param value the value, which will be appended.
 */
static inline void ArrayFloat_Append(Array *array, const float value) { Array_Append(array, &value); }

/*!
 * @ingroup ArrayFloatManipulation
 * @brief Append the array of elements of type float to the Array.
 * @param array the array to which the values will be added.
 * @param values the pointer to array of float values, which will be appended.
 * @param pointerLength the length of the given pointer of new values.
 */
static inline void ArrayFloat_AppendPointer(Array *array, const float *values, const size_t pointerLength) { Array_AppendPointer(array, values, pointerLength); }

//=============================================================================
//
//                     Array Utility Helper Functions
//
//=============================================================================

/*!
 * @ingroup ArrayFloatUtilityHelper
 * @brief Check if two arrays are equal.
 * @param arrayOne the first array to compare.
 * @param arrayTwo the second array to compare.
 */
static inline int ArrayFloat_CheckEqual(const Array *arrayOne, const Array *arrayTwo) {return Array_CheckEqual(arrayOne, arrayTwo); }

#endif //ARRAY_FLOAT_H

/**
* @defgroup ArrayFloat Array Float
* @ingroup Array
* @brief Functions of the Data Structure Array cast Float.
*/

/**
* @defgroup ArrayFloatLifecycle Array Lifecycle
* @ingroup ArrayFloat
* @brief Lifecycle functions of the Array.
*
* This functions create/destroy/copy Array
*/

/**
* @defgroup ArrayFloatQuery Array Query
* @ingroup ArrayFloat
* @brief Query of the Data Structure Array.
*
* This functions make read-only operations on data
*/

/**
* @defgroup ArrayFloatManipulation Array Manipulation
* @ingroup ArrayFloat
* @brief Manipulation of the Data Structure Array.
*
* This functions make write operations on data
*/

/**
* @defgroup ArrayFloatUtilityHelper Array Utility Helper
* @ingroup ArrayFloat
* @brief Inner utility functions.
*
* This functions perform logics which can't be mapped to other groups and is static.
*
* @note this will be seperated into a separate file as it is not directly interface operations
*/