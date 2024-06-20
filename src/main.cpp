#include <iostream>

#include "configuration.hpp"

int main()
{
	Configuration *config = readConfig("~/Documents/GitHub/Maybe-It-Works/src/TestConfig.txt");
	if (!config) {
		return 0;
	}

	std::cout << config->inputWeightFp << std::endl;
	std::cout << config->linksFp << std::endl;
	std::cout << config->neuronesCount << std::endl;
	std::cout << config->typeFile << std::endl;

	DeleteConfiguration(config);
	return 0;
}
