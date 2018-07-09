#include <iostream>
#include "math/polynomial.h"

using namespace std;

int main(int argc, char ** argv) {

	math::Polynomial<3> f(5, 1, 1, 1);

	cout << f.roots().empty() << endl;

	for (const double & root : f.roots())
	{
		cout << "Root: " << root << endl;
	}
}
