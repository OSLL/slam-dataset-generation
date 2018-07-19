#include "world/World.h"
#include "simulation/Robot.h"
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

	//Trajectory trajectory = find_trajectory(world, {});

	Vec P1 {0, 0};
	Vec M1 {0, 1};
	Vec P2 {1, 1};
	Vec M2 {1, 0};

	HermiteEdge f {P1, M1, P2, M2};

	cout << f << endl;
}
