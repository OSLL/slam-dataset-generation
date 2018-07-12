#ifndef EDGEPATH_H
#define EDGEPATH_H

#include "edge/observable/Edge.h"
#include "observationpath/ObservationPath.h"
#include <vector>
#include <iostream>

class EdgePath {
	private:
		const Vec * end_ptr;
	public:
		EdgePath(const Vec & start_point);
		~EdgePath();

		const Vec start;
		std::string id;

		const Vec & end();


		std::vector<Edge *> edges;

		void add_edge(Edge * e);
		void print(std::ostream & o = std::cout, int tabs = 0) const;

		// Raytracing
		bool is_in(const Vec & p);
		double distance(const ObservationPath & op) const;
};

std::ostream & operator<<(std::ostream & o, const EdgePath & path);

#endif
