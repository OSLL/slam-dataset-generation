#include "world/world.h"
#include "pathfinding/find_trajectory.h"
#include "draw_world.h"

using namespace std;

int main(int argc, char ** argv) {
	
	// Quickly parse command line arguments
	if (argc != 2) {
		cout << "USAGE: test <in.svg>" << endl;
		return -1;
	}

	const char * source = argv[1];

	World world;
	world.read_from_disk(source);

	Trajectory trajectory = find_trajectory(world, {});

	draw_world_and_trajectory(world, trajectory, "map.png");
}
