#ifndef PATH_H
#define PATH_H

#include "world/edge.h"
#include <vector>
#include <iostream>

class Path {
	private:
		const Vec * end_ptr;
	public:
		Path(const Vec & start_point);
		~Path();

		const Vec start;
		std::string id;

		const Vec & end();


		std::vector<Edge *> edges;

		void add_edge(Edge * e);
		void print(std::ostream & o = std::cout, int tabs = 0) const;
		bool is_in(const Vec & p);
};

std::ostream & operator<<(std::ostream & o, const Path & path);

#endif
