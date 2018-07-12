#ifndef CUBICSPLINEEDGE_H
#define CUBICSPLINEEDGE_H

#include "math/CubicPolynomial.h"

struct CubicSplineEdge {
	CubicPolynomial x;
	CubicPolynomial y;
};

#endif
