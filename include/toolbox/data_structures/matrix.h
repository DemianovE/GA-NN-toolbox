/**
 * @file matrix.h
 * @brief Matrix data structure public interface.
 *
 * This header defines the public interface for the Matrix data structure.
 * It includes type definitions and function declarations.
 */

#ifndef MATRIX_H
#define MATRIX_H

#include "array.h"

/**
 * @struct Matrix
 * @brief Internal definition of the Matrix structure.
 * @ingroup Matrix
 * @details
 * This structure holds the necessary components for the matrix:
 * It contains the pointer to the array structure and configuration number of columns and rows.
 *
 * @section MatrixStructDetails Detailed Structure Members
 * This section provides a detailed description of each member of the `Matrix` struct.
 *
 * @var Array* Array::matrix
 * A pointer to the dynamically allocated structure Array.
 * This buffer holds the Array which is responsible for actual data
 *
 * @var size_t Array::rows
 * The total number of rows in the Matrix
 * This value is used in the 1D array to 2D Matrix conversion as well as configurations
 *
 * @var size_t Array::cols
 * The total number of cols in the Matrix
 * This value is used in the 1D array to 2D Matrix conversion as well as configurations
 */
typedef struct Matrix{
    Array *matrix; // the matrix array itself

    size_t rows; // the number of rows
    size_t cols; // the number of columns
} Matrix;



//=============================================================================
//
//                     Matrix Lifecycle Management Functions
//
//=============================================================================

/*!
 * @ingroup MatrixLifecycle
 * @brief Creates and initializes a new matrix.
 * @param rows the desired number of rows.
 * @param cols the desired number of columns.
 * @return A pointer to the new Matrix instance.
 */
Matrix* Matrix_Create(const size_t rows, const size_t cols);

/*!
 * @ingroup MatrixLifecycle
 * @brief Creates and initializes a new matrix as well as populate it with values from the float tape pointer.
 * @param input the type float pointer with data to be used
 * @param rows the desired number of rows.
 * @param cols the desired number of columns.
 * @return A pointer to the new Matrix instance.
 */
Matrix* Matrix_CreateFromPointer(const float *input, const size_t rows, const size_t cols);

/*!
 * @ingroup MatrixLifecycle
 * @brief Make and initialize a copy of the matrix provided.
 * @param source the matrix pointer to be copied
 * @return A pointer to the new Matrix instance.
 */
Matrix* Matrix_MakeCopy(const Matrix *source);

/*!
 * @ingroup MatrixLifecycle
 * @brief Destroy matrix pointer.
 * @param matrix the matrix to be destroyed
 */
void Matrix_Destroy(Matrix *matrix);



//=============================================================================
//
//                     Matrix Query Functions
//
//=============================================================================

/*!
 * @ingroup MatrixQuery
 * @brief Return the values of the matrix as specific 2D coordinate from 1D array.
 * @param matrix the matrix which value will be returned
 * @param row the desired row.
 * @param col the desired column.
 * @return A float value at the coordinate from matrix
 */
float Matrix_GetCoordinate(const Matrix *matrix, const size_t row, const size_t col);

/*!
 * @ingroup MatrixQuery
 * @brief Return the type float pointer of the matrix with values of one row.
 * @param matrix the matrix which value will be returned
 * @param row the desired row.
 * @return An Array instance with the row objects
 */
Array* Matrix_GetRow(const Matrix *matrix, const size_t row);

//=============================================================================
//
//                     Matrix Manipulation Functions
//
//=============================================================================

/*!
 * @ingroup MatrixManipulation
 * @brief Delete the data of the matrix.
 * @param matrix the matrix which data is to be deleted
 */
void Matrix_Delete(Matrix *matrix);

/*!
 * @ingroup MatrixManipulation
 * @brief Set the value in the matrix at specific coordinated to the provided.
 * @param matrix the matrix which data is to be modified
 * @param row the desired row.
 * @param col the desired column.
 * @param value the value to be set.
 */
void Matrix_SetCoordinate(const Matrix *matrix, const size_t row, const size_t col, const float value);

/*!
 * @ingroup MatrixManipulation
 * @brief Apply a function to all values of the matrix.
 * @param matrix the matrix which data is to be modified
 * @param func_ptr the function to be applied to all values.
 */
void Matrix_ApplyFormula(const Matrix *matrix, float (*func_ptr)(float));

/*!
 * @ingroup MatrixManipulation
 * @brief Change the dimensions of the matrix.
 * @param matrix the matrix which data is to be modified
 * @param rows the desired new row count.
 * @param cols the desired new column count.
 *
 * @note Historically, when matrix was float** the reshaping was O(n^2) change to the new matrix. Now it is just a change of variable for index formula
 */
void Matrix_Reshape(Matrix *matrix, const size_t rows, const size_t cols);



//=============================================================================
//
//                     Matrix Math Functions
//
//=============================================================================

/*!
 * @ingroup MatrixManipulation
 * @brief Perform matrix multiplication and return the resulting initialized matrix instance.
 * @param leftMatrix the left matrix of the multiplication.
 * @param rightMatrix the right matrix of the multiplication.
 * @return A pointer to the new Matrix instance.
 */
Matrix* Matrix_Multiply(const Matrix *leftMatrix, const Matrix *rightMatrix);

/*!
 * @ingroup MatrixManipulation
 * @brief Perform matrix addition and return the resulting initialized matrix instance.
 * @param leftMatrix the left matrix of the multiplication.
 * @param rightMatrix the right matrix of the multiplication.
 * @return A pointer to the new Matrix instance.
 */
Matrix* Matrix_Add(const Matrix *leftMatrix, const Matrix *rightMatrix);

/*!
 * @ingroup MatrixManipulation
 * @brief Perform matrix subtraction and return the resulting initialized matrix instance.
 * @param leftMatrix the left matrix of the multiplication.
 * @param rightMatrix the right matrix of the multiplication.
 * @return A pointer to the new Matrix instance.
 */
Matrix* Matrix_Subs(const Matrix *leftMatrix, const Matrix *rightMatrix);

#define CLEAR_MATRIX_UNTIL(matrix, count_to_free) do { \
    if (matrix != NULL) {                              \
        for (int i = 0; i < (count_to_free); i++) {    \
            if (matrix[i] != NULL) {                   \
                free(matrix[i]);                       \
                matrix[i] = NULL;                      \
            }                                          \
        }                                              \
    }                                                  \
} while (0)

#endif

/**
* @defgroup Matrix Matrix
* @ingroup DataStructures
* @brief Functions of the Data Structure Array.
*/

/**
* @defgroup MatrixLifecycle Matrix Lifecycle
* @ingroup Matrix
* @brief Lifecycle functions of the Matrix.
*
* This functions create/destroy/copy Matrix
*/

/**
* @defgroup MatrixQuery Matrix Query
* @ingroup Matrix
* @brief Query of the Data Structure Matrix.
*
* This functions make read-only operations on data
*/

/**
* @defgroup MatrixManipulation Matrix Manipulation
* @ingroup Matrix
* @brief Manipulation of the Data Structure Matrix.
*
* This functions make write operations on data
*/

/**
* @defgroup MatrixMath Matrix Math
* @ingroup Matrix
* @brief Math Operations of the Data Structure Matrix.
*
* This functions perform math operations
*
* @note this will be seperated into a separate file as it is not directly interface operations
*/