#ifndef LINE_H
#define LINE_H

#include "observationpath/observationpath.h"
#include <iostream>

class Line : public ObservationPath {
	public:
		Line(const Vec & start_point, const Vec & end_point);
		
		void print(std::ostream & o = std::cout, int tabs = 0) const;
};

#endif
