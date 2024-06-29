#ifndef CONFIGURATION_HPP
#define CONFIGURATION_HPP

#include <string>


struct Neuron;


struct Configuration
{
	std::string linksFp;
	std::string inputWeightFp;
	std::string typeFile;

	size_t neuronsCount;
};


Configuration *readConfig(const std::string &fp);

void DeleteConfiguration(Configuration *conf);

Neuron *neuronsFromConfig(const Configuration * const config);
void deleteNeuronsFromConfig(const Configuration * const config, Neuron *neurons);


#endif // CONFIGURATION_HPP
