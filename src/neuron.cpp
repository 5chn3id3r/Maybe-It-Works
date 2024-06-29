#include "neuron.hpp"

#include <cmath>
#include <iostream>


float sigmoid(float x)
{
	return 1.f / (1.f + exp(-x));
}

Neuron *CreateNeuron(float *weights, unsigned int n_inputs, unsigned int n_outputs, NType type)
{
	if (n_inputs <= 0 || n_outputs <= 0 || weights == NULL || type < NType::DEFAULT || type >= NType::Last) {
		std::cout << "Problem in the variable given" << std::endl;
		return nullptr;
	}

	Neuron *neuron = (Neuron *)calloc(1, sizeof(Neuron));
	neuron->type = type;
	neuron->n_inputs = n_inputs;
	neuron->n_outputs = n_outputs;
	neuron->weights = (float *)calloc(n_inputs, sizeof(float));
	neuron->weights = weights;
	neuron->inputs = (float *)calloc(n_inputs, sizeof(float));
	neuron->inputs = nullptr;
	neuron->outputs = (float *)calloc(n_outputs, sizeof(float));
	neuron->outputs = nullptr;
	neuron->type = type;

	neuron->memory = (float *)calloc(n_outputs, sizeof(float));
	neuron->memory = nullptr;

	return neuron;
}

void DeleteFreeNeuron(Neuron *neuron)
{
	if (neuron == nullptr) {
		std::cout << "Problem with the neuron given" << std::endl;
		return;
	}

	free(neuron->inputs);
	free(neuron->outputs);
	free(neuron->weights);
	free(neuron->memory);
	free(neuron);
}

void DeleteNeuron(Neuron *neuron)
{
	if (neuron == nullptr) {
		std::cout << "Problem with the neuron given" << std::endl;
		return;
	}

	free(neuron->inputs);
	free(neuron->outputs);
	free(neuron->weights);
	free(neuron->memory);
}

void ComputeNeuron(Neuron *neuron)
{
	if (neuron == nullptr) {
		std::cout << "Unallocated neuron" << std::endl;
		return;
	}

	if (neuron->n_inputs == 0 || neuron->n_outputs == 0) {
		std::cout << "Neuron has no inputs or outputs" << std::endl;
		return;
	}

	if (neuron->inputs == nullptr || neuron->outputs == nullptr || neuron->weights == nullptr) {
		std::cout << "Neuron has no inputs, outputs or weights" << std::endl;
		return;
	}

	for (unsigned int i = 0; i < neuron->n_outputs; i++) {
		neuron->outputs[i] = 0.f;
		for (unsigned int j = 0; j < neuron->n_inputs; j++) {
			neuron->memory[i] += neuron->inputs[j] * neuron->weights[j];
		}
		neuron->outputs[i] = sigmoid(neuron->outputs[i]);
	}
}

void DiffuseNeuron(Neuron *neuron)
{
	if (neuron == nullptr) {
		std::cout << "Unallocated neuron" << std::endl;
		return;
	}

	if (neuron->n_inputs == 0 || neuron->n_outputs == 0) {
		std::cout << "neuron has no inputs or outputs" << std::endl;
		return;
	}

	if (neuron->inputs == nullptr || neuron->outputs == nullptr || neuron->weights == nullptr) {
		std::cout << "neuron has no inputs, outputs or weights" << std::endl;
		return;
	}

	for (unsigned int i = 0; i < neuron->n_outputs; i++) {
		neuron->outputs[i] = neuron->memory[i];
	}
}

