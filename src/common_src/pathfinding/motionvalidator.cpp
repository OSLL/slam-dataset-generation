#include "pathfinding/motionvalidator.h"

MotionValidator::MotionValidator(World & world_ref) :
	world(world_ref)
{ }

bool MotionValidator::checkMotion(const ompl::base::State * s1, const ompl::base::State * s2) const {
	//
}
