#ifndef GRAPH_H
#define GRAPH_H

#include "structs/path.h"

#include <vector>

class Graph {
	public:
		Graph();
		void add_edge(std::vector<Vec>);
};

#endif
