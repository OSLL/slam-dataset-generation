#ifndef WORLD_H
#define WORLD_H

#include <vector>
#include "structs/path.h"

class World {
	private:

	public:
		double width;
		double height;

		Path world_boundary;
		std::vector<Path> obstacles;

		World();
		void read_from_disk(const char * source);
		void write_to_disk(const char * destination);

		static World generate_world();

};

#endif
