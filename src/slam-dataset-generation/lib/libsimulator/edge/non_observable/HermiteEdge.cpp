#include "edge/non_observable/HermiteEdge.h"

HermiteEdge::HermiteEdge(const Pose & start_pose, const Pose & end_pose)
	: HermiteEdge(
		  start_pose.pos,				  // p1
		  Vec::Polar(smoothing_factor, start_pose.theta), // m1
		  end_pose.pos,					  // p2
		  Vec::Polar(smoothing_factor, end_pose.theta)	  // m2
	  )
{ }

HermiteEdge::HermiteEdge(const Vec & p1, const Vec & m1, const Vec & p2, const Vec & m2)
	: PolynomialEdge<3>(
		   2*p1 +   m1 - 2*p2 + m2, // A
		  -3*p1 - 2*m1 + 3*p2 - m2, // B
		   m1,			    // C
		   p1			    // D
	  )
{ }
