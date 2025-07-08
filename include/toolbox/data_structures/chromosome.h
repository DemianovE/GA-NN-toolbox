/**
* @file chromosome.h
 * @brief Chromosome data structure public interface header.
 *
 * This file shows the functions of the Chromosome data interface.
 * The Chromosome is an array and fit value combination used in the neural operations
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

#ifndef CHROMOSOME_H
#define CHROMOSOME_H
#include <stddef.h>

#include "array_wrappers/array_float.h"

/**
 * @struct Chromosome
 * @brief Internal definition of the Chromosome structure.
 * @ingroup Chromosome
 * @details
 * This structure holds all information required by the GA process from one chromosome.
 *
 * @section ChromosomeStructDetails Detailed Structure Members
 * This section provides a detailed description of each member of the `Chromosome` struct.
 *
 * @var size_t Chromosome::fit
 * The current fit value for the Chromosome based on last training run.
 *
 * @var Array* Chromosome::weights
 * Array type holder of the weights
 */
typedef struct Chromosome Chromosome;

//=============================================================================
//
//                     Array Lifecycle Management Functions
//
//=============================================================================

/**
 * @ingroup ChromosomeLifecycle
 * @brief The function to create a new Chromosome type object.
 * @param numberOfElements - the number of elements in the chromosome string.
 * @return the new Chromosome type object.
 */
Chromosome* Chromosome_Create(const size_t numberOfElements);



//=============================================================================
//
//                     Array Query Functions
//
//=============================================================================

/**
 * @ingroup ChromosomeQuery
 * @brief The function to return the fit value of the desired chromosome.
 * @param chromosome - the desired chromosome.
 * @return size_t type fit value.
 */
size_t Chromosome_GetFit(const Chromosome *chromosome);

/**
 * @ingroup ChromosomeQuery
 * @brief The function to return the weight value of the desired chromosome.
 * @param chromosome - the desired chromosome.
 * @return ArrayFloat* type array of the weight.
 */
ArrayFloat* Chromosome_GetWeights(const Chromosome *chromosome);

//=============================================================================
//
//                     Array Manipulation Functions
//
//=============================================================================

/**
 * @ingroup ChromosomeManipulation
 * @brief The function to set the value of fit.
 * @param chromosome - the desired chromosome.
 * @param fit - new fit value.
 */
void Chromosome_SetFit(Chromosome *chromosome, const size_t fit);

/**
 * @ingroup ChromosomeManipulation
 * @brief The function to set the value of weights.
 * @param chromosome - the desired chromosome.
 * @param weights - new weight array pointer.
 */
void Chromosome_SetWeights(Chromosome *chromosome, ArrayFloat *weights);

/**
 * @ingroup ChromosomeManipulation
 * @brief  * The function to set the values of the weights with the desired.
 * @param chromosome - the desired chromosome.
 * @param weights - new weight float pointer
 */
void Chromosome_SetWeightsFloat(const Chromosome *chromosome, const float *weights);

#endif //CHROMOSOME_H

/**
* @defgroup Chromosome Chromosome
* @ingroup DataStructures
* @brief Functions of the Data Structure Chromosome.
*/

/**
* @defgroup ChromosomeGeneric Chromosome Generic
* @ingroup Chromosome
* @brief Functions of the Data Structure Chromosome Generic.
*/

/**
* @defgroup ChromosomeLifecycle Chromosome Lifecycle
* @ingroup ChromosomeGeneric
* @brief Lifecycle functions of the Chromosome.
*
* This functions create/destroy/copy Chromosome
*/

/**
* @defgroup ChromosomeQuery Chromosome Query
* @ingroup ChromosomeGeneric
* @brief Query of the Data Structure Chromosome.
*
* This functions make read-only operations on data
*/

/**
* @defgroup ChromosomeManipulation Chromosome Manipulation
* @ingroup ChromosomeGeneric
* @brief Manipulation of the Data Structure Chromosome.
*
* This functions make write operations on data
*/