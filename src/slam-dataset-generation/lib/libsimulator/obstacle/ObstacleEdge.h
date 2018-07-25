#ifndef OBSTACLE_OBSTACLEEDGE_H
#define OBSTACLE_OBSTACLEEDGE_H

#include "math/Vec.h"
#include "observationpath/ObservationPath.h"
#include <iostream>
#include <set>

/* NOTE:
 * The purpose of this class is to serve as the abstract base class for all edges.
 * 
 * It should only contain the interface necessary for all edges to have.
 */

class ObstacleEdge {
	public:
		ObstacleEdge(const Vec & start_point, const Vec & end);

		const Vec & getStart() const {return start;}
		const Vec & getEnd() const {return end;}

		// Defined in Edge
		std::set<Vec> intersection_points(const Vec & edge_offset, const ObservationPath &) const;
		double distance(const Vec & edge_offset, const ObservationPath &) const;

		// Can be defined in subclass
		int number_of_intersections(const Vec & edge_offset, const ObservationPath &) const;
		virtual void print(std::ostream & o = std::cout, int tabs = 0) const;

		// Must be defined in subclass
		virtual std::set<Vec> linear_intersection_points(const Vec & edge_offset, const ObservationPath & op) const = 0;
		virtual Vec get_pos(const double & t) const = 0; // 0 <= t <= 1 for all adges

	protected:
		const Vec & start;
		const Vec end;
		
};

std::ostream & operator<<(std::ostream & o, const ObstacleEdge & e);

#endif
