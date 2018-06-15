#include "world/bezieredge.h"
#include <cmath>

using std::ostream;
using std::set;

BezierEdge::BezierEdge(const Vec & start_point, const Vec & c1, const Vec & c2, const Vec & end_point) :
	Edge(start_point, end_point),
	control_1(c1),
	control_2(c2)
{ }

set<Vec> BezierEdge::intersection(const Vec & pos, const Vec & range) {
	// Initialize set of intersections
	set<Vec> intersections;

	return intersections;
}

void BezierEdge::print(ostream & o, int tabs) const {
	// Print out correct number of tabs
	for (int i = 0; i < tabs; i++) {
		o << '\t';
	}

	// Print data
	o << "BezierEdge: " << start << " -> " << end << ", c1 = " << control_1 << ", c2 = " << control_2;
}
