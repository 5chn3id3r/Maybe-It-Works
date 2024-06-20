#include "configuration.hpp"

#include <fstream>
#include <iostream>
#include <sstream>
#include <unordered_map>
#include <vector>


const char *keyList[] = {
	"InputWeightFile",
	"LinkFile",
	"TypeFile",
	"Neurones",
};


std::vector<std::string> split(const std::string &s, char delim)
{
	std::vector<std::string> result;
	std::stringstream ss (s);
	std::string item;

	while (getline (ss, item, delim)) {
		result.push_back (item);
	}

	return result;
}

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
		auto vect = split(line, '=');
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

			std::cout << "Missing cpnfiguration key '" << keyList[i] << "'" << std::endl;
		}
	}

	if (!ok) {
		delete conf;
		return nullptr;
	}

	conf->inputWeightFp = dict["InputWeightFile"];
	conf->linksFp = dict["LinkFile"];
	conf->neuronesCount = std::stoi(dict["Neurones"]);

	return conf;
}

void DeleteConfiguration(Configuration *conf)
{
	delete conf;
}
