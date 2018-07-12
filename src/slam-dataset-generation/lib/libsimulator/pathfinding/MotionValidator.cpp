#include "pathfinding/MotionValidator.h"

MotionValidator::MotionValidator(const ompl::base::SpaceInformationPtr & si, World & world_ref) :
	ompl::base::MotionValidator(si),
	world(world_ref)
{ }

bool MotionValidator::checkMotion(const ompl::base::State * s1, const ompl::base::State * s2) const {
	return true;
}
