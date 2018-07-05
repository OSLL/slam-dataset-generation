#ifndef MATH_CUBICPOLYNOMIAL_H
#define MATH_CUBICPOLYNOMIAL_H

#include "math/function.h"

namespace math
{

	class CubicPolynomial : public Function<CubicPolynomial>
	{
	public:
		CubicPolynomial(double a, double b, double c, double d);
	private:
		struct Data
		{
			double a, b, c, d;
		};
	};

}

#endif
