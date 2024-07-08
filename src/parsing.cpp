#include "parsing.hpp"

#include <algorithm>
#include <fstream>
#include <iostream>

#include "neuron.hpp"
#include "misc.hpp"


bool parseNeuronsTypes(const std::string &fp, Neuron * const neurones, const size_t size)
{
	std::ifstream input(fp);

	if (!input.is_open()) [[unlikely]] {
		std::cout << "Failed to open neurones' types' file." << std::endl;
		return false;
	}
	input.imbue(std::locale("en_US.UTF8"));

	int lineNo = 1;
	std::string line;
	while (std::getline(input, line)) {
		auto vect = split(line, " : "); // Format: "NodeID : TypeID"
		if (vect.size() != 2) [[unlikely]] {
			std::cout << "Invalid syntax in types file, line " << lineNo << std::endl;
			return false;
		}

		size_t node = std::stoi(vect[0]);
		uint type = std::stoi(vect[1]);

		if (type < NType::First || type > NType::Last) [[unlikely]] {
			std::cout << "Invalid node type, line " << lineNo << std::endl;
			return false;
		}

		neurones[node].type = static_cast<NType>(type);

		lineNo++;
	}

	return true;
}

bool parseNeuronsLinks(const std::string &fp, Neuron * const neurons, const size_t size)
{
	std::ifstream input(fp);

	if (!input.is_open()) [[unlikely]] {
		std::cout << "Failed to open neurones' types' file." << std::endl;
		return false;
	}
	input.imbue(std::locale("en_US.UTF8"));

	int lineNo = 1;
	std::string line;
	while (std::getline(input, line)) { // For each line
		const std::vector<std::string> vect = split(line, " : "); // Format: "NodeID : InNodeID InNodeID ..."
		if (vect.size() < 2) [[unlikely]] {
			continue;
		} else if (vect.size() > 2) [[unlikely]] { // Check we hav a valid format.
			std::cout << "Invalid syntax in links file, line " << lineNo << std::endl;
			return false;
		}

		auto nid = std::stoi(vect[0]);
		if (nid < 0 || nid >=  size) [[unlikely]] { // Check if within range.
			std::cout << "Invalid source neuron ID in links file, line " << lineNo << std::endl;
			return false;
		}

		auto inputs = split(vect[1], ' ');
		int idNo = 1;
		for (const auto &elem : inputs) { // Check we have values.
			if (!all_of(elem.begin(), elem.end(), isdigit)) [[unlikely]] {
				std::cout << "Invalid target neuron ID in links file, does, not contain only numbers, line " << lineNo << ", element no. " << idNo << std::endl;
				std::cout << "Value: '" << elem << "'" << std::endl;
				return false;
			}

			const int v = std::stoi(elem);
			if (v < 0 || v >= size) [[unlikely]] {
				std::cout << "Invalid target neuron ID in links file, OOR, line " << lineNo << ", element no. " << idNo << std::endl;
				return false;
			}

			idNo++;
		}

		neurons[nid].n_inputs = inputs.size();
		neurons[nid].inputs = static_cast<InputBuffer>(malloc(inputs.size() * sizeof(float *)));
		size_t curr = 0;
		for (const auto &elem : inputs) {
			const int v = std::atoi(elem.c_str());

			neurons[nid].inputs[curr] = &neurons[v].value;
			curr++;
		}

		lineNo++;
	}

	return true;
}

bool parseNeuronsInputsWeights(const std::string &fp, Neuron * const neurons, const size_t size)
{
	std::ifstream input(fp);

	if (!input.is_open()) [[unlikely]] {
		std::cout << "Failed to open neurones' weights' file." << std::endl;
		return false;
	}
	input.imbue(std::locale("en_US.UTF8"));

	// Array for all registered inputs.

	int lineNo = 1;
	std::string line;
	while (std::getline(input, line)) {
		auto vect = split(line, " : "); // Format: "NodeID : Weight0 Weight1 ..."
		if (vect.size() != 2) [[unlikely]] {
			std::cout << "Invalid syntax in weights file, line " << lineNo << std::endl;
			return false;
		}

		auto nid = std::atoi(vect[0].c_str());
		if (nid < 0 || nid >=  size) [[unlikely]] { // Check if within range.
			std::cout << "Invalid neuron ID in weights file, line " << lineNo << std::endl;
			return false;
		}

		const std::vector<std::string> weights = split(vect[1], ' ');
		int idNo = 1;
		for (const auto &elem : weights) { // Check we have values.
			if (!is_float(elem)) [[unlikely]] {
				std::cout << "Invalid target neuron ID in links file, does, not containing only numbers, line " << lineNo << ", element no. " << idNo << std::endl;
				return false;
			}
			idNo++;
		}

		neurons[nid].weights = static_cast<Buffer>(malloc(weights.size() * sizeof(float)));
		size_t curr = 0;
		for (const auto &elem : weights) {
			neurons[nid].weights[curr] = std::stof(elem);
			curr++;
		}

		lineNo++;
	}

	return true;
}

void printNeuronsData(const Neuron * const neurons, const size_t size)
{
	for (size_t i = 0; i < size; i++) {
		std::cout << ">> Neuron no. " << i << std::endl;
		std::cout << "Type: " << neurons[i].type
				  << "\nInput number: " << neurons[i].n_inputs
				  << std::endl;

		std::cout << "Inputs:";
		for (uint j = 0; j < neurons[i].n_inputs; j++) {
			for (uint k = 0; k < size; k++) {
				if (neurons[i].inputs[j] == &neurons[k].value) {
					std::cout << " " << k;
				}
			}
		}
		std::cout << std::endl;

		std::cout << "Weights:";
		for (uint j = 0; j < neurons[i].n_inputs; j++) {
			std::cout << " " << neurons[i].weights[j];
		}
		std::cout << '\n' << std::endl;
	}
}

