#ifndef OBSERVATIONPATH_RAY_H
#define OBSERVATIONPATH_RAY_H

#include "observationpath/ObservationPath.h"

class Ray : public ObservationPath {
	public:
		Ray(const Vec & start_point, const double & theta_val);

		double theta;

		void change_theta(double dtheta);
		void change_end(const Vec & v);

		static bool on_ray(const Vec & p, const ObservationPath & op);
		void print(std::ostream & o = std::cout, int tabs = 0) const;
	private:
		void update_end();
		void update_theta();
		void update_abc();
};

#endif
