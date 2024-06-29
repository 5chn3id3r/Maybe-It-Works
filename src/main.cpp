#include <iostream>

#include "configuration.hpp"


int main()
{
	Configuration *config = readConfig("../data/config.txt");
	if (!config) {
		return 0;
	}

	std::cout << "\n==== CONFIG ====" << std::endl;
	std::cout << "Weights FP: " << config->inputWeightFp << std::endl;
	std::cout << "Links FP: " << config->linksFp << std::endl;
	std::cout << "Types FP: " << config->typeFile << std::endl;
	std::cout << "Neurons: " << config->neuronsCount << std::endl;
	std::cout << "================\n" << std::endl;

	Neuron *neurons = neuronsFromConfig(config);
	if (!neurons) {
		return 0;
	}

	std::cout << "Neurons have been loaded from files according to the config file.\n" << std::endl;

	deleteNeuronsFromConfig(config, neurons);
	DeleteConfiguration(config);

	return 0;
}
