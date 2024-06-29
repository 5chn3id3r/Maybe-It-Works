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
