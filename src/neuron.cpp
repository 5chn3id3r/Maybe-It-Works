#include "neuron.hpp"

#include <cmath>
#include <iostream>


constexpr float sigmoid(float x)
{
	return 1.f / (1.f + exp(-x));
}

void DeleteFreeNeuron(Neuron * const neuron)
{
	if (neuron == nullptr) {
		std::cout << "Problem with the neuron given" << std::endl;
		return;
	}

	free(neuron->inputs);
	free(neuron->weights);
	//free(neuron->memory);
	free(neuron);
}

void DeleteNeuron(Neuron * const neuron)
{
	if (neuron == nullptr) {
		std::cout << "Problem with the neuron given" << std::endl;
		return;
	}

	free(neuron->inputs);
	free(neuron->weights);
	//free(neuron->memory);
}

void ComputeNeurons(Neuron * const neurons, const size_t size)
{
	if (neurons == nullptr) [[unlikely]] {
		std::cout << "Unallocated neurons!" << std::endl;
		return;
	}

	// Reset all memories.
	for (size_t i = 0; i < size; i++) {
		neurons[i].memory = 0.f;
	}

	// Calculate for each neuron the sum
	for (size_t i = 0; i < size; i++) {
		if (neurons[i].n_inputs == 0) [[unlikely]] {
			continue;
		}

		Neuron * const neuron = &neurons[i];
		for (unsigned int i = 0; i < neuron->n_inputs; i++) {
			neuron->memory += *neuron->inputs[i] * neuron->weights[i];
		}
	}

	// Apply function on sum.
	// [NOTE] We can merge ComputeNeurons with DiffuseNeurons here by directly putting the result in value.
	for (size_t i = 0; i < size; i++) {
		neurons[i].memory = sigmoid(neurons[i].memory);
	}
}

void DiffuseNeurons(Neuron * const neurons, const size_t size)
{
	if (neurons == nullptr) [[unlikely]] {
		std::cout << "Unallocated neurons!" << std::endl;
		return;
	}

	for (size_t i = 0; i < size; i++) {
		if (neurons[i].n_inputs == 0) [[unlikely]] {
			continue;
		}

		neurons[i].value = neurons[i].memory;
	}
}

