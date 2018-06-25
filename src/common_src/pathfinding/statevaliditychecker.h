#ifndef STATEVALIDITYCHECKER_H
#define STATEVALIDITYCHECKER_H

#include "world/world.h"

class StateValidityChecker : public ompl::base::StateValidityChecker {
	private:
		World & world;
	public:
		StateValidityChecker(World & world_ref);

		bool isValid(const ompl::base::State * s) const;
};

#endif
