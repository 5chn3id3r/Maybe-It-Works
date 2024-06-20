#include "neurone.hpp"

float sigmoid(float x) 
{
    return 1.f / (1.f + exp(-x));
}

/* TODO : CreateNeurone(float* weights, unsigned int n_inputs, unsigned int n_outputs)
a function which allocates memory for neurones and put given weights in parameter
*/


/* TODO : DeleteNeurone(Neurone* neurone)
a function which frees memory allocated for neurone
*/

/*
Sum the inputs multiplied by the weights and apply the sigmoid function to the output
*/
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
            neurone->outputs[i] += neurone->inputs[j] * neurone->weights[j];
        }
        neurone->outputs[i] = sigmoid(neurone->outputs[i]);
    }
}