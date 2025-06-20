#include "matrix.h"
#include "activation_fnc.h"

#include <stdlib.h>
#include <stdio.h>
#include "unity/unity.h"

// define extern matrix's for the setUp
Matrix *desiredOne;
Matrix *desiredTwo;

Matrix *resultOne;
Matrix *resultTwo;

static void printMatrix(const Matrix *matrix, char *name){
  printf("result of the %s:\n", name);
  for (int x = 0; x < Matrix_GetRows(matrix); x++){
    for (int y = 0; y < Matrix_GetCols(matrix); y++) printf("%f ", Matrix_GetCoordinate(matrix, x, y));
  }
  printf("\n");
}

static void compareMatrices(const Matrix *a, const Matrix *b){
  // check if both matrix's have the same size
  TEST_ASSERT_EQUAL(Matrix_GetRows(a), Matrix_GetRows(b));
  TEST_ASSERT_EQUAL(Matrix_GetCols(a), Matrix_GetCols(b));

  TEST_ASSERT_EQUAL_FLOAT_ARRAY(Array_GetArray(Matrix_GetMatrix(a)), Array_GetArray(Matrix_GetMatrix(b)), Matrix_GetRows(a) * Matrix_GetCols(a));
}

void setUp(void){
  desiredOne = Matrix_Create(1, 4);
  desiredTwo = Matrix_Create(1, 4);

  resultOne = Matrix_Create(1, 4);
  resultTwo = Matrix_Create(1, 4);

  const float data[] = {1.0f, 1.0f, 1.0f, 1.0f};

  Matrix_SetRow(resultOne, 0, data);
  Matrix_SetRow(resultTwo, 0, data);

  Matrix_Reshape(resultOne, 2, 2);
  Matrix_Reshape(resultTwo, 2, 2);
}

void tearDown(void){
  Matrix_Destroy(desiredOne);
  Matrix_Destroy(desiredTwo);

  Matrix_Destroy(resultOne);
  Matrix_Destroy(resultTwo);
}

void testMatrix_AddSub(void){
  const float dataOne[] = {2.0f, 2.0f, 2.0f, 2.0f};
  Matrix_SetRow(desiredOne, 0, dataOne);
  Matrix_Reshape(desiredOne, 2, 2);

  const float dataTwo[] = {.0f, .0f, .0f, .0f};
  Matrix_SetRow(desiredTwo, 0, dataTwo);
  Matrix_Reshape(desiredTwo, 2, 2);

  // type: 0 - sub, 1 - add
  Matrix *add = Matrix_Add(resultOne, resultTwo);
  printMatrix(add, "add");

  // type: 0 - sub, 1 - add
  Matrix *sub = Matrix_Subs(resultOne, resultTwo);
  printMatrix(sub, "sub");

  compareMatrices(add, desiredOne);
  compareMatrices(sub, desiredTwo);

  Matrix_Destroy(add);
  Matrix_Destroy(sub);
}

void testMatrix_Multiply(void){
  const float data[] = {1.0f, 1.0f, 1.0f, 1.0f};
  Matrix_SetRow(desiredOne, 0, data);
  Matrix_Reshape(desiredOne, 2, 2);

  Matrix *mult = Matrix_Multiply(resultOne, resultTwo);
  printMatrix(mult , "multiply");

  compareMatrices(mult, desiredOne);
  Matrix_Destroy(mult);
}

void testMatrix_AllValuesFormula(void){
  float (*func_ptr_tan)(float);
  selectTangActivationFunction(&func_ptr_tan);

  float (*func_ptr_sigma)(float);
  selectSigmActivationFunction(&func_ptr_sigma);

  const float valueOne = func_ptr_tan(1);
  const float dataOne[] = {valueOne, valueOne, valueOne, valueOne};
  Matrix_SetRow(desiredOne, 0, dataOne);
  Matrix_Reshape(desiredOne, 2, 2);

  const float valueTwo = func_ptr_sigma(1);
  const float dataTwo[] = {valueTwo, valueTwo, valueTwo, valueTwo};
  Matrix_SetRow(desiredTwo, 0, dataTwo);
  Matrix_Reshape(desiredTwo, 2, 2);

  Matrix_ApplyFormula(resultOne, func_ptr_tan);
  printMatrix(resultOne, "tan");

  Matrix_ApplyFormula(resultTwo, func_ptr_sigma);
  printMatrix(resultTwo, "sigma");

  compareMatrices(resultOne, desiredOne);
  compareMatrices(resultTwo, desiredTwo);

  // free function pointers
  func_ptr_tan   = NULL;
  func_ptr_sigma = NULL;
}

void testMatrix_CreateFromPointer(void){
  const float data[] = {1.0f, 2.0f, 3.0f, 4.0f};
  Matrix_SetRow(desiredOne, 0, data);
  Matrix_Reshape(desiredOne, 2, 2);

  const float dataPointer[] = {1.0f, 2.0f, 3.0f, 4.0f};

  Matrix *matrix = Matrix_CreateFromPointer(dataPointer, 2, 2);
  printMatrix(matrix, "matrix from pointer");

  compareMatrices(matrix, desiredOne);
  Matrix_Destroy(matrix);
}

void testMatrix_FullyCoppyMatrix(void){
  const float data[] = {1.0f, 2.0f, 3.0f, 4.0f};
  Matrix_SetRow(desiredOne, 0, data);
  Matrix_Reshape(desiredOne, 2, 2);

  Matrix *matrix = Matrix_MakeCopy(desiredOne);
  compareMatrices(matrix, desiredOne);

  Matrix_Destroy(matrix);
}

int main(void) {
  UNITY_BEGIN();

  RUN_TEST(testMatrix_AddSub);
  RUN_TEST(testMatrix_Multiply);
  RUN_TEST(testMatrix_AllValuesFormula);
  RUN_TEST(testMatrix_CreateFromPointer);
  RUN_TEST(testMatrix_FullyCoppyMatrix);

  return UNITY_END();
}