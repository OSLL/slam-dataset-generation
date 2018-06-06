#ifndef PATH_H
#define PATH_H

#include <vector>
#include <vec2d.h>

class Path {
	private:
		bool isWorldBoundary;
	public:
		Path();
		std::vector<Vec2D> vertices;
		void populate_from_svg_data(const char *);
		bool is_world_boundary();
};

#endif
