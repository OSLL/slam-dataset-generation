#include "observationpath/linesegment.h"
#include <algorithm>
#include <cstdlib>

using std::min;
using std::max;
using std::ostream;

LineSegment::LineSegment(const Vec & start_point, const Vec & end_point) :
	ObservationPath(start_point, end_point, on_line_segment)
{ }

bool LineSegment::on_line_segment(const Vec & p, const ObservationPath & op) {
	// Either the segment is vertical or it is not
	//
	// If it isn't vertical, we test if p.x is within [op.start.x, op.end.x]
	//
	// If it is vertical, we test if p.y is within [op.start.y, op.end.y]

	double dx = abs(op.end.x - op.start.x);
	const double epsilon = 0.01;

	if (dx < epsilon) {
		double x_min = min(op.start.x, op.end.x);
		double x_max = max(op.start.x, op.end.x);
		return (p.x >= x_min) && (p.x <= x_max);
	} else {
		double y_min = min(op.start.y, op.end.y);
		double y_max = max(op.start.y, op.end.y);
		return (p.y >= y_min) && (p.y <= y_max);
	}
}

void LineSegment::print(ostream & o, int tabs) const {
	// Print out correct number of tabs
	for (int i = 0; i < tabs; i++) {
		o << '\t';
	}

	// Print data
	o << "LineSegment: " << start << " -> " << end;
}
