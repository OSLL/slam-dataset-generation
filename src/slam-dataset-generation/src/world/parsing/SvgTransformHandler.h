#ifndef WORLD_PARSING_SVGTRANSFORMHANDLER_H
#define WORLD_PARSING_SVGTRANSFORMHANDLER_H

#include "misc/vec.h"
#include <boost/array.hpp>
#include <vector>

class SvgParser;

class SvgTransformHandler
{
public:
	SvgTransformHandler();

	typedef boost::array<double, 6> Transform;

	void enterElement();
	void exitElement();

	void receiveTransform(Transform transform);

	void setViewportHeight(const double & viewport_height_val);

	Vec operator()(const Vec & v);
private:
	int depth_;

	double viewport_height_;

	Transform current_transform_;

	std::vector<Transform> transforms_;
	std::vector<int> transform_depths_;

};

#endif
