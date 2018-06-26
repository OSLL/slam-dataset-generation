#ifndef WORLD_H
#define WORLD_H

#include <vector>
#include <iostream>
#include <string>
#include "world/edgepath.h"

class World {
	private:
		double width;
		double height;

		EdgePath * world_boundary;
		std::vector<EdgePath *> interior_obstacles;
		std::vector<EdgePath *> all_obstacles;
	public:

		World();
		~World();

		const EdgePath * get_world_boundary();
		const std::vector<EdgePath *> & get_obstacles();
		const std::vector<EdgePath *> & get_all_obstacles();
		const EdgePath * get_obstacle_by_id(std::string id);

		void read_from_disk(const char * source);
		void write_to_disk(const char * destination);

		void print(std::ostream & o = std::cout, int tabs = 0) const;

		static World generate_world();

		bool is_valid(const Vec & p);

		friend class ParsingContext;
};

std::ostream & operator<<(std::ostream & o, const World & world);

#endif
