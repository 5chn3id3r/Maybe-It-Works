#ifndef PARSING_HPP
#define PARSING_HPP

#include <string>

struct Neuron;


bool parseNeuronsTypes(const std::string &fp, Neuron * const neurons, const size_t size);
bool parseNeuronsLinks(const std::string &fp, Neuron * const neurons, const size_t size);
bool parseNeuronsInputsWeights(const std::string &fp, Neuron * const neurons, const size_t size);

void printNeuronsData(const Neuron * const neurons, const size_t size);


#endif // PARSING_HPP
