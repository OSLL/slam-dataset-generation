#include "path/observable/EdgePath.h"
#include "observationpath/Ray.h"
#include <iostream>
#include <string>

using std::ostream;
using std::cout;
using std::endl;
using std::string;

EdgePath::EdgePath(const Vec & start_point) :
	start(start_point),
	end_ptr(&start)
{ }

EdgePath::~EdgePath() {
	// In this case, RAII isn't really being obeyed, because dynamic allocation happens in ParsingContext, not in EdgePath
	for (ObstacleEdge * e : edges) {
		delete e;
	}
}

// Getters
const Vec & EdgePath::end() {
	return *end_ptr;
}


void EdgePath::add_edge(ObstacleEdge * e) {
	edges.push_back(e);
	end_ptr = &e->end;
}

void EdgePath::print(ostream & o, int tabs) const {
	// Print the correct number of tabs
	for (int i = 0; i < tabs; i++) {
		o << '\t';
	}

	// Print data
	o << "EdgePath: " << id << endl;
	for (ObstacleEdge * e : edges) {
		e->print(o, tabs + 1);
		o << endl;
	}
}

bool EdgePath::is_in(const Vec & p) {
	// Cast ray in some direction and count the total number of intersections
	Ray ray {p, 0};

	int intersections = 0;
	for (ObstacleEdge * e : edges) {
		intersections += e->number_of_intersections(ray);
	}

	// If number of intersections the ray encountered is odd, then the point is inside the path
	return intersections % 2 == 1;
}

double EdgePath::distance(const ObservationPath & op) const {
	
	double closest_distance = -1;

	for (const ObstacleEdge * e : edges) {

		double distance_to_edge = e->distance(op);

		if (distance_to_edge != -1) {
			if (distance_to_edge < closest_distance || closest_distance == -1) {
				closest_distance = distance_to_edge;
			}
		}
	}

	return closest_distance;
}

ostream & operator<<(ostream & o, const EdgePath & path) {
	path.print();
	return o;
}
