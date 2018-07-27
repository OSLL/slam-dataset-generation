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
	public:
		World();

		const std::unique_ptr<Obstacle> & getWorldBoundary() const {return obstacles[0];}
		const std::vector<std::unique_ptr<Obstacle>> & getObstacles() const {return obstacles;}

		void addObstacle(std::unique_ptr<Obstacle> obstacle);
		std::vector<std::unique_ptr<Obstacle>>::iterator findObstacle(const std::string & requested_id);

		const Trajectory & getRobotTrajectory() const;
		void setRobotTrajectory(std::unique_ptr<Trajectory> robot_trajectory_val);

		void read_from_disk(const char * source);

		bool is_valid(const Vec & p) const;

		double distance(const double & t, const ObservationPath & op) const;

		void print(std::ostream & o = std::cout, int tabs = 0) const;

		friend class SvgParser;
	private:
		double width;
		double height;

		std::vector<std::unique_ptr<Obstacle>> obstacles;
		std::unique_ptr<Trajectory> robot_trajectory_;
};

std::ostream & operator<<(std::ostream & o, const World & world);

#endif
