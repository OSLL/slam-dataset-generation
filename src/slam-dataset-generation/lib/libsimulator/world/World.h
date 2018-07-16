#ifndef WORLD_WORLD_H
#define WORLD_WORLD_H

#include <vector>
#include <iostream>
#include <string>
#include <memory>
#include "obstacle/Obstacle.h"
#include "observationpath/ObservationPath.h"

#include "trajectory/Trajectory.h"

class World {
	private:
		double width;
		double height;

		std::unique_ptr<Obstacle> world_boundary;
		std::vector<std::unique_ptr<Obstacle>> obstacles;
	public:
		World();

		const std::unique_ptr<Obstacle> & getWorldBoundary() const {return world_boundary;}
		const std::vector<std::unique_ptr<Obstacle>> & getObstacles() const {return obstacles;}

		void addObstacle(std::unique_ptr<Obstacle> obstacle);
		std::unique_ptr<Obstacle> extractLinearTrajectory();

		void read_from_disk(const char * source);

		bool is_valid(const Vec & p) const;

		double distance(const ObservationPath & op) const;

		void print(std::ostream & o = std::cout, int tabs = 0) const;

		friend class ParsingContext;
};

std::ostream & operator<<(std::ostream & o, const World & world);

#endif
