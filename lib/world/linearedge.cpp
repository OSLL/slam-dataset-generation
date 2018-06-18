#include "world/linearedge.h"
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
	Edge(start_point, end_point)
{ }

set<Vec> LinearEdge::linear_intersection_points(const ObservationPath & op) {
	// Initialize set of intersections
	set<Vec> intersections;

	// Represent edge as a1*x + b1*y = c1
	double a1 = start.y - end.y;
	double b1 = end.x - start.x;
	double c1 = start.x*a1 + start.y*b1;

	// Represent view as a2*x + b2*y = c2
	double a2 = op.start.y - op.end.y;
	double b2 = op.end.x - op.start.x;
	double c2 = op.start.x*a2 + op.start.y*b2;

	// Determinant will quickly tell us if the lines are parallel
	double det = a1*b2 - a2*b1;
	if (det != 0) {
		// Calculate intersection (not guaranteed to be on line segment)
		double x = (b2*c1 - b1*c2)/det;
		double y = (a1*c2 - a2*c1)/det;
		Vec i {x, y};

		cout << "i = " << i << endl;

		intersections.insert(i);
	}
	
	return intersections;
}

void LinearEdge::print(ostream & o, int tabs) const {
	// Print out the correct number of tabs
	for (int i = 0; i < tabs; i++) {
		o << '\t';
	}

	// Print out data
	o << "LinearEdge: " << start << " -> " << end;
}
