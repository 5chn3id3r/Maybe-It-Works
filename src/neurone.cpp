#include "neurone.hpp"

float sigmoid(float x)
{
    return 1.f / (1.f + exp(-x));
}

Neurone *CreateNeurone(float *weights, unsigned int n_inputs, unsigned int n_outputs, NType type)
{
    if (n_inputs <= 0 || n_outputs <= 0 || weights == NULL || type <= 0 || type >= 4)
    {
        printf("Problem in the variable given\n");
        return nullptr;
    }
    Neurone *neurone = (Neurone *)calloc(1, sizeof(Neurone));
    neurone->type = type;
    neurone->n_inputs = n_inputs;
    neurone->n_outputs = n_outputs;
    neurone->weights = (float *)calloc(n_inputs, sizeof(float));
    neurone->weights = weights;
    neurone->inputs = (float *)calloc(n_inputs, sizeof(float));
    neurone->inputs = nullptr;
    neurone->outputs = (float *)calloc(n_outputs, sizeof(float));
    neurone->outputs = nullptr;
    neurone->type = type;

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

void ComputeNeurone(Neurone* neurone)
{
    if (neurone == nullptr)
        printf("Unallocated Neurone\n");return;
    
    if (neurone->n_inputs == 0 || neurone->n_outputs == 0)
        printf("Neurone has no inputs or outputs\n");return;

    if (neurone->inputs == nullptr || neurone->outputs == nullptr || neurone->weights == nullptr)
        printf("Neurone has no inputs, outputs or weights\n");return;
    
    for (unsigned int i = 0; i < neurone->n_outputs; i++)
    {
        neurone->outputs[i] = 0.f;
        for (unsigned int j = 0; j < neurone->n_inputs; j++)
        {
            neurone->memory[i] += neurone->inputs[j] * neurone->weights[j];
        }
        neurone->outputs[i] = sigmoid(neurone->outputs[i]);
    }
}

void DiffuseNeurone(Neurone *neurone)
{
    if (neurone == nullptr)
        printf("Unallocated Neurone\n");return;
    
    if (neurone->n_inputs == 0 || neurone->n_outputs == 0)
        printf("Neurone has no inputs or outputs\n");return;

    if (neurone->inputs == nullptr || neurone->outputs == nullptr || neurone->weights == nullptr)
        printf("Neurone has no inputs, outputs or weights\n");return;

    for (unsigned int i = 0; i < neurone->n_outputs; i++)
    {
        neurone->outputs[i] = neurone->memory[i];
    }
}

