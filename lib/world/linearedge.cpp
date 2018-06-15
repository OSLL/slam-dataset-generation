#include "world/linearedge.h"
#include <algorithm>
#include <cmath>

using std::min;
using std::max;
using std::ostream;
using std::set;

LinearEdge::LinearEdge(const Vec & start_point, const Vec & end_point) :
	Edge(start_point, end_point)
{ }

static inline bool is_on(const Vec & p, const LinearEdge & e) {
	double x_min = min(e.start.x, e.end.x);
	double x_max = max(e.start.x, e.end.x);
	double y_min = min(e.start.y, e.end.y);
	double y_max = max(e.start.y, e.end.y);

	return (p.x >= x_min && p.x <= x_max) && (p.y >= y_min && p.y <= y_max);
}

set<Vec> LinearEdge::intersection(const Vec & pos, const Vec & range) {
	// Initialize set of intersections
	set<Vec> intersections;

	// Represent edge as a1*x + b1*y = c1
	double a1 = start.y - end.y;
	double b1 = end.x - start.x;
	double c1 = start.x*a1 + start.y*b1;

	// Represent view as a2*x + b2*y = c2
	double a2 = -range.y;
	double b2 = range.x;
	double c2 = pos.x*a2 + pos.y*b2;

	// Determinant will quickly tell us if the lines are parallel
	double det = a1*b2 - a2*b1;
	if (det != 0) {
		// Calculate intersection (not guaranteed to be on line segment)
		double x = (b2*c1 - b1*c2)/det;
		double y = (a1*c2 - a2*c1)/det;
		Vec i {x, y};

		// Check if (x,y) is on both line segments
		if (is_on(i, {start, end}) && is_on(i, {pos, pos + range})) {
			intersections.insert(i);
		}
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
