#include "world/path.h"
#include "misc/ray.h"
#include <iostream>
#include <string>

using std::ostream;
using std::endl;
using std::string;

Path::Path(const Vec & start_point) :
	start(start_point),
	end_ptr(&start)
{ }

Path::~Path() {
	// In this case, RAII isn't really being obeyed, because dynamic allocation happens in ParsingContext, not in Path
	for (Edge * e : edges) {
		delete e;
	}
}

// Getters
const Vec & Path::end() {
	return *end_ptr;
}


void Path::add_edge(Edge * e) {
	edges.push_back(e);
	end_ptr = &e->end;
}

void Path::print(ostream & o, int tabs) const {
	// Print the correct number of tabs
	for (int i = 0; i < tabs; i++) {
		o << '\t';
	}

	// Print data
	o << "Path: " << id << endl;
	for (Edge * e : edges) {
		e->print(o, tabs + 1);
		o << endl;
	}
}

bool Path::is_in(const Vec & p) {
	// Cast ray in some direction and count the total number of intersections
	Ray ray {p, 0};

	int intersections = 0;
	for (Edge * e : edges) {
		intersections += e->number_of_intersections(ray);
	}

	// If number of intersections the ray encountered is odd, then the point is inside the path
	return intersections % 2 == 1;
}

ostream & operator<<(ostream & o, const Path & path) {
	path.print();
	return o;
}
