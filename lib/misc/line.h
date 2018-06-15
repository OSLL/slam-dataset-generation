#ifndef LINE_H
#define LINE_H

#include "misc/observationpath.h"

class Line : public ObservationPath {
	public:
		Line(const Vec & start_point, const Vec & end_point);

		static bool on_line(const Vec & p, const ObservationPath & op);
};

#endif
