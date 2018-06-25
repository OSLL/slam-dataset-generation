#include "pathfinding/statevaliditychecker.h"

StateValidityChecker::StateValidityChecker(World & world_ref) :
	world(world_ref)
{ }

bool StateValidityChecker::isValid(const ompl::base::State * s) const {
	//
}
