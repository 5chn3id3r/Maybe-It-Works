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
		auto vect = split(line, " : "); // Format: "NodeID : TypeID"
		if (vect.size() != 2) {
			std::cout << "Invalid syntax in types file, line " << lineNo << std::endl;
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

bool parseNeuronesLinks(const std::string &fp, Neurone *neurones, size_t size)
{
	// [TODO] Define more precisely how we handle the neurons' IOs to make this func.

	std::cout << __func__ << " is currently not implemented." << std::endl;

	/*std::ifstream input(fp);

	if (!input.is_open()) {
		std::cout << "Failed to open neurones' types' file." << std::endl;
		return false;
	}

	// Array for all registered inputs.

	int lineNo = 1;
	std::string line;
	while (std::getline(input, line)) {
		auto vect = split(line, " : "); // Format: "NodeID : InNodeID InNodeID ..."
		if (vect.size() != 2) {
			std::cout << "Invalid syntax in links file, line " << lineNo << std::endl;
			return false;
		}

		if (type < NType::First || type > NType::Last) {
			std::cout << "Invalid node type, line " << lineNo << std::endl;
			return false;
		}

		neurones[node].type = static_cast<NType>(type);

		lineNo++;
	}*/

	return true;
}

bool parseNeuronesInputsWeights(const std::string &fp, Neurone *neurones, size_t size)
{
	// [TODO] Define more precisely how we handle the neurons' IOs to make this func.

	std::cout << __func__ << " is currently not implemented." << std::endl;

	/*std::ifstream input(fp);

	if (!input.is_open()) {
		std::cout << "Failed to open neurones' types' file." << std::endl;
		return false;
	}

	// Array for all registered inputs.

	int lineNo = 1;
	std::string line;
	while (std::getline(input, line)) {
		auto vect = split(line, " : "); // Format: "NodeID : InNodeID InNodeID ..."
		if (vect.size() != 2) {
			std::cout << "Invalid syntax in links file, line " << lineNo << std::endl;
			return false;
		}

		if (type < NType::First || type > NType::Last) {
			std::cout << "Invalid node type, line " << lineNo << std::endl;
			return false;
		}

		neurones[node].type = static_cast<NType>(type);

		lineNo++;
	}*/

	return true;
}


