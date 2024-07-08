#ifndef NEURON_H
#define NEURON_H

#include <cstddef>

#include "types.hpp"


enum NType
{
	DEFAULT = 0,
	INPUT = 1,
	OUTPUT = 2,
	KILLER = 3,

	First = DEFAULT,
	Last = KILLER,
};

struct Neuron
{
	NType type = DEFAULT;

	uint n_inputs = 0;

	InputBuffer inputs = nullptr;
	float memory = 0.f;
	Buffer weights = nullptr;

	float value = 0.f;
};


/// @brief A function which frees memory allocated for neuron
/// @param neuron= The neuron you want to delete AND free
void DeleteFreeNeuron(Neuron * const neuron);

/// @brief A function which free memory allocated for neuron
/// @param neuron The neuron you want to delete
void DeleteNeuron(Neuron * const neuron);

/// @brief A function which computes the output of neurons.
/// @param neurons The neurons to compute.
/// @param size The number of elements pointed to by neurons.
void ComputeNeuron(Neuron * const neurons, const size_t size);

/// @brief A function which diffuses the output of neurons.
/// @param neurons The neurons to compute.
/// @param size The number of elements pointed to by neurons.
void DiffuseNeurons(Neuron * const neurons, const size_t size);


#endif // NEURON_HPP
