#include "parsing.hpp"

#include <fstream>
#include <iostream>

#include "misc.hpp"


bool parseNeuronesTypes(const std::string &fp, Neurone *neurones, size_t size)
{
	std::ifstream input(fp);

	if (!input.is_open()) {
		std::cout << "Failed to open neurones' types' file." << std::endl;
		return false;
	}

	int lineNo = 1;
	std::string line;
	while (std::getline(input, line)) {
		auto vect = split(line, " : ");
		if (vect.size() != 2) {
			std::cout << "Invalid syntax in config file, line " << lineNo << std::endl;
			return false;
		}

		size_t node = std::stoi(vect[0]);
		uint type = std::stoi(vect[1]);

		if (type < NType::First || type > NType::Last) {
			std::cout << "Invalid node type, line " << lineNo << std::endl;
			return false;
		}

		neurones[node].type = static_cast<NType>(type);

		lineNo++;
	}

	return true;
}
