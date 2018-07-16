#ifndef PATHFINDING_MOTIONVALIDATOR_H
#define PATHFINDING_MOTIONVALIDATOR_H

#include "world/World.h"
#include <ompl/base/MotionValidator.h>

class MotionValidator : public ompl::base::MotionValidator {
	private:
		World & world;
	public:
		MotionValidator(const ompl::base::SpaceInformationPtr & si, World & world_ref);

		bool checkMotion(const ompl::base::State * s1, const ompl::base::State * s2) const;
};

#endif
