#ifndef EDGE_H
#define EDGE_H

#include "misc/vec.h"
#include "misc/observationpath.h"
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
		std::set<Vec> intersection_points(const ObservationPath &);
		double distance(const ObservationPath &);

		// Can be defined in subclass
		int number_of_intersections(const ObservationPath &);
		virtual void print(std::ostream & o = std::cout, int tabs = 0) const;

		// Must be defined in subclass
		virtual std::set<Vec> linear_intersection_points(const ObservationPath &) = 0;

		// No harm in exposing to public, since both are const
		const Vec & start;
		const Vec end;

		friend class Path;
};

std::ostream & operator<<(std::ostream & o, const Edge & e);

#endif
