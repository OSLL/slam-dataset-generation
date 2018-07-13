#ifndef WORLD_H
#define WORLD_H

#include <vector>
#include <iostream>
#include <string>
#include "obstacle/Obstacle.h"
#include "observationpath/ObservationPath.h"

class World {
	private:
		double width;
		double height;

	public:

		Obstacle * world_boundary;
		std::vector<Obstacle *> interior_obstacles;
		std::vector<Obstacle *> all_obstacles;

		World();
		~World();

		const Obstacle * get_world_boundary() const;
		const std::vector<Obstacle *> & get_obstacles() const;
		const std::vector<Obstacle *> & get_all_obstacles() const;
		const Obstacle * get_obstacle_by_id(std::string id) const;

		void read_from_disk(const char * source);
		void write_to_disk(const char * destination) const;

		void print(std::ostream & o = std::cout, int tabs = 0) const;

		bool is_valid(const Vec & p) const;

		// Raytracing
		double distance(const ObservationPath & op) const;

		friend class ParsingContext;
};

std::ostream & operator<<(std::ostream & o, const World & world);

#endif
