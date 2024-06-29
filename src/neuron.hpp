#ifndef NEURON_H
#define NEURON_H


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
	unsigned int n_inputs;
	unsigned int n_outputs;

	float *inputs;
	float *outputs;
	float *memory;
	float *weights;
};

/// @brief A function which allocates memory for neurons and put given weights in parameter
/// @param weights Array of weights
/// @param n_inputs Number of inputs
/// @param n_outputs Number of outputs
/// @return The correctly allocated neuron
Neuron *CreateNeuron(float *weights, unsigned int n_inputs, unsigned int n_outputs);

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
