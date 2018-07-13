#ifndef MATH_POLYNOMIAL_H
#define MATH_POLYNOMIAL_H

#include <array>
#include <vector>
#include <cmath>
#include <iostream>
#include "math/RootFinder.h"

template <int degree>
class Polynomial
{
public:
	using coefficients_t = std::array<double, degree + 1>;
	using roots_t = std::vector<double>;

	Polynomial() = default;

	template <typename ... Args>
	Polynomial(Args ... args);

	double operator()(double t) const;

	double derivative(double t, int n = 1) const;
	
	roots_t roots() const;

	void print(std::ostream & o = std::cout) const;
private:
	// An n-degree polynomial needs n + 1 coefficients because of the constant term
	coefficients_t coefficients_;

	// A Polynomial<n> can hold a polynomial of up to degree n
	// Knowing the actual order of the stored polynomial allows dynamic dispatch to the correct root-finding procedure
	void updateActualOrder();
	int actual_order_;

	// Check template parameters to ensure Polynomial is well-formed
	template <typename ... Args>
	void checkValidity();
};

/* ==================== Constructor and argument validation =================== */
template <int degree>
template <typename ... Args>
Polynomial<degree>::Polynomial(Args ... args)
	// Call to check validity does some static_asserts to make sure template parameter pack is valid
	: coefficients_(
		(
			checkValidity<Args ...>(),
			std::move(coefficients_t { static_cast<double>(args) ... })
		)
	)
{
	updateActualOrder();
}

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
void Polynomial<degree>::checkValidity()
{
	static_assert(degree >= 0, "Cannot instantiate a Polynomial of degree < 0.");
	static_assert(sizeof...(Args) == degree + 1, "Incorrect number of parameters for Polynomial constructor");
	static_assert(and_<std::is_convertible<Args, double> ...>::value, "One of the parameters to the Polynomial constructor has an incorrect type.");
}

template <int degree>
void Polynomial<degree>::updateActualOrder()
{
	actual_order_ = degree;

	for (auto & coefficient : coefficients_)
	{
		if (coefficient != 0)
			break;
		else
			--actual_order_;
	}
}
/* ============================================================================ */



/* ====================== Function operator & derivative ====================== */
template <int degree>
double Polynomial<degree>::operator()(double t) const
{
	double sum = 0;

	for (int i = 0; i < actual_order_ + 1; i++)
	{
		sum += coefficients_[i] * std::pow(t, i);
	}

	return sum;
}

inline constexpr int f(int i, int n)
{
		return (n == 0)? 1 : i * f(i - 1, n - 1);
}

template <int degree>
double Polynomial<degree>::derivative(double t, int n) const
{
	double sum = 0;

	for (int i = 0; i < actual_order_; i++)
	{
		// d^n/dx^n [a[i] * x^i] = a[i] * [ i * (i - 1) * (i - 2) * ... (i - (n - 1)) ] * x^(i-n)
		//
		// Let f(i, n) = i * (i - 1) * (i - 2) * ... * (i - (n - 1))
		//
		// Then, d^n/dx^n [a[i] * x^i] = a[i] * f(i, n) * x^(i-n)
		sum += coefficients_[i] * f(i, n) * std::pow(t, i - n);
	}

	return sum;
}
/* ============================================================================ */



/* =============================== Root finding =============================== */
template <int degree>
typename Polynomial<degree>::roots_t Polynomial<degree>::roots() const
{
	switch (actual_order_)
	{
		case 0:
			return {};
		case 1:
			return RootFinder::linear(coefficients_.data());
		case 2:
			return RootFinder::quadratic(coefficients_.data());
		case 3:
			return RootFinder::cubic(coefficients_.data());
		default:
			std::cout << "Rootfinding for polynomials of degree " << degree << " not implemented.  Returning empty set." << std::endl;
			return {};
	}
}
/* ============================================================================ */


/* ================================= Printing ================================= */
template <int degree>
void Polynomial<degree>::print(std::ostream & o) const
{
	for (int i = degree; i > 0; i--)
	{
		if (i == 1)
			o << coefficients_[i] << "t + ";
		else
			o << coefficients_[i] << "t^" << i << " + ";
	}
	o << coefficients_[0];
}

template <int degree>
std::ostream & operator<<(std::ostream & o, const Polynomial<degree> f)
{
	f.print(o);
	return o;
}
/* ============================================================================ */

#endif
