#ifndef SPLINEPATH_H
#define SPLINE_PATH

#include <vector>
#include "structs/vec.h"

// Encodes information for one spline
struct SplineData {
	// f(t) = at^3 + bt^2 + ct + d
	double a, b, c, d;

	// y(t) = et^3 + ft^2 + gt + h
	double e, f, g, h;

	// t must be in [t_min, t_max)
	double t_min, t_max;
};

class SplinePath {
	private:
		// Static information about the spline coefficients and t bounds
		SplineData * spline_data; // Responsible for pointing to heap-allocated spline data array
		const int number_of_splines;

		// State and function to keep track of which spline is currently being used (for efficiency)
		SplineData * current_spline;
		bool find_new_spline(double t);

		// Range for t values for the entire spline function
		double t_min;
		double t_max;

		// Small helper function that just computes the position
		static Vec evaluate_spline(SplineData * s, double t);

	public:
		SplinePath(std::vector<Vec> line_path);
		~SplinePath();
		Vec get_pos(double t);
};

#endif
