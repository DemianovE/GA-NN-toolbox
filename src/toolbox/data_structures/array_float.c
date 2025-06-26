

#include "array_float.h"

//=============================================================================
//
//                     Array Query Functions
//
//=============================================================================

float ArrayFloat_GetValue(const ArrayFloat *array, const size_t index){
  // get the void pointer and convert it to 0.0f or actual value
  void* pointer = Array_GetValue(array, index);
  if (pointer == NULL) return 0.0f;
  return *(float*)pointer;
}

int ArrayFloat_CheckEqual(const ArrayFloat *arrayOne, const ArrayFloat *arrayTwo){
  if (ArrayFloat_GetIndex(arrayOne)  != ArrayFloat_GetIndex(arrayTwo))  return 0;

  for (size_t i=0; i < ArrayFloat_GetCapacity(arrayOne); i++){
    if (ArrayFloat_GetValue(arrayOne, i) != ArrayFloat_GetValue(arrayTwo, i)) return 0;
  }
  return 1;
}