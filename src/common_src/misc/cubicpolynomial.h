#ifndef CUBICPOLYNOMIAL_H
#define CUBICPOLYNOMIAL_H

struct CubicPolynomial {
	double a;
	double b;
	double c;
	double d;

	double operator()(double t) {
		return a*t*t*t + b*t*t + c*t + d;
	}

	double derivative(double t) {
		return 3*a*t*t + 2*b*t + c;
	}
};

#endif
