#ifndef OBSTACLE_OBSTACLE_H
#define OBSTACLE_OBSTACLE_H

#include "obstacle/ObstacleEdge.h"
#include "observationpath/ObservationPath.h"
#include <vector>
#include <iostream>

class Obstacle {
	private:
		const Vec * end_ptr;
	public:
		Obstacle(const Vec & start_point);
		~Obstacle();

		const Vec start;
		std::string id;

		const Vec & end();


		std::vector<ObstacleEdge *> edges;

		void add_edge(ObstacleEdge * e);
		void print(std::ostream & o = std::cout, int tabs = 0) const;

		// Raytracing
		bool is_in(const Vec & p);
		double distance(const ObservationPath & op) const;
};

std::ostream & operator<<(std::ostream & o, const Obstacle & path);

#endif
