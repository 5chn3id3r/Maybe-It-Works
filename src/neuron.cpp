#include "neuron.hpp"

#include <cmath>
#include <iostream>


float sigmoid(float x)
{
	return 1.f / (1.f + exp(-x));
}

void DeleteFreeNeuron(Neuron *neuron)
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

void DeleteNeuron(Neuron *neuron)
{
	if (neuron == nullptr) {
		std::cout << "Problem with the neuron given" << std::endl;
		return;
	}

	free(neuron->inputs);
	free(neuron->weights);
	//free(neuron->memory);
}

void ComputeNeuron(Neuron *neuron)
{
	if (neuron == nullptr) {
		std::cout << "Unallocated neuron" << std::endl;
		return;
	}

	if (neuron->n_inputs == 0 || neuron->n_inputs == 0) {
		std::cout << "Neuron has no inputs" << std::endl;
		return;
	}

	neuron->memory = 0.f;
	for (unsigned int i = 0; i < neuron->n_inputs; i++) {
		neuron->memory += *neuron->inputs[i] * neuron->weights[i];
	}
	neuron->memory = sigmoid(neuron->memory);
}

void DiffuseNeuron(Neuron *neuron)
{
	if (neuron == nullptr) {
		std::cout << "Unallocated neuron" << std::endl;
		return;
	}

	if (neuron->n_inputs == 0) {
		std::cout << "neuron has no inputs or outputs" << std::endl;
		return;
	}

	if (neuron->inputs == nullptr || neuron->weights == nullptr) {
		std::cout << "neuron has no inputs or weights" << std::endl;
		return;
	}

	neuron->value = neuron->memory;
}

