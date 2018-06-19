#include <iostream>
#include <vector>
#include <cmath>
#include "misc/vec.h"
#include "misc/line.h"
#include "world/cubicbezieredge.h"
#include "world/linearedge.h"
#include "world/world.h"

using namespace std;

ostream & operator<< (ostream & o, const std::set<Vec> & s) {
	if (!s.empty()) {
		for (const Vec & v : s) {
			o << v << endl;
		}
	} else {
		o << "Set is empty" << endl;
	}
	return o;
}

int main(int argc, char ** argv) {
	
	// Quickly parse command line arguments
	if (argc != 2) {
		cout << "USAGE: test <in.svg>" << endl;
		return -1;
	}
	const char * source = argv[1];

	Vec start {0, 0};
	Vec end {100, 100};

	LinearEdge le(start, end);
	CubicBezierEdge cbe(start, start, end, end);

	Vec line_start {50, 50};
	Vec line_end = line_start + Vec {0, 1};

	Line l {line_start, line_end};
	
	//cout << le.intersection_points(l);
	cout << cbe.intersection_points(l);
}
