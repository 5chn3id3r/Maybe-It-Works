#ifndef CONFIGURATION_HPP
#define CONFIGURATION_HPP

#include <string>


struct Configuration
{
	std::string linksFp;
	std::string weightFp;
	std::string inputWeightFp;

	size_t neuronesCount;

};

Configuration *readConfig(const std::string &fp);

void DeleteConfiguration(Configuration *conf);


#endif // CONFIGURATION_HPP
