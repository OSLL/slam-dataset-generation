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

		// Default constructor (only enters overload resolution if degree >= 0
		//template <typename = std::enable_if< degree >= 0 >, typename ... Args>
		template <typename ... Args>
		Polynomial(Args ... args);

		double operator()(double t);

		template <int n>
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


// Normal constructor
template <int degree>
template <typename ... Args>
math::Polynomial<degree>::Polynomial(Args ... args)
	// Call to check validity does some static_asserts to make sure template parameter pack is valid
	: data_((check_validity<Args ...>(), coefficients_t {static_cast<double>(args) ...}))
{ }

/* ================= Metafunction for checking multiple metafunction conditionals ================= */
template<typename... Conds>
struct and_
	: std::true_type
{ };

template<typename Cond, typename... Conds>
struct and_<Cond, Conds...>
	: std::conditional<Cond::value, and_<Conds...>, std::false_type>::type
{ };
/* ================================================================================================ */



/* ======================================== check_validity ======================================== */
template <int degree>
template <typename ... Args>
void math::Polynomial<degree>::check_validity()
{
	static_assert(degree >= 0, "Cannot instantiate a Polynomial of degree < 0.");
	static_assert(sizeof...(Args) == degree + 1, "Incorrect number of parameters for Polynomial constructor");
	static_assert(and_<std::is_convertible<Args, double> ...>::value, "One of the parameters to the Polynomial constructor has an incorrect type.");
}
/* ================================================================================================ */

template <int degree>
double math::Polynomial<degree>::operator()(double t)
{
	double sum = 0;

	for (int i = 0; i < degree + 1; i++)
	{
		sum += data_[i] * std::pow(t, i);
	}

	return sum;
}

inline constexpr int f(int i, int n)
{
		return (n == 0)? 1 : i * f(i - 1, n - 1);
}

template <int degree>
template <int n>
double math::Polynomial<degree>::derivative(double t)
{
	if (n == 0)
	{
		return (*this)(t);
	}
	else
	{
		double sum = 0;

		for (int i = 0; i < degree; i++)
		{
			// d^n/dx^n [a[i] * x^i] = a[i] * [ i * (i - 1) * (i - 2) * ... (i - (n - 1)) ] * x^(i-n)
			//
			// Let i * (i - 1) * (i - 2) * ... * (i - (n - 1)) be calculated by a constexpr function f
			//
			// Then, d^n/dx^n [a[i] * x^i] = a[i] * function(i, n) * x^(i-n)
			sum += data_[i] * f(i, n) * std::pow(t, i - n);
		}

		return sum;
	}
}

template <int degree>
std::array<double, degree + 1> math::Polynomial<degree>::roots()
{
	
}


#endif
