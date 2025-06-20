//
// Created by egor on 16.06.25.
//
#include "array.h"

#include <stdlib.h>
#include <stdio.h>
#include "unity/unity.h"

Array *usedArrayOne;
Array *usedArrayTwo;

void setUp(void){
  const float values[] = {2.0f, 3.0f};

  usedArrayOne = Array_Create(2);
  usedArrayTwo = Array_Create(2);

  Array_AppendPointer(usedArrayOne, values, 2);
  Array_AppendPointer(usedArrayTwo, values, 2);
}

void tearDown(void){
  Array_Destroy(usedArrayOne);
  Array_Destroy(usedArrayTwo);
}


void testArray_Concat(void){
  Array *newArray = Array_Concat(usedArrayOne, usedArrayTwo);
  const float correct[] = {2.0f, 3.0f, 2.0f, 3.0f};

  TEST_ASSERT_EQUAL_FLOAT_ARRAY(correct, Array_GetArray(newArray), 4);

  Array_Destroy(newArray);
}

void testArray_Append(void){
  Array_Append(usedArrayOne, 2.0f);
  const float correct[] = {2.0f, 3.0f, 2.0f};

  TEST_ASSERT_EQUAL_FLOAT_ARRAY(correct, Array_GetArray(usedArrayOne), 3);
  TEST_ASSERT_EQUAL(Array_GetLength(usedArrayOne), 4);
  TEST_ASSERT_EQUAL(Array_GetIndex(usedArrayOne), 3);
}

void testArray_SetCoordinate(void){
  Array_SetCoordinate(usedArrayOne, 0, 4.0f);
  const float correct[] = {4.0f, 3.0f};

  TEST_ASSERT_EQUAL_FLOAT_ARRAY(Array_GetArray(usedArrayOne), correct, 2);
}

void testArray_SetDataFromTo(void){
  const float data[] = {5.0f, 6.0f};
  Array_SetDataFromTo(usedArrayOne, 0, 2, data);

  TEST_ASSERT_EQUAL_FLOAT_ARRAY(Array_GetArray(usedArrayOne), data, 2);
}

void testArray_Copy(void){
  Array *copyArray = Array_MakeCopy(usedArrayOne);
  TEST_ASSERT_TRUE(Array_CheckEqual(copyArray, usedArrayOne));
  Array_Destroy(copyArray);
}

void testArray_Getters(void){
  const float values[] = {2.0f, 3.0f};

  TEST_ASSERT_EQUAL(Array_GetIndex(usedArrayOne), 2);
  TEST_ASSERT_EQUAL(Array_GetLength(usedArrayOne), 2);

  TEST_ASSERT_EQUAL(Array_GetValue(usedArrayOne, 0), 2.0f);
  TEST_ASSERT_EQUAL(Array_GetValue(usedArrayOne, 1), 3.0f);

  TEST_ASSERT_EQUAL_FLOAT_ARRAY(Array_GetArray(usedArrayOne), values, 2);
}

int main(void){
  UNITY_BEGIN();

  RUN_TEST(testArray_Concat);
  RUN_TEST(testArray_Append);
  RUN_TEST(testArray_SetCoordinate);
  RUN_TEST(testArray_SetDataFromTo);
  RUN_TEST(testArray_Copy);
  RUN_TEST(testArray_Getters);

  return UNITY_END();
}