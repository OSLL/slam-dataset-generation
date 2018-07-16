#ifndef PATHFINDING_MOTIONVALIDATOR_H
#define PATHFINDING_MOTIONVALIDATOR_H

#include "world/World.h"
#include <ompl/base/MotionValidator.h>

class MotionValidator : public ompl::base::MotionValidator {
	public:
		MotionValidator(const ompl::base::SpaceInformationPtr & si, World & world_ref);

		bool checkMotion(const ompl::base::State * s1, const ompl::base::State * s2) const;
	private:
		World & world;
};

#endif
