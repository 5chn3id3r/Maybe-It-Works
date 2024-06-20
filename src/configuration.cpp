#include "configuration.hpp"

#include <fstream>
#include <iostream>
#include <sstream>
#include <unordered_map>


const char *keyList[] = {
	"InputWeightFile",
	"WeightFile",
	"LinkFile",
	"Neurones",
};


Configuration *readConfig(const std::string &fp)
{
	std::ifstream input(fp);
	input.open("r");

	if (!input.is_open()) {
		std::cout << "Failed to open configuration file." << std::endl;
		return nullptr;
	}

	Configuration *conf = new Configuration;
	std::unordered_map<std::string, std::string> dict;

	int lineNo = 1;
	std::string line;
	while (std::getline(input, line)) {
		std::istringstream iss(line);
		std::string k, v;

		if (!(iss >> k >> v)) { // error
			std::cout << "Failed to read configuration, at line " << lineNo << std::endl;

			delete conf;
			return nullptr;
		}

		dict[k] = v;
		lineNo++;
	}

	bool ok = true;
	// Check for all required data.
	for (int i = 0; i < sizeof(keyList)/sizeof(char *); i++) {
		if (dict.find(keyList[i]) == dict.cend()) {
			ok = false;

			std::cout << "Missing cpnfiguration key '" << keyList[i] << "'" << std::endl;
		}
	}

	if (!ok) {
		delete conf;
		return nullptr;
	}

	conf->inputWeightFp = dict["InputWeightFile"];
	conf->weightFp = dict["WeightFile"];
	conf->linksFp = dict["LinkFile"];
	conf->neuronesCount = std::stoi(dict["Neurones"]);

	return conf;
}

void DeleteConfiguration(Configuration *conf)
{
	delete conf;
}
