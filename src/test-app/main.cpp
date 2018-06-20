#include "world/world.h"
#include <vector>
#include "misc/misc.h"
#include "misc/find_roots.h"

using namespace std;

int main(int argc, char ** argv) {
	
	// Quickly parse command line arguments
	if (argc != 2) {
		cout << "USAGE: test <in.svg>" << endl;
		return -1;
	}
	const char * source = argv[1];

	const int number_of_iterations = 100000;

	int failures = 0;
	for (int i = 0; i < number_of_iterations; i++) {
		// Generate random coefficients
		double a = generate_random_number(-10, 10);
		double b = generate_random_number(-10, 10);
		double c = generate_random_number(-10, 10);
		double d = generate_random_number(-10, 10);

		// See if find_roots could locate roots
		set<double> roots = find_roots(a, b, c, d);	
		if (roots.empty()) {
			failures++;
		}
	}

	// Show failure rate
	double failure_percentage = 100.0 * (double)failures / (double)number_of_iterations;
	cout << "Failure percentage = " << failure_percentage << endl;
}
