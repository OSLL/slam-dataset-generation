#include "misc/find_roots.h"
#include "misc/misc.h" // for sign()
#include <iostream>
#include <cstdlib>
#include <cstdio>
#include <cmath>

using std::abs;
using std::max;
using std::cout;
using std::endl;
using std::set;

static double f(const double & b, const double & c, const double & d, const double & t) {
	return t*t*t + b*t*t + c*t + d;
}

static double f_prime(const double & b, const double & c, const double & d, const double & t) {
	return 3*t*t + 2*b*t + c;
}

static double find_one_root(const double & b, const double & c, const double & d, set<double> & roots) {
	
	// for x^3 + ax^2 + bx + c = 0, |x| <= max(1, |a| + |b| + |c|)
	const double max_abs_x = max(1.0, abs(b) + abs(c) + abs(d));

	// Initialize right and left bounds for search interval
	double right_bound = max_abs_x;
	double left_bound = -max_abs_x;

	const double tolerance = 0.000001;
	const uint32_t max_iterations = 999999999; // I WANT THAT ANSWER DAMNIT

	// Bisect until interval is within tolerance or max iterations has been reached
	for (uint32_t i = 0; i < max_iterations; i++) {

		// Generate guess
		double guess = (left_bound + right_bound) / 2;

		// Test guess
		double f_of_guess = f(b, c, d, guess);
		if (right_bound - left_bound < tolerance) {
			cout << "Found root: " << guess << endl;
			roots.insert(guess);
			return guess;
		} else if (sign(f_of_guess) == sign( f(b, c, d, left_bound) )) {
			left_bound = guess;
		} else {
			right_bound = guess;
		}

	}

	// Failed to find root
	printf("\nCould not locate roots for t^3 + %.8ft^2 + %.8ft + %.8f\n", b, c, d);
	printf("Searched in area [%.8f, %.8f]\n\n", -max_abs_x, max_abs_x);
	return 0;
}

set<double> find_roots(double a, double b, double c, double d) {

	// Prior to normalization
	//printf("Finding the roots for %ft^3 + %ft^2 + %ft + %f\n", a, b, c, d);

	// Normalize cubic
	if (a != 0) {
		b /= a;
		c /= a;
		d /= a;
		a = 1;
	}

	// After normalization
	//printf("Finding the roots for %ft^3 + %ft^2 + %ft + %f\n", a, b, c, d);

	// Construct set
	set<double> roots;

	// Find the one real root
	double r1 = find_one_root(b, c, d, roots);

	// Check if the first root was found
	if (roots.empty()) {
		return roots;
	} else {
		//cout << "First root found: " << r1 << endl;
	}

	// Reduce the polynomial to a quadratic and find the rest of the roots
	a = 1;
	b += r1*a;
	c += r1*b;
	d += r1*c;

	// Remaining quadratic is given by ax^2 + bx + c
	//
	// Check the discriminate to see if roots remain
	double discriminant = b*b - 4*a*c;
	if (discriminant >= 0) {
		double sqrt_of_discriminant = sqrt(discriminant);
		roots.insert( (-b + sqrt_of_discriminant) / (2 * a) );
		roots.insert( (-b - sqrt_of_discriminant) / (2 * a) );
	}

	return roots;
}
