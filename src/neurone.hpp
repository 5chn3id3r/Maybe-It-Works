#ifndef NEURONE_HPP
#define NEURONE_HPP

#include <cmath>

struct Neurone 
{
    unsigned int n_inputs;
    unsigned int n_outputs;
    float* inputs;
    float* outputs;
    float* weights;
};

#endif