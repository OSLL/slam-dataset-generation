#include "structs/splinepath.h"
#include <vector>
#include <cmath>

using std::vector;

SplinePath::SplinePath(vector<Vec> line_path) :
	number_of_intervals(line_path.size() - 1),
	spline_data(new SplineData[number_of_splines]),
	current_spline(spline_data) // Assume first query will be to t=0
{
	//
}

~SplinePath::SplinePath() {
	delete[] spline_data;
}

void SplinePath::find_new_spline(double t) {
	// The splines are sorted by domain, so a binary search makes sense.
	
}

Vec SplinePath::evaluate_spline(SplineData * s, double t) {
	// x(t) = at^3 + bt^2 + ct + d
	double x = (s->a)*pow(t, 3) + (s->b)*pow(t,2) + (s->c)*t + s->d;
	// y(t) = et^3 + ft^2 + gt + h
	double y = (s->e)*pow(t, 3) + (s->f)*pow(t,2) + (s->g)*t + s->h;
	return {x, y};
}

Vec SplinePath::get_pos(double t) {
	// Check if t is within the range of the current spline
	if (t >= current_spline->t_min && t < current_spline->t_max) {
		return Trajectory::evaluate_spline(current_spline, t);
	} else {
		// If there is a next node and t is within its range, return value
		if ( current_spline != spline_data + number_of_splines &&
		     t >= (current_spline+1)->t_min && t < (current_spline+1)->t_max ) {
			current_spline++;
			return SplinePath::evaluate_spline(current_spline, t);
		} else {
			if (find_new_spline(t)) {
				return SplinePath::evaluate_spline(current_spline, t);
			} else {
				// Function was given t that didn't match the domain of any spline
			}
		}
	}
}
