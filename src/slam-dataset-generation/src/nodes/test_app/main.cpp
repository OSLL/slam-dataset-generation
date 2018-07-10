#include <iostream>
#include <utility>
#include <vector>
#include <cstdlib>
#include "misc/misc.h"
#include "math/polynomial.h"

using namespace std;

enum class FAILURE_REASON {EMPTY_ROOTS, INCORRECT_ROOTS};

const char * reason(FAILURE_REASON r)
{
	switch (r)
	{
		case FAILURE_REASON::EMPTY_ROOTS:
			return "EMPTY_ROOTS";
		case FAILURE_REASON::INCORRECT_ROOTS:
			return "INCORRECT_ROOTS";
		default:
			return "UNKNOWN_REASON";
	}
}

int main(int argc, char ** argv) {

	const int number_of_iterations = 10000000;
	const double tolerance = 0.1;

	vector<pair<math::Polynomial<3>, FAILURE_REASON>> failures;
	
	double a, b, c, d;
	for (int i = 0; i < number_of_iterations; i++)
	{
		a = generate_random_number(-20, 20);
		b = generate_random_number(-20, 20);
		c = generate_random_number(-20, 20);
		d = generate_random_number(-20, 20);

		math::Polynomial<3> f(d, c, b, a);

		auto roots = f.roots();

		if (roots.empty())
		{
			failures.push_back(make_pair(f, FAILURE_REASON::EMPTY_ROOTS));
		}
		else
		{
			for (const double & root : roots)
			{
				double abs_f_root = abs(f(root));
				if (abs_f_root > tolerance)
				{
					failures.push_back(make_pair(f, FAILURE_REASON::INCORRECT_ROOTS));
				}
			}
		}
	}

	for (auto failure : failures)
	{
		cout << failure.first << " failed with " << reason(failure.second) << endl;
	}

	cout << "Failure rate: " << ((double)failures.size() * 100.0f / (double)number_of_iterations) << "%" << endl;
}
