#include "world/parsing/SvgTransformHandler.h"
#include <iostream>

using std::cout;
using std::endl;

using std::ostream;

typedef SvgTransformHandler::Transform Transform;

static void operator*=(Transform & t1, const Transform & t2);
static Transform inverse(const Transform & t);
static ostream & operator<<(ostream & o, const Transform & m);

enum TransformationIndex
{
	a = 0,
	b = 1,
	c = 2,
	d = 3,
	e = 4,
	f = 5
};


SvgTransformHandler::SvgTransformHandler()
	: depth_(0)
	, current_transform_(Transform {1, 0, 0, 1, 0, 0}) // Identity transform
{ }

void SvgTransformHandler::setViewportHeight(const double & viewport_height_val)
{
	viewport_height_ = viewport_height_val;
}

void SvgTransformHandler::enterElement()
{
	++depth_;
}

void SvgTransformHandler::exitElement()
{
	if (depth_ == transform_depths_.back())
	{
		const Transform & expired_transform = transforms_.back();

		current_transform_ *= inverse(expired_transform);

		// Remove transforms
		transforms_.pop_back();
		transform_depths_.pop_back();
	}

	--depth_;
}

void SvgTransformHandler::receiveTransform(Transform transform)
{
	current_transform_ *= transform;

	transforms_.push_back(std::move(transform));
	transform_depths_.push_back(depth_);
}

Vec SvgTransformHandler::operator()(const Vec & v)
{
	// Create succinct reference for transformation matrix
	const Transform & t = current_transform_;

	// Transform vector relative to current  viewport
	Vec result {t[a]*v.x + t[c]*v.y + t[e], t[b]*v.x + t[d]*v.y + t[f]};

	// Flip y coordinate so that the axis system is like a traditional cartesian coordinate system
	result.y = viewport_height_ - result.y;

	return result;
}


/* ============================ Helper functions  ============================ */
void operator*=(Transform & t1, const Transform & t2)
{
	t1[a] = t1[a]*t2[a] + t1[c]*t2[b];	   // a = a1*a2 + c1*b2
	t1[b] = t1[b]*t2[a] + t1[d]*t2[b];	   // b = b1*a2 + d1*b2
	t1[c] = t1[a]*t2[c] + t1[c]*t2[d];	   // c = a1*c2 + c1*d2
	t1[d] = t1[b]*t2[c] + t1[d]*t2[d];	   // d = b1*c2 + d1*d2
	t1[e] = t1[a]*t2[e] + t1[c]*t2[f] + t1[e]; // e = a1*e2 + c1*f2 + e1
	t1[f] = t1[b]*t2[e] + t1[d]*t2[f] + t1[f]; // f = b1*e2 + d1*f2 + f1
}

Transform inverse(const Transform & t)
{
	const double det = t[a]*t[d] - t[b]*t[c];

	Transform i
	{
		 t[d] / det,
		-t[b] / det,
		-t[c] / det,
		 t[a] / det,
		(t[f]*t[c] - t[d]*t[e]) / det,
		(t[b]*t[e] - t[a]*t[f]) / det
	};

	return i;
}

ostream & operator<<(ostream & o, const Transform & m) {
	printf(
		"\n"
		"[%f, %f, %f]\n"
		"[%f, %f, %f]\n"
		"[%f, %f, %f]\n",
		m[0], m[2], m[4],
		m[1], m[3], m[5],
		0.0f, 0.0f, 1.0f
	);
	return o;
}
/* =========================================================================== */
