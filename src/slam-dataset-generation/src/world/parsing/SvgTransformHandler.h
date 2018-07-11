#ifndef WORLD_PARSING_SVGTRANSFORMHANDLER_H
#define WORLD_PARSING_SVGTRANSFORMHANDLER_H

#include "misc/vec.h"

class SvgTransformHolder
{
public:
	SvgTransformHolder();

	void enterElement();
	void exitElement();

	void receiveTransform();

	Vec operator()(const Vec & v);
private:
	int elements_deep;
};

#endif
