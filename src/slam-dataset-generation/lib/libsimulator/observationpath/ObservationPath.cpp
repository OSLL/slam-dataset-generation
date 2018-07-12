#include "observationpath/ObservationPath.h"

#include <iostream>

using std::cout;
using std::endl;
using std::ostream;

ObservationPath::ObservationPath(const Vec & start_point, const Vec & end_point, bool (*on_path_fn)(const Vec &, const ObservationPath &)) :
	start(start_point),
	end(end_point),
	ab(start.y - end.y, end.x - start.x),
	c(dot(start, ab)),
	on_path(on_path_fn)
{ }


void ObservationPath::print(ostream & o, int tabs) const {
	// Print correct number of tabs
	for (int i = 0; i < tabs; i++) {
		o << '\t';
	}

	// Print data
	o << "ObservationPath: " << start << " -> " << end;
}

ostream & operator<<(ostream & o, const ObservationPath & op) {
	op.print(o);
	return o;
}
