#include "structs/splinepath.h"
#include <vector>
#include <iostream>
#include <cstdlib>
#include <cmath>

using std::cout;
using std::endl
using std::vector;

SplineData generate_spline_data(Vec v1, Vec v2, double m1, double m2);

SplinePath::SplinePath(vector<Vec> line_path) :
	number_of_intervals(line_path.size() - 1),
	spline_data(new SplineData[number_of_splines]),
	current_spline(spline_data) // Assume first query will be to t=0
{
	if (line_path.size() < 2) {
		cout << "SplinePath was supplied line path with the insufficient vertices." << endl;
		exit(-1);
	}

	// Perform interpolation for x
}

~SplinePath::SplinePath() {
	delete[] spline_data;
}

bool SplinePath::find_new_spline(double t) {
	// The splines are sorted by domain, so a binary search makes sense.

	int l = 0;
	int r = number_of_splines - 1;
	
	bool found = false;
	int iterations = 0;
	while (!found && iterations < 25) {
		SplineData guess = spline_data + (r + l) / 2;
		
		if (t < guess->t_min) {
			// t is below the bounds of the guess, so the correct spline must be in the lower half
			r = guess - 1;
		} else if (t > guess->t_max) {
			// t is below the bounds of the guess, so the correct spline must be in the upper half
			l = guess + 1;
		} else {
			// t is between the bounds of the guess, so the current guess is the correct spline
			current_spline = guess;
			return true;
		}
		iterations++;
	}
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
	} else if ( current_spline != spline_data + number_of_splines &&
		    t >= (current_spline+1)->t_min && t < (current_spline+1)->t_max ) {
		// t is valid for the next spline
		current_spline++;
		return SplinePath::evaluate_spline(current_spline, t);
	} else if (t < t_min || t > t_max) {
		// t is not valid for this SplinePath
		cout << "T supplied to SplinePath did not fit in valid domain." << endl;
	} else {
		if (find_new_spline()) {
			return SplinePath::evaluate_spline(current_spline, t);
		} else {
			cout << "No spline could be found for t = " << t << endl;
		}
	}
}

SplineData generate_spline_data(Vec v1, Vec v2, double m1, double m2) {
	//
}
