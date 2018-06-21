#ifndef LINESEGMENT_H
#define LINESEGMENT_H

#include "observationpath/observationpath.h"
#include "misc/vec.h"

class LineSegment : public ObservationPath {
	public:
		LineSegment(const Vec & start_point, const Vec & end_point);

		static bool on_line_segment(const Vec & p, const ObservationPath & op);
		void print(std::ostream & o = std::cout, int tabs = 0) const;
};

#endif
