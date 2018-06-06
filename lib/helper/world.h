#ifndef WORLD_H
#define WORLD_H

#include <vector>
#include "path.h"

class World {
	private:
		double width;
		double height;

		Path world_boundary;
		std::vector<Path> obstacles;

	public:
		World();
		void populate_from_file(const char *);
};

#endif
