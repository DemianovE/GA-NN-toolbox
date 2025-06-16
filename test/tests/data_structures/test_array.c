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

  usedArrayOne = ArrayCreate(2);
  usedArrayTwo = ArrayCreate(2);

  ArrayAppendPointer(usedArrayOne, values, 2);
  ArrayAppendPointer(usedArrayTwo, values, 2);
}

void tearDown(void){
  ArrayDestroy(usedArrayOne);
  ArrayDestroy(usedArrayTwo);
}


void testArrayConcat(void){
  Array *newArray = ArrayConcat(usedArrayOne, usedArrayTwo);
  const float correct[] = {2.0f, 3.0f, 2.0f, 3.0f};

  TEST_ASSERT_EQUAL_FLOAT_ARRAY(correct, newArray->data, 4);

  ArrayDestroy(newArray);
}

void testArrayAppend(void){
  ArrayAppend(usedArrayOne, 2.0f);
  const float correct[] = {2.0f, 3.0f, 2.0f};

  TEST_ASSERT_EQUAL_FLOAT_ARRAY(correct, usedArrayOne->data, 3);
  TEST_ASSERT_EQUAL(usedArrayOne->length, 4);
  TEST_ASSERT_EQUAL(usedArrayOne->index, 3);
}

int main(void){
  UNITY_BEGIN();

  RUN_TEST(testArrayConcat);
  RUN_TEST(testArrayAppend);

  return UNITY_END();
}