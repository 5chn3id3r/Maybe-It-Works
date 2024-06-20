#ifndef NEURONE_HPP
#define NEURONE_HPP

#include <cmath>
#include <iostream>

enum NType
{
    DEFAULT = 0,
    INPUT = 1,
    OUTPUT = 2,
    KILLER = 3,

    First = DEFAULT,
    Last = KILLER,
};

struct Neurone
{
    NType type;
    unsigned int n_inputs;
    unsigned int n_outputs;

    float *inputs;
    float *outputs;
    float *memory;
    float *weights;
};

/// @brief A function which allocates memory for neurones and put given weights in parameter
/// @param weights Array of weights
/// @param n_inputs Number of inputs
/// @param n_outputs Number of outputs
/// @return The neurone correctly allocated
Neurone *CreateNeurone(float *weights, unsigned int n_inputs, unsigned int n_outputs);

/// @brief A function which free memory allocated for neurone
/// @param neurone The neurone you want to free
void DeleteNeurone(Neurone *neurone);

/// @brief A function which compute the output of a neurone
/// @param neurone The neurone to compute
void ComputeNeurone(Neurone *neurone);

#endif
