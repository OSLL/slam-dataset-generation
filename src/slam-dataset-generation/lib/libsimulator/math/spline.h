#ifndef MATH_SPLINE_H
#define MATH_SPLINE_H

#include "misc/vec.h"
#include "math/polynomial.h"

class Spline
{
public:
	Vec operator()(double t) {return {x(t), y(t)};};
private:
	math::Polynomial x;
	math::Polynomial y;
};

#endif
