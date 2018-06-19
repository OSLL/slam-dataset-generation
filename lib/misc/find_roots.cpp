#include "misc/find_roots.h"
#include <iostream>
#include <cstdlib>
#include <cmath>

using std::abs;
using std::max;
using std::signbit;
using std::cout;
using std::endl;
using std::set;

// A lambda for f and f' will be useful
static double f(const double & b, const double & c, const double & d, const double & t) {
	return t*t*t + b*t*t + c*t + d;
}

static double f_prime(const double & b, const double & c, const double & d, const double & t) {
	return 3*t*t + 2*b*t + c;
}

static double find_one_root(const double & b, const double & c, const double & d, set<double> & roots) {

	// Uses Newton's method to search for first root

	const double tolerance = 0.00001;
	const int max_iterations = 20;
	
	// for x^3 + ax^2 + bx + c = 0, |x| <= max(1, |a| + |b| + |c|)
	double right = max(1.0, abs(b) + abs(c) + abs(d));
	double left = -right;

	// Initialize guess (NOTE: f_prime(b, c, d, guess) must not be 0)
	double guess = 0;
	while (f_prime(b, c, d, guess) == 0) {
		guess += 0.1;
	}

	for (int iterations = 0; iterations < max_iterations; iterations++) {

		// Generate guess
		guess -= f(b, c, d, guess) / f_prime(b, c, d, guess);

		// Test guess
		double f_guess = f(b, c, d, guess);
		if (abs(f_guess) < tolerance) {
			roots.insert(guess);
			return guess;
		}
	}
}

set<double> find_roots(double a, double b, double c, double d) {

	// Normalize cubic
	b /= a;
	c /= a;
	d /= a;
	a = 1;

	// Construct set
	set<double> roots;

	printf("Finding the roots for %ft^3 + %ft^2 + %ft + %f\n", a, b, c, d);

	// Find the one real root
	double r1 = find_one_root(b, c, d, roots);

	// Check if the first root was found
	if (roots.empty()) {
		cout << "First root could not be found" << endl;
	} else {
		cout << "First root found: " << r1 << endl;
	}

	// Reduce the polynomial to a quadratic and find the rest of the roots
	a = 1;
	b -= r1*a;
	c -= r1*b;
	d -= r1*c;

	cout << "Remainder: " << d << endl;

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
