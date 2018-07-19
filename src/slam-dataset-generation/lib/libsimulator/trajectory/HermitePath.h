#ifndef TRAJECTORY_HERMITEPATH_H
#define TRAJECTORY_HERMITEPATH_H

#include <vector>
#include "trajectory/HermiteEdge.h"
#include "math/Pose.h"

class HermitePath {
	public:
		HermitePath(const std::vector<Pose> & intermediate_poses, const double & t_start_val = 0.0f);
		
		Pose operator()(double t) const;

		const double & getStartTime() const {return start_t;}
		const double & getEndTime() const {return end_t;}

		const Pose & getStartPose() const {return start_pose;}
		const Pose & getEndPose() const {return end_pose;}

	protected:
		void populateFromIntermediatePoses(const std::vector<Pose> & intermediate_poses);

		std::vector<HermiteEdge> edges;

		const double start_t;
		const double end_t;

		Pose start_pose;
		Pose end_pose;
};

#endif
