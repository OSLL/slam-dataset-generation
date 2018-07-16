#ifndef OBSERVATIONPATH_LINESEGMENT_H
#define OBSERVATIONPATH_LINESEGMENT_H

#include "observationpath/ObservationPath.h"
#include "math/Vec.h"

class LineSegment : public ObservationPath {
	public:
		LineSegment(const Vec & start_point, const Vec & end_point);

		static bool on_line_segment(const Vec & p, const ObservationPath & op);
		void print(std::ostream & o = std::cout, int tabs = 0) const;
};

#endif
