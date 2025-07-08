//
// Created by egor on 26.06.25.
//

#include "chromosome.h"

#include <assert.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>

struct Chromosome {
  size_t fit; // the value of the fit applied to the chromosome
  ArrayFloat *weights; // the actual weight array
};

//=============================================================================
//
//                     Array Lifecycle Management Functions
//
//=============================================================================

Chromosome* Chromosome_Create(const size_t numberOfElements){
  assert(numberOfElements > 0 && "number of elements must be positive!");

  Chromosome *chromosome = NULL;
  chromosome = malloc(sizeof(Chromosome));
  if (chromosome == NULL) { perror("Failed to allocate chromosome"); return NULL; }

  Chromosome_SetWeights(chromosome, ArrayFloat_Create(numberOfElements)); // by default is set to 0.0 all values
  Chromosome_SetFit(chromosome, SIZE_MAX);

  return chromosome;
}



//=============================================================================
//
//                     Array Query Functions
//
//=============================================================================

size_t Chromosome_GetFit(const Chromosome *chromosome) { return chromosome->fit; }
ArrayFloat* Chromosome_GetWeights(const Chromosome *chromosome) { return chromosome->weights; }



//=============================================================================
//
//                     Array Manipulation Functions
//
//=============================================================================

void Chromosome_SetFit(Chromosome *chromosome, const size_t fit) { assert(fit >= 0  && "fit must be positive!"); chromosome->fit = fit; }
void Chromosome_SetWeights(Chromosome *chromosome, ArrayFloat *weights) { chromosome->weights = weights; }

void Chromosome_SetWeightsFloat(const Chromosome *chromosome, const float *weights){
  const size_t size = Array_GetIndex(Chromosome_GetWeights(chromosome));
  ArrayFloat_SetDataFromTo(Chromosome_GetWeights(chromosome), 0, size, weights);
}