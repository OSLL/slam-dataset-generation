#ifndef MATH_POLYNOMIAL_IMPLEMENTATION_H
#define MATH_POLYNOMIAL_IMPLEMENTATION_H

#include "polynomial.h"

/* ==================== Constructor and argument validation =================== */
template <int degree>
template <typename ... Args>
math::Polynomial<degree>::Polynomial(Args ... args)
	// Call to check validity does some static_asserts to make sure template parameter pack is valid
	: data_( ( check_validity<Args ...>(), std::move(coefficients_t { static_cast<double>(args) ... } ) ) )
{ }

template<typename... Conds>
struct and_
	: std::true_type
{ };

template<typename Cond, typename... Conds>
struct and_<Cond, Conds...>
	: std::conditional<Cond::value, and_<Conds...>, std::false_type>::type
{ };

template <int degree>
template <typename ... Args>
void math::Polynomial<degree>::check_validity()
{
	static_assert(degree >= 0, "Cannot instantiate a Polynomial of degree < 0.");
	static_assert(sizeof...(Args) == degree + 1, "Incorrect number of parameters for Polynomial constructor");
	static_assert(and_<std::is_convertible<Args, double> ...>::value, "One of the parameters to the Polynomial constructor has an incorrect type.");
}
/* ============================================================================ */



/* ====================== Function operator & derivative ====================== */
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
			// Let f(i, n) = i * (i - 1) * (i - 2) * ... * (i - (n - 1))
			//
			// Then, d^n/dx^n [a[i] * x^i] = a[i] * f(i, n) * x^(i-n)
			sum += data_[i] * f(i, n) * std::pow(t, i - n);
		}

		return sum;
	}
}
/* ============================================================================ */



/* =============================== Root finding =============================== */
template <>
roots_t math::Polynomial<0>::roots()
{
	return {0};
}

template <>
roots_t math::Polynomial<1>::roots()
{
	// at + b = 0
	const double & a = data_[1];
	const double & b = data_[0];
	
	roots_t roots;

	// Check for actual degree of polynomial
	if (a != 0)
	{
		roots[0] = 1;
		roots[1] = -b/a;
	}
	else
	{
		roots[0] = 0;
	}

	return roots;
}

template <>
roots_t math::Polynomial<2>::roots()
{
	// at^2 + bt + c = 0
	const double & a = data_[2];
	const double & b = data_[1];
	const double & c = data_[0];

	roots_t roots;


	// Check for actual degree of polynomial
	if (a != 0)
	{
		roots[1] = -b/a;
	}


	double discriminant = b*b - 4.0f*a*c;

	if (discriminant > 0.0f)
	{
		double sqrt_of_discriminant = sqrt(discriminant);


		roots[0] = 2;
		roots[1] = (-b + sqrt_of_discriminant)/(2.0f*a);
		roots[2] = (-b - sqrt_of_discriminant)/(2.0f*a);
	}
	else if (discriminant == 0)
	{
		roots[0] = 1;
		roots[1] = -b/(2.0f*a);
	}

	return roots;
}

template <>
roots_t math::Polynomial<3>::roots()
{
	// at^3 + bt^2 + ct + d = 0
	const double & a = data_[3];
	const double & b = data_[2];
	const double & c = data_[1];
	const double & d = data_[0];

	roots_t roots;

	return roots;
}

template <int degree>
roots_t math::Polynomial<degree>::roots()
{
	roots_t roots;

	return roots;
}
/* ============================================================================ */

#endif
