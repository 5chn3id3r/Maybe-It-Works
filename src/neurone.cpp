#include "neurone.hpp"

float sigmoid(float x)
{
    return 1.f / (1.f + exp(-x));
}

Neurone *CreateNeurone(float *weights, unsigned int n_inputs, unsigned int n_outputs)
{
    if (n_inputs <= 0 || n_outputs <= 0 || weights == NULL)
    {
        printf("Problem in the variable give\n");
        return nullptr;
    }
    Neurone *neurone = (Neurone *)calloc(1, sizeof(Neurone));
    neurone->n_inputs = n_inputs;
    neurone->n_outputs = n_outputs;
    neurone->weights = (float *)calloc(n_inputs, sizeof(float));
    neurone->weights = weights;
    neurone->inputs = (float *)calloc(n_inputs, sizeof(float));
    neurone->inputs = nullptr;
    neurone->outputs = (float *)calloc(n_outputs, sizeof(float));
    neurone->outputs = nullptr;

    return neurone;
}

void DeleteNeurone(Neurone *neurone)
{
    if (neurone == nullptr)
    {
        printf("Problem with the neurone given\n");
        return;
    }
    free(neurone->inputs);
    free(neurone->outputs);
    free(neurone->weights);
    free(neurone);
}

/* TODO : ComputeNeurone(Neurone* neurone)
a function which computes the output of the neurone
*/