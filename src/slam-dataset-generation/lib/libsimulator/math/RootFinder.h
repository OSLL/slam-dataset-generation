#ifndef MATH_ROOTFINDER_H
#define MATH_ROOTFINDER_H

#include <vector>

class RootFinder
{
public:
	template <int degree>
	friend class Polynomial;
private:
	static std::vector<double> linear(const double * data);
	static std::vector<double> quadratic(const double * data);
	static std::vector<double> cubic(const double * data);
};

#endif
