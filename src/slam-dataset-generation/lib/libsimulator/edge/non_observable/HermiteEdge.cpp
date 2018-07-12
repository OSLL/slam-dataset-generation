#include "edge/non_observable/HermiteEdge.h"
#include <cmath>

HermiteEdge::HermiteEdge(const Pose & pose1, const Pose & pose2) {

	const Vec & p1 = pose1.pos;
	const Vec & p2 = pose2.pos;

	// Form m1 and m2 vectors
	const Vec m1 = 0.2f * Vec {cos(pose1.theta), sin(pose1.theta)};
	const Vec m2 = 0.2f * Vec {cos(pose2.theta), sin(pose2.theta)};

	// Make vector equation r(t) = At^3 + Bt^2 + Ct + D
	Vec A = 2*p1 + m1 - 2*p2 + m2;
	Vec B = -3*p1 - 2*m1 + 3*p2 - m2;
	Vec C = m1;
	Vec D = p1;

	// Initialize CubicSplineEdge data
	x.a = A.x;
	x.b = B.x;
	x.c = C.x;
	x.d = D.x;

	y.a = A.y;
	y.b = B.y;
	y.c = C.y;
	y.d = D.y;
}

Vec HermiteEdge::derivative(double t) const {
	return {x.derivative(t), y.derivative(t)};
}

Vec HermiteEdge::operator()(double t) const {
	return {x(t), y(t)};
}
