#include "edge/observable/ObstacleEdge.h"

using std::ostream;
using std::cout;
using std::endl;
using std::set;

ObstacleEdge::ObstacleEdge(const Vec & start_point, const Vec & end_point) :
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
			double distance = (*i - p).mag();

			if (distance < result) {
				result = distance;
			}
		}

		return result;
	} else {
		return -1.0;
	}
}

double ObstacleEdge::distance(const ObservationPath & op) const {
	set<Vec> path_intersection_points = intersection_points(op);

	return closest_distance(op.start, path_intersection_points);
}

std::set<Vec> ObstacleEdge::intersection_points(const ObservationPath & op) const {
	// Obtain set of intersection points as though op was a Line
	set<Vec> line_intersection_points = linear_intersection_points(op);

	// If op has a filtering function, then perform filtering on the set
	if (op.on_path != nullptr) {
		for (auto itr = line_intersection_points.cbegin(); itr != line_intersection_points.cend();) {
			if (!op.on_path(*itr, op)) {
				//cout << "Point " << *itr << " is not on path " << op << ".  Filtering out..." << endl;
				itr = line_intersection_points.erase(itr);
			} else {
				itr++;
			}
		}
	}

	return line_intersection_points;
}

// For some edge types, the only way to find the number of intersections
// is to analytically find all intersection points and count them
//
// If there is a faster way for a particular edge type to accomplish this,
// these are virtual and can be defined in a subclass

int ObstacleEdge::number_of_intersections(const ObservationPath & op) const {
	return intersection_points(op).size();
}

void ObstacleEdge::print(ostream & o, int tabs) const {
	// Print out the correct number of tabs
	for (int i = 0; i < tabs; i++) {
		cout << '\t';
	}

	// Print edge information
	o << "ObstacleEdge: " << start << " -> " << end;
}

ostream & operator<<(ostream & o, const ObstacleEdge & e) {
	e.print(o);
	return o;
}
