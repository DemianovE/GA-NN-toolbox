

#include "array_float.h"

//=============================================================================
//
//                     Array Query Functions
//
//=============================================================================

float ArrayFloat_GetValue(const Array *array, const size_t index){
  // get the void pointer and convert it to 0.0f or actual value
  void* pointer = Array_GetValue(array, index);
  if (pointer == NULL) return 0.0f;
  return *(float*)pointer;
}