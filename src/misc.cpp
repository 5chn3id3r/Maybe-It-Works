#include "misc.hpp"

#include <sstream>


std::vector<std::string> split(const std::string &s, char delim)
{
	std::vector<std::string> result;
	std::stringstream ss(s);
	std::string item;

	while (getline (ss, item, delim)) {
		result.push_back (item);
	}

	return result;
}

std::vector<std::string> split(const std::string &s, const std::string &delim)
{
	std::vector<std::string> res;
	size_t pos = 0;
	size_t offset = 0;

	while (pos < s.size()) {
		pos = s.find(delim, offset);
		std::string str = s.substr(offset, pos);
		res.push_back(str);

		offset += delim.length() + str.length();
	}

	return res;
}

bool is_float(std::string myString)
{
	std::istringstream iss(myString);
	float f;
	iss >> std::noskipws >> f; // noskipws considers leading whitespace invalid
	// Check the entire string was consumed and if either failbit or badbit is set
	return iss.eof() && !iss.fail();
}
