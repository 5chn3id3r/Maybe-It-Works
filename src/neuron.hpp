#ifndef NEURON_H
#define NEURON_H

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
/// @param neurone The neurone you want to delete AND free
void DeleteFreeNeuron(Neuron *neurone);

/// @brief A function which free memory allocated for neuron
/// @param neurone The neurone you want to delete
void DeleteNeuron(Neuron *neurone);

/// @brief A function which compute the output of a neuron
/// @param neurone The neurone to compute
void ComputeNeuron(Neuron *neurone);


#endif // NEURON_HPP
