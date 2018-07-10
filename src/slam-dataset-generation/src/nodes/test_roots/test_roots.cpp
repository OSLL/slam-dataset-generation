#include "test_roots.h"
#include <iostream>
#include <utility>
#include <vector>
#include <memory>
#include <cstdlib>
#include "misc/misc.h"
#include "math/polynomial.h"

using namespace std;
using namespace math;

struct FailureReason
{
	virtual void print() = 0;
};

struct EmptyRoots : FailureReason
{
	void print()
	{
		cout << "\tEmpty roots" << endl;
	}
};

struct IncorrectRoots : FailureReason
{
	vector<pair<double, double>> points;
	void print()
	{
		cout << "\tIncorrect roots" << endl;
		for (auto point : points)
		{
			cout << "\t\t(" << point.first << ", " << point.second << ")" << endl;
		}
	}
};

struct Failure
{
	Failure(Polynomial<3> function) : f(function) {}

	Polynomial<3> f;
	vector<shared_ptr<FailureReason>> failure_reasons;

	void print()
	{
		cout << f << " failed by:" << endl;
		for (auto reason : failure_reasons)
			reason->print();
	}
};


void test_roots(const int number_of_iterations) {

	const double tolerance = 0.1;

	vector<Failure> failures;
	
	double a, b, c, d;
	for (int i = 0; i < number_of_iterations; i++)
	{
		a = generate_random_number(-20, 20);
		b = generate_random_number(-20, 20);
		c = generate_random_number(-20, 20);
		d = generate_random_number(-20, 20);

		math::Polynomial<3> f(d, c, b, a);

		auto roots = f.roots();

		bool roots_empty = roots.empty();

		bool incorrect_root = false;
		vector<pair<double, double>> points;
		for (auto root : roots)
		{
			double f_root = f(root);
			double abs_f_root = abs(f_root);
			if (abs_f_root > tolerance)
			{
				incorrect_root = true;
				points.push_back(make_pair(root, f_root));
			}
		}
		

		if (roots_empty || incorrect_root)
		{
			Failure failure(std::move(f));
			if (roots_empty)
			{
				auto ptr = make_shared<EmptyRoots>();
				failure.failure_reasons.push_back(std::move(ptr));
			}

			if (incorrect_root)
			{
				auto ptr = make_shared<IncorrectRoots>();
				swap(points, ptr->points);
				failure.failure_reasons.push_back(std::move(ptr));
			}
			failures.push_back(std::move(failure));
		}
	}

	for (auto failure : failures)
	{
		failure.print();
	}

	cout << "Failure rate: " << ((double)failures.size() * 100.0f / (double)number_of_iterations) << "%" << endl;
}
