#ifndef OBSTACLE_OBSTACLE_H
#define OBSTACLE_OBSTACLE_H

#include "obstacle/ObstacleEdge.h"
#include "observationpath/ObservationPath.h"
#include <vector>
#include <string>
#include <memory>
#include <iostream>

class Obstacle {
	private:
		std::string id;

		const Vec * end_ptr;
	public:
		Obstacle(const Vec & start_point);

		const Vec start;

		const Vec & end();
		
		void setId(std::string id_val) { id = std::move(id_val);}

		std::vector<std::unique_ptr<ObstacleEdge>> edges;

		void add_edge(std::unique_ptr<ObstacleEdge> e);
		void print(std::ostream & o = std::cout, int tabs = 0) const;

		// Raytracing
		bool is_in(const Vec & p);
		double distance(const ObservationPath & op) const;
};

std::ostream & operator<<(std::ostream & o, const Obstacle & path);

#endif
