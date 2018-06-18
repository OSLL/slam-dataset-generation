#ifndef RAY_H
#define RAY_H

#include "misc/observationpath.h"

class Ray : public ObservationPath {
	private:
		void update_end();
		void update_theta();
	public:
		Ray(const Vec & start_point, const double & theta_val);

		double theta;

		void change_theta(double dtheta);
		static bool on_ray(const Vec & p, const ObservationPath & op);
		void print(std::ostream & o = std::cout, int tabs = 0) const;
};

#endif
