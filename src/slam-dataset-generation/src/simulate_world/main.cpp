#include "world/world.h"
#include "simulation/robot.h"
#include "pathfinding/find_trajectory.h"

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

	Robot robot(world, trajectory);
	robot.simulate("data.bag");
}
