#ifndef OBSTACLE_OBSTACLE_H
#define OBSTACLE_OBSTACLE_H

#include "obstacle/ObstacleEdge.h"
#include "observationpath/ObservationPath.h"
#include "trajectory/Trajectory.h"

#include <vector>
#include <string>
#include <memory>
#include <iostream>

class Obstacle {
	public:
		Obstacle(const Vec & start_point);

		const Vec & getStart() const {return start;}
		const Vec & getEnd() const {return *end_ptr;}
		const std::string & getId() const {return id;}
		const std::vector<std::unique_ptr<ObstacleEdge>> & getEdges() const {return edges;}

		void setId(std::string id_val);
		void setTrajectory(std::unique_ptr<Trajectory> trajectory);

		void add_edge(std::unique_ptr<ObstacleEdge> e);
		void print(std::ostream & o = std::cout, int tabs = 0) const;

		// Raytracing
		bool is_in(const Vec & p);
		double distance(const double & t, const ObservationPath & op) const;
	private:
		std::string id;

		const Vec start;
		const Vec * end_ptr;

		std::unique_ptr<Trajectory> obstacle_trajectory;

		std::vector<std::unique_ptr<ObstacleEdge>> edges;
};

std::ostream & operator<<(std::ostream & o, const Obstacle & path);

#endif
