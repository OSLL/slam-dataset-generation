#include "structs/vec2d.h"

using std::ostream;

ostream & operator<<(ostream & o, Vec2D v) {
	printf("(%.2f, %.2f)", v.x, v.y);
	return o;
}
