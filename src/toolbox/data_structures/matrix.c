/**
 * @file matrix.c
 * @brief Matrix data structure public interface implementation.
 *
 * This file defines all implementations of the Matrix public interface
 */

#include "matrix.h"

#include <assert.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>

static void Matrix_SetRows(Matrix* matrix, const size_t rows);
static void Matrix_SetCols(Matrix* matrix, const size_t cols);
static void Matrix_SetMatrix(Matrix* matrix, Array *array);

//=============================================================================
//
//                     Matrix Utility Helper Management Functions
//
//=============================================================================

/*!
 * @ingroup MatrixUtilityHelper
 * @brief Make the 1D index from 2D indexes for the matrix.
 * @param matrix - the matrix for each index will be created
 * @param row the desired rows.
 * @param col the desired columns.
 * @return Am 1D index.
 */
static size_t Matrix_MakeIndex(const Matrix * matrix, const size_t row, const size_t col){
    return row * Matrix_GetCols(matrix) + col;
}

//=============================================================================
//
//                     Matrix Lifecycle Management Functions
//
//=============================================================================

Matrix* Matrix_Create(const size_t rows, const size_t cols){
    /* Matrix *matrix - the output matrix pointer */
    assert(rows > 0 && "array of sizes value x should be positive!");
    assert(cols > 0 && "array of sizes value y should be positive!");

    Matrix *matrix = NULL;
    matrix = malloc(sizeof(Array));
    if (matrix == NULL){ perror("Failed to allocate Matrix"); exit(EXIT_FAILURE); }

    Matrix_SetRows(matrix, rows);
    Matrix_SetCols(matrix, cols);

    Matrix_SetMatrix(matrix, NULL);
    Matrix_SetMatrix(matrix, Array_Create(matrix->rows*matrix->cols));

    return matrix;
}

Matrix* Matrix_CreateFromPointer(const float *input, const size_t rows, const size_t cols){
    /* Matrix *matrix - the output matrix pointer */
    assert(input != NULL && "input pointer should not be NULL!");

    // sizes are in format [row, col]
    Matrix *output = Matrix_Create(rows, cols);
    Array_AppendPointer(Matrix_GetMatrix(output), input, rows*cols);
    return output;
}

Matrix* Matrix_MakeCopy(const Matrix *input){
    /* Matrix *matrix - the output matrix pointer */
    Matrix *output = Matrix_Create(Matrix_GetRows(input), Matrix_GetCols(input));

    Array_AppendPointer(Matrix_GetMatrix(output), Array_GetArray(Matrix_GetMatrix(input)), Matrix_GetRows(input) * Matrix_GetCols(input));
    return output;
}

void Matrix_Destroy(Matrix *matrix){
    if (matrix == NULL) { return; }

    Matrix_Delete(matrix);
    free(matrix);
}



//=============================================================================
//
//                     Matrix Query Functions
//
//=============================================================================

float Matrix_GetCoordinate(const Matrix *matrix, const size_t row, const size_t col){
    assert(matrix != NULL && "matrix pointer should not be NULL!");
    assert(row >= 0 && "row index should be positive!");
    assert(col >= 0 && "col index should be positive!");

    assert(row <= Matrix_GetRows(matrix) && "row index is out of range!");
    assert(col <= Matrix_GetCols(matrix) && "col index is out of range!");

    const size_t index = Matrix_MakeIndex(matrix, row, col);
    return Array_GetValue(Matrix_GetMatrix(matrix), index);
}

Array* Matrix_GetRow(const Matrix *matrix, const size_t row){
    assert(matrix != NULL && "matrix pointer should not be NULL!");
    assert(row >= 0 && "row index should be positive!");

    assert(row <= Matrix_GetRows(matrix) && "row index is out of range!");
    return Array_ReturnDataFromTo(Matrix_GetMatrix(matrix), row * Matrix_GetCols(matrix), Matrix_GetCols(matrix));
}

Array* Matrix_GetMatrix(const Matrix *matrix){
    return matrix->matrix;
}

size_t Matrix_GetRows(const Matrix *matrix){
    return matrix->rows;
}

size_t Matrix_GetCols(const Matrix *matrix){
    return matrix->cols;
}



//=============================================================================
//
//                     Matrix Manipulation Functions
//
//=============================================================================

void Matrix_Delete(Matrix *matrix){
    if (matrix == NULL || Matrix_GetMatrix(matrix) == NULL) { return; }

    Array_Destroy(Matrix_GetMatrix(matrix));
    Matrix_SetMatrix(matrix, NULL);
}

/*!
 * @ingroup MatrixManipulation
 * @brief Change matrix row count.
 * @param matrix the matrix which data is to be modified.
 * @param rows the new rows count value.
 */
static void Matrix_SetRows(Matrix* matrix, const size_t rows){
    matrix->rows = rows;
}

/*!
 * @ingroup MatrixManipulation
 * @brief Change matrix col count.
 * @param matrix the matrix which data is to be modified.
 * @param cols the new cols count value.
 */
static void Matrix_SetCols(Matrix* matrix, const size_t cols){
    matrix->cols = cols;
}

/*!
 * @ingroup MatrixManipulation
 * @brief Change matrix array.
 * @param matrix the matrix which data is to be modified.
 * @param array the new array value.
 */
static void Matrix_SetMatrix(Matrix* matrix, Array *array){
    matrix->matrix = array;
}

void Matrix_SetCoordinate(const Matrix *matrix, const size_t row, const size_t col, const float value){
    assert(matrix != NULL && "matrix pointer should not be NULL!");
    assert(row >= 0 && "row index should be positive!");
    assert(col >= 0 && "col index should be positive!");

    assert(row <= Matrix_GetRows(matrix) && "row index is out of range!");
    assert(col <= Matrix_GetCols(matrix) && "col index is out of range!");

    Array_SetCoordinate(Matrix_GetMatrix(matrix), row * Matrix_GetCols(matrix) + col, value);
}

void Matrix_SetRow(const Matrix *matrix, const size_t row, const float *data){
    assert(matrix != NULL && "matrix pointer should not be NULL!");
    assert(row >= 0 && "row index should be positive!");
    assert(data != NULL && "data pointer should not be NULL!");

    Array_SetDataFromTo(Matrix_GetMatrix(matrix), Matrix_MakeIndex(matrix, row, 0), Matrix_GetCols(matrix), data);
}

void Matrix_ApplyFormula(const Matrix *matrix, float (*func_ptr)(float)){
    assert(matrix != NULL && "matrix pointer should not be NULL!");

    for(int i = 0; i < Matrix_GetRows(matrix); i++){
        for(int y = 0; y < Matrix_GetCols(matrix); y++){
            const float newValue = func_ptr(Matrix_GetCoordinate(matrix, i, y));
            Matrix_SetCoordinate(matrix, i, y, newValue);
        }
    }
}

void Matrix_Reshape(Matrix *matrix, const size_t rows, const size_t cols){
    assert(rows >= 0 && "row index should be positive!");
    assert(cols >= 0 && "col index should be positive!");

    assert(rows * cols == Matrix_GetRows(matrix) * Matrix_GetCols(matrix));

    Matrix_SetRows(matrix, rows);
    Matrix_SetCols(matrix, cols);
}



//=============================================================================
//
//                     Matrix Math Functions
//
//=============================================================================

Matrix* Matrix_Multiply(const Matrix *leftMatrix, const Matrix *rightMatrix){
    /* Matrix *matrix - the output matrix pointer */

    assert(leftMatrix != NULL && "leftMatrix pointer should not be NULL!");
    assert(rightMatrix != NULL && "rightMatrix pointer should not be NULL!");

    if(Matrix_GetCols(leftMatrix) != Matrix_GetRows(rightMatrix)){
        fprintf(stderr, "Error: Sizes of matrix's are incorrect\n");
        exit(EXIT_FAILURE);
    }
    Matrix *output = Matrix_Create(Matrix_GetRows(leftMatrix), Matrix_GetCols(rightMatrix));

    for(size_t i=0; i < Matrix_GetCols(rightMatrix); i++){
        // start of a column of matrix
        for(size_t y=0; y < Matrix_GetRows(leftMatrix); y++){
            // start of a row of matrix

            Matrix_SetCoordinate(output, y, i, 0);
            for(size_t x=0; x < Matrix_GetCols(leftMatrix); x++){
                const float newValue = Matrix_GetCoordinate(rightMatrix, y, x) * Matrix_GetCoordinate(leftMatrix, x, i);
                Matrix_SetCoordinate(output, y, i, newValue);
            }
        }
    }
    return output;
}

static Matrix* Matrix_SubstAdd(const Matrix *leftMatrix, const Matrix *rightMatrix, const size_t type){
    /* Matrix *matrix - the output matrix pointer */
    assert(leftMatrix != NULL && "leftMatrix pointer should not be NULL!");
    assert(rightMatrix != NULL && "rightMatrix pointer should not be NULL!");


    Matrix *output = Matrix_Create(Matrix_GetRows(leftMatrix), Matrix_GetCols(rightMatrix));

    for(size_t i=0; i < Matrix_GetRows(output); i++){
        for(size_t y=0; y < Matrix_GetCols(output); y++){
            const float leftValue = Matrix_GetCoordinate(leftMatrix, i, y);
            const float rightValue = Matrix_GetCoordinate(rightMatrix, i, y);

            const float newValue = (type == 0) ? leftValue - rightValue : leftValue + rightValue;
            Matrix_SetCoordinate(output, i, y, newValue);
        }
    }
    return output;
}

Matrix* Matrix_Add(const Matrix *leftMatrix, const Matrix *rightMatrix){
    return Matrix_SubstAdd(leftMatrix, rightMatrix, 1);
}

Matrix* Matrix_Subs(const Matrix *leftMatrix, const Matrix *rightMatrix){
    return Matrix_SubstAdd(leftMatrix, rightMatrix, 0);
}