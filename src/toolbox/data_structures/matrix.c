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

    matrix->rows = rows;
    matrix->cols = cols;

    matrix->matrix = NULL;
    matrix->matrix = Array_Create(matrix->rows*matrix->cols);

    return matrix;
}

Matrix* Matrix_CreateFromPointer(const float *input, const size_t rows, const size_t cols){
    /* Matrix *matrix - the output matrix pointer */
    assert(input != NULL && "input pointer should not be NULL!");

    // sizes are in format [row, col]
    Matrix *output = Matrix_Create(rows, cols);
    Array_AppendPointer(output->matrix, input, rows*cols);
    return output;
}

Matrix* MatrixMakeCopy(const Matrix *input){
    /* Matrix *matrix - the output matrix pointer */
    Matrix *output = Matrix_Create(input->rows, input->cols);

    Array_AppendPointer(output->matrix, input->matrix->data, input->rows * input->cols);
    return output;
}

void MatrixDestroy(Matrix *matrix){
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

    assert(row <= matrix->rows && "row index is out of range!");
    assert(col <= matrix->cols && "col index is out of range!");

    return Array_GetCoordinate(matrix->matrix, row * matrix->cols + col);
}

Array* Matrix_GetRow(const Matrix *matrix, const size_t row){
    assert(matrix != NULL && "matrix pointer should not be NULL!");
    assert(row >= 0 && "row index should be positive!");

    assert(row <= matrix->rows && "row index is out of range!");
    return Array_ReturnDataFromTo(matrix->matrix, row*matrix->cols, matrix->cols);
}




//=============================================================================
//
//                     Matrix Manipulation Functions
//
//=============================================================================

void Matrix_Delete(Matrix *matrix){
    if (matrix == NULL || matrix->matrix == NULL) { return; }

    Array_Destroy(matrix->matrix);
    matrix->matrix = NULL;
}


void Matrix_SetCoordinate(const Matrix *matrix, const size_t row, const size_t col, const float value){
    assert(matrix != NULL && "matrix pointer should not be NULL!");
    assert(row >= 0 && "row index should be positive!");
    assert(col >= 0 && "col index should be positive!");

    assert(row <= matrix->rows && "row index is out of range!");
    assert(col <= matrix->cols && "col index is out of range!");

    Array_SetCoordinate(matrix->matrix, row * matrix->cols + col, value);
}

void Matrix_ApplyFormula(const Matrix *matrix, float (*func_ptr)(float)){
    assert(matrix != NULL && "matrix pointer should not be NULL!");

    for(int i=0; i<matrix->rows; i++){
        for(int y=0; y<matrix->cols; y++){
            const float newValue = func_ptr(Matrix_GetCoordinate(matrix, i, y));
            Matrix_SetCoordinate(matrix, i, y, newValue);
        }
    }
}

void Matrix_Reshape(Matrix *matrix, const size_t rows, const size_t cols){
    assert(rows >= 0 && "row index should be positive!");
    assert(cols >= 0 && "col index should be positive!");

    assert(rows + cols == matrix->rows + matrix->cols);

    matrix->rows = rows;
    matrix->cols = cols;
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

    if(leftMatrix->cols != rightMatrix->rows){
        fprintf(stderr, "Error: Sizes of matrix's are incorrect\n");
        exit(EXIT_FAILURE);
    }
    Matrix *output = Matrix_Create(leftMatrix->rows, rightMatrix->cols);

    for(size_t i=0; i < rightMatrix->cols; i++){
        // start of a column of matrix
        for(size_t y=0; y < leftMatrix->rows; y++){
            // start of a row of matrix

            Matrix_SetCoordinate(output, y, i, 0);
            for(size_t x=0; x < leftMatrix->cols; x++){
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


    Matrix *output = Matrix_Create(leftMatrix->rows, rightMatrix->cols);

    for(size_t i=0; i<output->rows; i++){
        for(size_t y=0; y<output->cols; y++){
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