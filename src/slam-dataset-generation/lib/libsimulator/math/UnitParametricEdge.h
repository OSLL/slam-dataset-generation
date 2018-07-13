#ifndef MATH_UNITPARAMETRICEDGE_H
#define MATH_UNITPARAMETRICEDGE_H

#include "math/Vec.h"

class UnitParametricEdge
{
public:
	
	UnitParametricEdge() = default;
	virtual ~UnitParametricEdge() = default;

	virtual Vec operator()(double t) const = 0;
	virtual Vec derivative(double t, int n = 1) const = 0;
};

#endif
