#ifndef PATH_H
#define PATH_H

#include <vector>
#include "world/edge.h"

class Path {
	private:
	public:
		Path(const Vec & start_point);
		Path();
		~Path();

		Vec start;
		Vec end;
		std::vector<Edge *> edges;

		void add_edge(Edge * e);
};

#endif
