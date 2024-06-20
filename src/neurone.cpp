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

/* TODO : ComputeNeurone(Neurone* neurone)
a function which computes the output of the neurone
*/