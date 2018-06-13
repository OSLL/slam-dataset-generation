#include "world/path.h"

Path::Path(const Vec & start_point) :
	start(start_point),
	end(start)
{ }

Path::Path() { }

Path::~Path() {
	// In this case, RAII isn't really being obeyed, because dynamic allocation happens in World, not Path
	for (Edge * e : edges) {
		delete e;
	}
}

void Path::add_edge(Edge * e) {
	edges.push_back(e);
}
