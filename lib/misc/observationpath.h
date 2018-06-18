#ifndef OBSERVATIONPATH_H
#define OBSERVATIONPATH_H

#include "misc/vec.h"
#include <iostream>
#include <set>

class ObservationPath {
	public:
		ObservationPath(const Vec & start_point, const Vec & end_point, bool (*)(const Vec &, const ObservationPath &));

		Vec start;
		Vec end;

		// Note that this function only has to distinguish between lines on the line connecting
		// the start and end; it doesn't have to check whether the point exists on the line
		bool (*on_path)(const Vec & p, const ObservationPath & op);

		virtual void print(std::ostream & o = std::cout, int tabs = 0) const;
};

std::ostream & operator<<(std::ostream & o, const ObservationPath & op);

#endif
