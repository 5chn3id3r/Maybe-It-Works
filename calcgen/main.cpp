#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
#include <fstream>
#include <sstream>
#include <ctime>


class AppArgs
	: public std::vector<std::string>
{
public:
	explicit AppArgs(const int argc, const char * const * const argv)
		: std::vector<std::string>(argc)
	{
		for (int i = 0; i < argc; i++) {
			(*this)[i] = argv[i];
		}
	}

	bool contains(const std::string &str) const
	{
		return std::find(this->cbegin(), this->cend(), str) != this->cend();
	}

	bool contains(std::initializer_list<std::string> list) const
	{
		for(const auto &str : list) {
			if (std::find(this->cbegin(), this->cend(), str) != this->cend()) {
				return true;
			}
		}

		return false;
	}

	template<typename ... Args>
	inline bool contains(Args ... args) const
	{
		return contains({args ...});
	}
};

size_t toSize(const std::string &str)
{
	std::stringstream stream(str);
	size_t s;
	stream >> s;

	return s;
}

int gen(const int range, const int min = 0)
{
	return (std::rand() % range) + min;
}

int main(int argc, char **argv)
{
	AppArgs args(argc, argv);

	if (args.contains("--help", "-h", "help")) {
		std::cout << "USAGE: calcgen <minimum> <maximum> <width> <count> <output>\n";
		std::cout << "Where:\n";
		std::cout << "\tminimum \t is the lowest number used for addition,\n";
		std::cout << "\tmaximum \t is the highest number used for addition,\n";
		std::cout << "\twidth   \t maximum number of additions a sample may have,\n";
		std::cout << "\tcount   \t number of samples,\n";
		std::cout << "\toutput  \t output file for the calculations to do.\n";
		std::cout << "\t        \t Formatting for n0 + ... nn = r: n0;...;nn;r\\n\n";
		std::cout << "--help (-h, help) Shows this help.";
		std::cout << std::endl;

		return 0;
	}

	if (args.size() != 6) { // Due to the executable's location, so n+1.
		std::cout << "Wrong number of args given. Use --help (-h) to get usage." << std::endl;
		return 0;
	}

	const int min = std::stoi(args[1]);
	const int max = std::stoi(args[2]);
	const int range = max - min;
	const int width = std::stoi(args[3]) + 1;
	size_t count = toSize(args[4]);

	if (width <= 1) {
		std::cout << "Impossible to use a width that is below 2." << std::endl;
		return 0;
	}

	std::ofstream calcs(args[5]);

	if (!calcs.is_open()) {
		std::cout << "Unable to open '" << args[5] << '\'' << std::endl;
		return 0;
	}

	std::srand(std::time(0)); // Seed it. [NOTE] C++ allows use of better random generators but that should suffice.

	for (size_t i = 0; i < count; i++) {
		const int w = gen(width, 2);
		int sum = 0;
		for (int j = 0; j < w; j++) {
			const int v = gen(range, min);
			calcs << v << ';';
			sum += v;
		}
		calcs << sum << ";\n";
	}

	return 0;
}
