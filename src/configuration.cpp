#include "configuration.hpp"

#include <fstream>
#include <iostream>
#include <unordered_map>
#include <vector>

#include "neuron.hpp"
#include "parsing.hpp"
#include "misc.hpp"


const char *keyList[] = {
	"InputWeightFile",
	"LinkFile",
	"TypeFile",
	"Neurons",
};


Configuration *readConfig(const std::string &fp)
{
	std::ifstream input(fp);

	if (!input.is_open()) {
		std::cout << "Failed to open configuration file." << std::endl;
		return nullptr;
	}

	Configuration *conf = new Configuration;
	std::unordered_map<std::string, std::string> dict;

	int lineNo = 1;
	std::string line;
	while (std::getline(input, line)) {
		auto vect = split(line, "=");
		if (vect.size() != 2) {
			std::cout << "Invalid syntax in config file, line " << lineNo << std::endl;

			delete conf;
			return nullptr;
		}

		dict[vect[0]] = vect[1];
		lineNo++;
	}

	bool ok = true;
	// Check for all required data.
	for (int i = 0; i < sizeof(keyList)/sizeof(char *); i++) {
		if (dict.find(keyList[i]) == dict.cend()) {
			ok = false;

			std::cout << "Missing configuration key '" << keyList[i] << "'" << std::endl;
		}
	}

	if (!ok) {
		delete conf;
		return nullptr;
	}

	conf->inputWeightFp = dict["InputWeightFile"];
	conf->linksFp = dict["LinkFile"];
	conf->typeFile = dict["TypeFile"];
	conf->neuronsCount = std::stoi(dict["Neurons"]);
	std::cout << "Configuration loaded." << std::endl;

	return conf;
}

void DeleteConfiguration(Configuration * const conf)
{
	delete conf;
}

Neuron *neuronsFromConfig(const Configuration * const config)
{
	Neuron *neurons = (Neuron *)calloc(config->neuronsCount, sizeof(Neuron));
	if (!neurons) {
		std::cout << "Failed to allocate neurons required for the network." << std::endl;
		return nullptr;
	}

	std::cout << "Loading neurons' types..." << std::endl;
	if (!parseNeuronsTypes(config->typeFile, neurons, config->neuronsCount)) {
		free(neurons);
		return nullptr;
	}

	std::cout << "Loading neurons' links..." << std::endl;
	if (!parseNeuronsLinks(config->linksFp, neurons, config->neuronsCount)) {
		free(neurons);
		return nullptr;
	}

	std::cout << "Loading neuronal links' data..." << std::endl;
	if (!parseNeuronsInputsWeights(config->inputWeightFp, neurons, config->neuronsCount)) {
		free(neurons);
		return nullptr;
	}

	std::cout << "Loading done." << std::endl;
	return neurons;
}

void deleteNeuronsFromConfig(const Configuration * const config, Neuron *neurons)
{
	if (!neurons) {
		return;
	}

	if (!config) {
		std::cout << "No config given to release neurons." << std::endl;
		return;
	}

	for (size_t i = 0; i < config->neuronsCount; i++) {
		DeleteNeuron(&neurons[i]);
	}
}
