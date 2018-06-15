#ifndef OBSERVATIONPATH_H
#define OBSERVATIONPATH_H

#include "misc/vec.h"
#include <set>

class ObservationPath {
	public:
		ObservationPath(const Vec & start_point, const Vec & end_point);

		Vec start;
		Vec end;

		void (*on_path)(const Vec & p, const ObservationPath & op);
};

#endif
