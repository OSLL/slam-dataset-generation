#include <vector>
#include "misc/vec.h"
#include "world/path.h"
#include "world/world.h"
#include "structs/graph.h"

using std::vector;

/* Generating a trajectory:
 * 
 * The function generate_trajectory should take in a world and a list of critical points
 * and should return a valid trajectory that will pass through all of the critical points.
 * 
 * This problem can be broken down into two distinct steps
 * 
 * 1. Generate a complete edge-weighted graph representing planned paths between each of
 *    each critical point.  To do this, implement plan_path(World, Vec, Vec) which
 *    will make generation of the graph as simple as generating edges for each pair of nodes
 * 
 * 
 * 2. Generate a trajectory that passes through all of the critical points.  To do this,
 *    implement travelling_salesman (contained in util/travelling_salesman.cpp) on that
 *    edge-weighted graph.
 */

Path travelling_salesman(const Graph & g);

// Returns a path connecting two points that is valid in the world provided
static Path plan_path(const World & world, const Vec & v1, const Vec & v2) {
	// Not implemented
}

Path generate_trajectory(const World & world, const vector<Vec> & critical_points) {

	// Construct graph
	Graph g;

	// Add an edge for each unique pair of critical points
	int size = critical_points.size();
	for (int i = 0; i < size; i++) {
		for (int j = i + 1; j  < size; j++) {
			Path new_edge = plan_path(world, critical_points[i], critical_points[j]);
			g.add_edge(new_edge);
		}
	}

	// Compute and return trajectory
	return travelling_salesman(g);
}
