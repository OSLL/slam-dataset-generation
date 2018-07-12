#include "edge/observable/LinearEdge.h"
#include <iostream>
#include <algorithm>
#include <cmath>

using std::min;
using std::max;
using std::ostream;
using std::set;
using std::cout;
using std::endl;

LinearEdge::LinearEdge(const Vec & start_point, const Vec & end_point) :
	Edge(start_point, end_point),
	direction(end-start)
{ }

set<Vec> LinearEdge::linear_intersection_points(const ObservationPath & op) const {
	
	// Initialize set of intersections
	set<Vec> intersections;

	// Edge is characterized by R(t) = start + direction*t
	// ObservationPath is characterized by op.a*x + op.b*y = op.c
	// 				    -> <op.a, op.b> dot R(t) = op.c
	// 				    -> <op.a, op.b> dot [start + direction*t] = op.c
	// 				    -> <op.a, op.b> dot start + <op.a, op.b> dot direction*t = op.c
	// 				    -> t = (op.c - <op.a, op.b> dot start) / <op.a, op.b> dot direction
	// 
	// Note that t is only valid if denominator != 0


	// Calculate denominator
	double denominator = dot(op.ab, direction);

	// If denominator isn't zero, we do further calculation
	if (denominator != 0) {
		// Calculate numerator
		double numerator = op.c - dot(op.ab, start);

		// Calculate value of t for intersection
		double t = numerator / denominator;
		
		// t is only on the edge if 0 <= t <= 1
		if (t >= 0 && t <= 1) {
			intersections.insert(get_pos(t));
		}
	}
	
	return intersections;
}

Vec LinearEdge::get_pos(const double & t) const {
	return start + direction*t;
}

void LinearEdge::print(ostream & o, int tabs) const {
	// Print out the correct number of tabs
	for (int i = 0; i < tabs; i++) {
		o << '\t';
	}

	// Print out data
	o << "LinearEdge: " << start << " -> " << end;
}
