#ifndef PATHFINDING_STATEVALIDITYCHECKER_H
#define PATHFINDING_STATEVALIDITYCHECKER_H

#include "world/World.h"
#include <ompl/base/StateValidityChecker.h>

class StateValidityChecker : public ompl::base::StateValidityChecker {
	private:
		World & world;
	public:
		StateValidityChecker(const ompl::base::SpaceInformationPtr & si, World & world_ref);

		bool isValid(const ompl::base::State * s) const;
};

#endif
