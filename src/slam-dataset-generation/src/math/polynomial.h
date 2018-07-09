#ifndef MATH_POLYNOMIAL_H
#define MATH_POLYNOMIAL_H

#include <array>
#include <cmath>

#include <iostream>

namespace math
{
	template <int degree>
	class Polynomial
	{
	public:
		using coefficients_t = std::array<double, degree + 1>;
		using roots_t = coefficients_t;

		template <typename ... Args>
		Polynomial(Args ... args);

		double operator()(double t);

		template <int n = 1>
		double derivative(double t);
		
		// A polynomial of degree n has at most n roots
		// The first value of the array specifies the number of real roots (which are the only ones stored)
		roots_t roots();
	private:
		// An n-degree polynomial needs n + 1 coefficients because of the constant term
		coefficients_t data_;

		template <typename ... Args>
		void check_validity();
	};
}

// Include template implementation
#include "polynomial_implementation.h"

#endif
