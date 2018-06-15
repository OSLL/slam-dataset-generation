#include "misc/line.h"
#include "misc/vec.h"

Line::Line(const Vec & start_point, const Vec & end_point):
	ObservationPath(start_point, end_point),
	on_path(Line::on_line)
{ }

// Quickly check whether a point is on the line
bool Line::on_line(const Vec & p, const ObservationPath & op) {
	return true;
}
