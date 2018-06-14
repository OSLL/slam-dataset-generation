#ifndef PATH_H
#define PATH_H

#include "world/edge.h"
#include <vector>
#include <iostream>

class Path {
	private:
		std::string _id;

		const Vec _start;
		const Vec * _end_ptr;
	public:
		Path(const Vec & start_point);
		~Path();

		// Getters
		const Vec & start();
		const std::string & id();
		const Vec & end();

		// Setters
		void set_id(const std::string & id_value);

		std::vector<Edge *> edges;

		void add_edge(Edge * e);
		void print(std::ostream & o = std::cout, int tabs = 0) const;
};

std::ostream & operator<<(std::ostream & o, const Path & path);

#endif
