#include "misc/misc.h"
#include <random>

using std::random_device;
using std::mt19937;
using std::uniform_real_distribution;;


#ifdef __GNUG__
#include <cstdlib>
#include <memory>
#include <cxxabi.h>
// g++ compiler
std::string demangle(const char * name) {
	int status = -4;

	std::unique_ptr<char, void(*)(void *)> res {
		abi::__cxa_demangle(name, NULL, NULL, &status),
		std::free
	};

	return (status==0) ? res.get() : name;
}
#else
// Not g++ compiler
std::string demangle(const char * name) {
	return name;
}
#endif


double generate_random_number(const double & min, const double & max) {
	static random_device rd;
	static mt19937 gen(rd());
	static uniform_real_distribution<> distribution(min, max);

	return distribution(gen);
}
