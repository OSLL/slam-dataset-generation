#include "math/root_finder.h"
//#include "math/find_roots.h"
#include <cstdlib>
#include <cmath>

using std::abs;
using std::max;
using std::vector;

#include <iostream>
using std::cout;
using std::endl;

vector<double> math::RootFinder::linear(const double * coefficients)
{
	// at + b = 0
	const double & a = coefficients[1];
	const double & b = coefficients[0];
	
	vector<double> roots;

	// Check for actual degree of polynomial
	if (a != 0)
	{
		roots.push_back(-b/a);
	}

	return roots;
}

vector<double> math::RootFinder::quadratic(const double * coefficients)
{
	// at^2 + bt + c = 0
	const double & a = coefficients[2];
	const double & b = coefficients[1];
	const double & c = coefficients[0];

	vector<double> roots;

	double discriminant = b*b - 4.0f*a*c;

	if (discriminant > 0.0f)
	{
		double sqrt_of_discriminant = sqrt(discriminant);

		roots.push_back( (-b + sqrt_of_discriminant)/(2.0f*a) );
		roots.push_back( (-b - sqrt_of_discriminant)/(2.0f*a) );
	}
	else if (discriminant == 0)
	{
		roots.push_back( -b/(2.0f*a) );
	}

	return roots;
}

vector<double> math::RootFinder::cubic(const double * coefficients)
{
	// at^3 + bt^2 + ct + d = 0
	//
	// Note: we create a copy of the coefficients because we will do synthetic divison to reduce to
	// a quadratic after we locate the first root and we don't want to modify the original polynomial.
	//
	// They're gathered in an array so that we can call math::RootFinder::quadratic(const double *)
	double copy_of_coefficients[4] {
		coefficients[0],
		coefficients[1],
		coefficients[2],
		coefficients[3]
	};
	double & a = copy_of_coefficients[3];
	double & b = copy_of_coefficients[2];
	double & c = copy_of_coefficients[1];
	double & d = copy_of_coefficients[0];

	// Normalize the cubic
	b /= a;
	c /= a;
	d /= a;
	a = 1;

	auto f = [&](const double & t) {return t*t*t + b*t*t + c*t + d;};
	auto f_prime = [&](const double & t) {return 3*t*t + 2*b*t + c;};

	const double search_window = 0.000001;

	// for x^3 + bx^2 + cx + d = 0, |x| <= max(1, |b| + |c| + |d| )
	const double max_abs_x = max(1.0, abs(b) + abs(c) + abs(d));

	// Initialize right and left bounds for search interval
	double right_bound = max_abs_x;
	double left_bound = -max_abs_x;

	double guess = (left_bound + right_bound) / 2;
	double f_guess = f(guess);

	// Bisect until search interval is small enough for newton's method to take over
	while (right_bound - left_bound > search_window)
	{
		if (f_guess < 0) {
			left_bound = guess;
		} else {
			right_bound = guess;
		}

		guess = (left_bound + right_bound) / 2;
		f_guess = f(guess);
	}

	// Guess is accurate enough to perform Newton's method
	/*
	const double tolerance = 0.000001;
	while (abs(f_guess) > tolerance)
	{
		guess -= f_guess / f_prime(guess);
		f_guess = f(guess);
	}
	*/

	// Now, we have the first root
	//
	// We use synthetic division to produce three coefficients that present the reduced quadratic
	//
	// Note that the array contains | d | c | b | a |
	//
	// We modify d, c, and b so that they represent the quadratic bt^2 + ct + d

	d = c + (b + a*guess)*guess;
	c = b + a*guess;
	b = a;

	vector<double> roots {guess};
	vector<double> quadratic_roots = quadratic(copy_of_coefficients);
	roots.insert(roots.end(), quadratic_roots.begin(), quadratic_roots.end());

	return roots;
}
