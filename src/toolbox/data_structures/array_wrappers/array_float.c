/**
 * @file array_float.c
 * @brief Dynamic Float Array data structure public interface implementation.
 *
 * This file defines all implementations of the Float Array public interface
 *
 * Copyright (C) 2025 Egor Demianov
 *
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program. If not, see <https://www.gnu.org/licenses/>.
 */

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