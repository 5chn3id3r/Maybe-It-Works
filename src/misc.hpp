#ifndef MISC_HPP
#define MISC_HPP

#include <vector>
#include <string>


std::vector<std::string> split(const std::string &s, char delim);
std::vector<std::string> split(const std::string &s, const std::string &delim);
bool is_float(std::string myString);


#endif // MISC_HPP
