#include "structs/edge.h"

using std::ostream;

Edge::Edge(Vec2D v1_val, Vec2D v2_val) :
	v1(v1_val),
	v2(v2_val)
{ }

ostream & operator<<(ostream & o, Edge e) {
	o << e.v1 << " -> " << e.v2;
	return o;
}
