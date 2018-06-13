#include "world/bezieredge.h"
#include <cmath>

BezierEdge::BezierEdge(const Vec & start_point, const Vec & c1, const Vec & c2, const Vec & end_point) :
	start(start_point),
	control_1(c1),
	control_2(c2),
	end(end_point)
{ }

double BezierEdge::distance(const Vec & pos, const Vec & range) {

}
