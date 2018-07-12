#ifndef STATEVALIDITYCHECKER_H
#define STATEVALIDITYCHECKER_H

#include "world/world.h"
#include <ompl/base/StateValidityChecker.h>

class StateValidityChecker : public ompl::base::StateValidityChecker {
	private:
		World & world;
	public:
		StateValidityChecker(const ompl::base::SpaceInformationPtr & si, World & world_ref);

		bool isValid(const ompl::base::State * s) const;
};

#endif
