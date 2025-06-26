//
// Created by egor on 16.06.25.
//
#include "array_float.h"

#include <stdlib.h>
#include <stdio.h>
#include "unity/unity.h"

ArrayFloat *usedArrayOne;
ArrayFloat *usedArrayTwo;

void setUp(void){
  const float values[] = {2.0f, 3.0f};

  usedArrayOne = ArrayFloat_Create(2);
  usedArrayTwo = ArrayFloat_Create(2);

  ArrayFloat_AppendPointer(usedArrayOne, values, 2);
  ArrayFloat_AppendPointer(usedArrayTwo, values, 2);
}

void tearDown(void){
  ArrayFloat_Destroy(usedArrayOne);
  ArrayFloat_Destroy(usedArrayTwo);
}


void testArray_Concat(void){
  ArrayFloat *newArray = ArrayFloat_Concat(usedArrayOne, usedArrayTwo);
  const float correct[] = {2.0f, 3.0f, 2.0f, 3.0f};

  TEST_ASSERT_EQUAL_FLOAT_ARRAY(correct, ArrayFloat_GetArray(newArray), 4);

  ArrayFloat_Destroy(newArray);
}

void testArray_Append(void){
  ArrayFloat_Append(usedArrayOne, 2.0f);
  const float correct[] = {2.0f, 3.0f, 2.0f};

  TEST_ASSERT_EQUAL_FLOAT_ARRAY(correct, ArrayFloat_GetArray(usedArrayOne), 3);
  TEST_ASSERT_EQUAL(ArrayFloat_GetCapacity(usedArrayOne), 4);
  TEST_ASSERT_EQUAL(ArrayFloat_GetIndex(usedArrayOne), 3);
}

void testArray_SetCoordinate(void){
  ArrayFloat_SetCoordinate(usedArrayOne, 0, 4.0f);
  const float correct[] = {4.0f, 3.0f};

  TEST_ASSERT_EQUAL_FLOAT_ARRAY(ArrayFloat_GetArray(usedArrayOne), correct, 2);
}

void testArray_SetDataFromTo(void){
  const float data[] = {5.0f, 6.0f};
  ArrayFloat_SetDataFromTo(usedArrayOne, 0, 2, data);

  TEST_ASSERT_EQUAL_FLOAT_ARRAY(ArrayFloat_GetArray(usedArrayOne), data, 2);
}

void testArray_Copy(void){
  ArrayFloat *copyArray = ArrayFloat_MakeCopy(usedArrayOne);
  TEST_ASSERT_TRUE(ArrayFloat_CheckEqual(copyArray, usedArrayOne));
  ArrayFloat_Destroy(copyArray);
}

void testArray_Getters(void){
  const float values[] = {2.0f, 3.0f};

  TEST_ASSERT_EQUAL(ArrayFloat_GetIndex(usedArrayOne), 2);
  TEST_ASSERT_EQUAL(ArrayFloat_GetCapacity(usedArrayOne), 2);

  TEST_ASSERT_EQUAL(ArrayFloat_GetValue(usedArrayOne, 0), 2.0f);
  TEST_ASSERT_EQUAL(ArrayFloat_GetValue(usedArrayOne, 1), 3.0f);

  TEST_ASSERT_EQUAL_FLOAT_ARRAY(ArrayFloat_GetArray(usedArrayOne), values, 2);
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