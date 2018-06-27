#include "pathfinding/statevaliditychecker.h"

StateValidityChecker::StateValidityChecker(const ompl::base::SpaceInformationPtr & si, World & world_ref) :
	ompl::base::StateValidityChecker(si),
	world(world_ref)
{ }

bool StateValidityChecker::isValid(const ompl::base::State * s) const {
	//
}
