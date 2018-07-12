#include "observationpath/Line.h"
#include "math/Vec.h"

using std::ostream;

Line::Line(const Vec & start_point, const Vec & end_point):
	ObservationPath(start_point, end_point, nullptr)
{ }

void Line::print(ostream & o, int tabs) const {
	// Print out correct number of tabs
	for (int i = 0; i < tabs; i++) {
		o << '\t';
	}

	// Print data
	o << "Line : " << start << " -> " << end;
}
