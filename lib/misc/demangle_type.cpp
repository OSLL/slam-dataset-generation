#include "misc/demangle_type.h"
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
