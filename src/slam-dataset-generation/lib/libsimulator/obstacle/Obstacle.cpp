#include "obstacle/Obstacle.h"
#include "observationpath/Ray.h"
#include <iostream>
#include <string>

using std::ostream;
using std::cout;
using std::endl;
using std::string;
using std::unique_ptr;

Obstacle::Obstacle(const Vec & start_point) :
	start(start_point),
	end_ptr(&start)
{ }


void Obstacle::add_edge(unique_ptr<ObstacleEdge> edge) {
	edges.push_back(std::move(edge));
	end_ptr = &(edges.back()->getEnd());
}

void Obstacle::print(ostream & o, int tabs) const {
	// Print the correct number of tabs
	for (int i = 0; i < tabs; i++) {
		o << '\t';
	}

	// Print data
	o << "Obstacle: " << id << endl;
	for (const auto & edge : edges) {
		edge->print(o, tabs + 1);
		o << endl;
	}
}

bool Obstacle::is_in(const Vec & p) {
	// Cast ray in some direction and count the total number of intersections
	Ray ray {p, 0};

	int intersections = 0;
	for (const auto & edge : edges) {
		intersections += edge->number_of_intersections(ray);
	}

	// If number of intersections the ray encountered is odd, then the point is inside the path
	return intersections % 2 == 1;
}

double Obstacle::distance(const ObservationPath & op) const {
	
	double closest_distance = -1;

	for (const auto & edge : edges) {

		double distance_to_edge = edge->distance(op);

		if (distance_to_edge != -1) {
			if (distance_to_edge < closest_distance || closest_distance == -1) {
				closest_distance = distance_to_edge;
			}
		}
	}

	return closest_distance;
}

ostream & operator<<(ostream & o, const Obstacle & path) {
	path.print();
	return o;
}
