#ifndef PARSING_HPP
#define PARSING_HPP

#include <string>

#include "neurone.hpp"


bool parseNeuronesTypes(const std::string &fp, Neurone *neurones, size_t size);
bool parseNeuronesLinks(const std::string &fp, Neurone *neurones, size_t size);
bool parseNeuronesInputsWeights(const std::string &fp, Neurone *neurones, size_t size);


#endif // PARSING_HPP
