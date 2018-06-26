#include "world/world.h"
#include <vector>
#include "misc/misc.h"
#include "misc/find_roots.h"

using namespace std;

vector<Vec> trajectory {
	{1.29215882, 1.27719232},
	{2.19018437, 1.19736775},
	{3.21792473, 1.18738978},
	{3.96129038, 1.39193991},
	{4.20575294, 2.17022887},
	{4.24067596, 2.99840793},
	{3.87647668, 3.67691609},
	{3.00838547, 3.87647738},
	{2.10038181, 3.95131283},
	{1.34204913, 3.68190522},
	{1.07763052, 3.20794719},
	{0.89802539, 2.54440614},
	{0.95290474, 1.92576631}
};

int main(int argc, char ** argv) {
	
	// Quickly parse command line arguments
	if (argc != 2) {
		cout << "USAGE: test <in.svg>" << endl;
		return -1;
	}
	const char * source = argv[1];

	World world;
	world.read_from_disk(source);

	for (const Vec & p : trajectory) {
		bool is_valid = world.is_valid(p);
		cout << p << " is " << (is_valid? "valid" : "not valid") << endl;
	}
}
