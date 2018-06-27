#ifndef CUBICSPLINEEDGE_H
#define CUBICSPLINEEDGE_H

#include "misc/cubicpolynomial.h"

struct CubicSplineEdge {
	CubicPolynomial x;
	CubicPolynomial y;
};

#endif
