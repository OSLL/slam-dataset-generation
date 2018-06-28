#ifndef HERMITEEDGE_H
#define HERMITEEDGE_H

#include "misc/cubicsplineedge.h"
#include "misc/pose.h"

class HermiteEdge : public CubicSplineEdge {
	public:
		HermiteEdge(const Pose & p1, const Pose & p2);
		
		Vec derivative(double t) const;
		Vec operator()(double t) const;
};

#endif
