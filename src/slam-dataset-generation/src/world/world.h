#ifndef WORLD_H
#define WORLD_H

#include <vector>
#include <iostream>
#include <string>
#include "world/edgepath.h"
#include "observationpath/observationpath.h"

class World {
	private:
		double width;
		double height;

	public:

		EdgePath * world_boundary;
		std::vector<EdgePath *> interior_obstacles;
		std::vector<EdgePath *> all_obstacles;

		World();
		~World();

		const EdgePath * get_world_boundary() const;
		const std::vector<EdgePath *> & get_obstacles() const;
		const std::vector<EdgePath *> & get_all_obstacles() const;
		const EdgePath * get_obstacle_by_id(std::string id) const;

		void read_from_disk(const char * source);
		void write_to_disk(const char * destination) const;

		void print(std::ostream & o = std::cout, int tabs = 0) const;

		static World generate_world();

		bool is_valid(const Vec & p) const;

		// Raytracing
		double distance(const ObservationPath & op) const;

		friend class ParsingContext;
};

std::ostream & operator<<(std::ostream & o, const World & world);

#endif
