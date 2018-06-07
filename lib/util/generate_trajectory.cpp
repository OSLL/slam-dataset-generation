#include <vector>
#include "structs/vec2d.h"
#include "structs/path.h"
#include "structs/world.h"
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
 *    each critical point.  To do this, implement plan_path(World, Vec2D, Vec2D) which
 *    will make generation of the graph as simple as generating edges for each pair of nodes
 * 
 * 
 * 2. Generate a trajectory that passes through all of the critical points.  To do this,
 *    implement travelling_salesman(doesn't necessarily have to be optimal) on that
 *    edge-weighted graph.
 */

static Path plan_path(World world, Vec2D v1, Vec2D v2);
static Path travelling_salesman(Graph g);

Path generate_trajectory(const World & world, const vector<Vec2D> & critical_points) {

	// Construct graph
	Graph g;

	// Add an edge for each unique pair of critical points
	int size = critical_points.size();
	for (int i = 0; i < size; i++) {
		for (int j = i + 1; j  < size; j++) {
			g.add_edge(critical_points[i], critical_points[j]);
		}
	}

	return travelling_salesman(g);
}

// Returns a path connecting two points that is valid in the world provided
Path plan_path(World world, Vec2D v1, Vec2D v2) {
	// Not implemented
}

// Performs a travelling salesman solution on the edge-weighted graph of critical points
Path travelling_salesman(Graph g) {
	// Not implemented
}
