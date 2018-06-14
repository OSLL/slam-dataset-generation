#ifndef WORLD_H
#define WORLD_H

#include <vector>
#include "world/path.h"

class World {
	private:
		double width;
		double height;

		Path * world_boundary;
		std::vector<Path *> interior_obstacles;
		std::vector<Path *> all_obstacles;
	public:

		World();
		~World();

		const Path * get_world_boundary();
		const std::vector<Path *> & get_obstacles();
		const std::vector<Path *> & get_all_obstacles();

		void read_from_disk(const char * source);
		void write_to_disk(const char * destination);

		static World generate_world();

		friend class ParsingContext;
};

#endif
