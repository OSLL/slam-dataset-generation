#include "world/edge.h"

using std::ostream;
using std::cout;

Edge::Edge(const Vec & start_point, const Vec & end_point) :
	start(start_point),
	end(end_point)
{ }

Edge::~Edge() { }

void Edge::print(ostream & o, int tabs) const {
	// Print out the correct number of tabs
	for (int i = 0; i < tabs; i++) {
		cout << '\t';
	}

	// Print edge information
	o << "Edge: " << start << " -> " << end;
}

ostream & operator<<(ostream & o, const Edge & e) {
	e.print(o);
	return o;
}
