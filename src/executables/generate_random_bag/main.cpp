#include <iostream>
#include <vector>
#include "world/world.h"
#include "misc/vec2d.h"
#include "world/path.h"

using namespace std;

vector<Vec> generate_critical_points(const World & world);
Path generate_trajectory(const World & world, const vector<Vec> & critical_points);
void simulate_trajectory(const World & world, const Path & trajectory, const char * destination);

int main(int argc, char ** argv) {
	
	// Quickly parse command line arguments
	if (argc != 2) {
		cout << "USAGE: simulate <out.bag>" << endl;
		return -1;
	}
	const char * destination = argv[1];

	/* STEP 1: Generate world */
	// World world = World::generate_world();

	/* STEP 2: Generate critical points */
	//vector<Vec2D> critical_points = generate_critical_points(world);

	/* STEP 3: Generate trajectory */
	//Path trajectory = generate_trajectory(world, critical_points);

	/* STEP 4: Simulate trajectory, construct bag file, and write to disk */
	//simulate_trajectory(world, trajectory, destination);
}