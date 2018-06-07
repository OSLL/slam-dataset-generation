#include "structs/path.h"

Path::Path(bool is_world_boundary_value) :
	is_world_boundary(is_world_boundary_value)
{
	edges.push_back({{2.2, 2.2}, {5.5, 5.5}});
}

void Path::add_edge(Edge e) {
	edges.push_back(e);
}
