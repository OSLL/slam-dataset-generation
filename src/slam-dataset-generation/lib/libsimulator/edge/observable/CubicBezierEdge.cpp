#include "edge/observable/CubicBezierEdge.h"
#include "math/find_roots.h"
#include <iostream>
#include <cmath>

using std::cout;
using std::endl;
using std::ostream;
using std::set;

CubicBezierEdge::CubicBezierEdge(const Vec & start_point, const Vec & c1, const Vec & c2, const Vec & end_point) :
	ObstacleEdge(start_point, end_point),
	control_1(c1),
	control_2(c2),
	A(-start + 3*control_1 - 3*control_2 + end),
	B(3*start - 6*control_1 + 3*control_2),
	C(-3*start + 3*control_1),
	D(start)
{ }

set<Vec> CubicBezierEdge::linear_intersection_points(const ObservationPath & op) const {
	// Initialize set of intersections
	set<Vec> intersections;

	// Edge is characterized by R(t) = At^3 + Bt^2 + Ct + D
	// ObservationPath is given by op.ab.a*x + op.ab.b*y = op.c
	// 			    -> op.ab dot R(t) = op.c
	// 		   	    -> op.ab dot [At^3 + Bt^2 + Ct + D] = op.c
	// 			    -> op.ab dot At^3 + op.ab dot Bt^2 + op.ab dot Ct + op.ab dot D - op.c = 0
	//
	// Find solutions t to that polynomial, check whether they lie in [0, 1], and then construct the intersection points if they do

	// a = op.ab dot A
	double a = dot(op.ab, A);
	// b = op.ab dot B
	double b = dot(op.ab, B);
	// c = op.ab dot C
	double c = dot(op.ab, C);
	// d = op.ab dot D - op.c
	double d = dot(op.ab, D) - op.c;

	// Find roots to this polynomial
	std::set<double> roots = find_roots(a, b, c, d);

	// For all the roots t where 0 <= t <= 1, fetch the position and insert it into the intersection set
	for (const double & root : roots) {
		if (root >= 0 && root <= 1) {
			intersections.insert(get_pos(root));
		}
	}

	return intersections;
}

Vec CubicBezierEdge::get_pos(const double & t) const {
	Vec pos = A*(t*t*t) + B*(t*t) + C*t + D;
	return pos;
}

void CubicBezierEdge::print(ostream & o, int tabs) const {
	// Print out correct number of tabs
	for (int i = 0; i < tabs; i++) {
		o << '\t';
	}

	// Print data
	o << "CubicBezierEdge: " << start << " -> " << end << ", c1 = " << control_1 << ", c2 = " << control_2;
}
