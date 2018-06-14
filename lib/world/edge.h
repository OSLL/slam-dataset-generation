#ifndef EDGE_H
#define EDGE_H

#include "misc/vec.h"
#include <iostream>

/* NOTE:
 * The purpose of this class is to serve as the abstract base class for all edges.
 * 
 * It should only contain the interface necessary for all edges to have.
 */

class Edge {
	public:
		Edge(const Vec & start_point, const Vec & end);
		virtual ~Edge();

		virtual double distance(const Vec & pos, const Vec & visual_range) = 0;

		virtual void print(std::ostream & o = std::cout, int tabs = 0) const;

		// No harm in exposing to public, since both are const
		const Vec & start;
		const Vec end;

		friend class Path;
};

std::ostream & operator<<(std::ostream & o, const Edge & e);

#endif
