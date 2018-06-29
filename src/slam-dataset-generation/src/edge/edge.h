#ifndef EDGE_H
#define EDGE_H

#include "misc/vec.h"
#include "observationpath/observationpath.h"
#include <iostream>
#include <set>

/* NOTE:
 * The purpose of this class is to serve as the abstract base class for all edges.
 * 
 * It should only contain the interface necessary for all edges to have.
 */

class Edge {
	public:
		Edge(const Vec & start_point, const Vec & end);

		// Defined in Edge
		std::set<Vec> intersection_points(const ObservationPath &) const;
		double distance(const ObservationPath &) const;

		// Can be defined in subclass
		int number_of_intersections(const ObservationPath &) const;
		virtual void print(std::ostream & o = std::cout, int tabs = 0) const;

		// Must be defined in subclass
		virtual std::set<Vec> linear_intersection_points(const ObservationPath &) const = 0;
		virtual Vec get_pos(const double & t) const = 0; // 0 <= t <= 1 for all adges

		// No harm in exposing to public, since both are const
		const Vec & start;
		const Vec end;

		friend class Path;
};

std::ostream & operator<<(std::ostream & o, const Edge & e);

#endif
