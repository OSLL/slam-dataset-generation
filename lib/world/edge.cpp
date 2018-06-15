#include "world/edge.h"

using std::ostream;
using std::cout;
using std::set;

Edge::Edge(const Vec & start_point, const Vec & end_point) :
	start(start_point),
	end(end_point)
{ }


static double closest_distance(const Vec & p, const set<Vec> & s) {
	if (!s.empty()) {
		// Obtain iterator to set (guaranteed to have at least one element)
		set<Vec>::iterator i = s.begin();

		// Start by assuming closest distance is the first element of the set and advance iterator
		double result = (*i - p).mag();
		i++;

		// Loop over rest of set (if it exists) to determine actual closest distance
		for (; i != s.end(); i++) {
			// Get distance between p and this particular intersection point
			double distance = (*i - pos).mag();

			if (distance < result) {
				result = distance;
			}
		}

		return result;
	} else {
		return -1.0;
	}
}

double Edge::distance(const ObservationPath & op) {
	set<Vec> path_intersection_points = intersection_points(op);
	return closest_distance(pos, path_intersection_points);
}

std::set<Vec> Edge::intersection(const ObservationPath & op) {
	// Obtain set of intersection points as though op was a Line
	set<Vec> line_intersection_points = linear_intersection_points(op);

	// Construct a new set of only the points that
	set<Vec> result;
	for (Vec v : line_intersection_points) {
		if (op.cannot_be_on_path(v, op)) {
			
		}
	}

	return result;
}

// For some edge types, the only way to find the number of intersections
// is to analytically find all intersection points and count them
//
// If there is a faster way for a particular edge type to accomplish this,
// these are virtual and can be defined in a subclass

int Edge::number_of_intersections(const ObservationPath & op) {
	return intersection_points(op).size();
}

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
