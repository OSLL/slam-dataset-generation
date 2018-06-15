#ifndef LINESEGMENT_H
#define LINESEGMENT_H

#include "misc/vec.h"

class LineSegment {
	public:
		Vec start;
		Vec end;

		LineSegment(const Vec & start_point, const Vec & end_point);
};

#endif
