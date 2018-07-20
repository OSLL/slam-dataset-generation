#include "trajectory/HermiteEdge.h"

#include <iostream>
#include <cassert>

using std::cout;
using std::endl;
using std::ostream;

const double HermiteEdge::smoothing_factor = 0.2f;

HermiteEdge::HermiteEdge(const Pose & start_pose, const Pose & end_pose)
	: HermiteEdge(
		  start_pose.pos,				  // p1
		  Vec::Polar(smoothing_factor, start_pose.theta), // m1
		  end_pose.pos,					  // p2
		  Vec::Polar(smoothing_factor, end_pose.theta)	  // m2
	  )
{ }

void HermiteEdge::print(ostream & o, int tabs) const
{
	// Print the right number of tabs
	for (int i = 0; i < tabs; i++)
		o << '\t';
	
	o << "HermiteEdge: ";
	printVectorPolynomial(o);
}

HermiteEdge::HermiteEdge(const Vec & p1, const Vec & m1, const Vec & p2, const Vec & m2)
	: PolynomialEdge<3>(
		   2*p1 +   m1 - 2*p2 + m2, // A
		  -3*p1 - 2*m1 + 3*p2 - m2, // B
		   m1,			    // C
		   p1			    // D
	  )
{
	double t = 1.0f;
	Vec v = (*this).derivative(1.0f);
	cout << "v(" << t << ") = " << v << " == " << m2 << "?" << endl;
	//assert(v == m2);
}
