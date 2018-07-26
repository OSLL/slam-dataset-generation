#ifndef WORLD_PARSING_SVGPARSER_H
#define WORLD_PARSING_SVGPARSER_H

#include <vector>
#include <utility>
#include <string>
#include <memory>
#include <boost/range/iterator_range.hpp>
#include <boost/array.hpp>

#include "world/parsing/SvgppForwardDeclarations.h"

// Forward declaration instead of providing full types to separate compile time dependencies
class Vec;
class World;
class Obstacle;
class Trajectory;

class LengthFactory;
class SvgTransformHandler;

class SvgParser
{
public:
	SvgParser(World & parent_obj);
	~SvgParser();

	// See world/parsing/SvgParser_parse.cpp for implementation of SvgParser::parse(const char *, World &)
	//
	// It's segregated into its own translation unit because it brings in two heavy compile-time dependencies:
	// 	- Svgpp
	// 	- RapidXML
	// These are heavily templated libraries and significantly increase compilation time.
	//
	// I had entertained segregating the functionality from the parsing context entirely so that
	// it doesn't recompile when this header file is updated, but that would involve creating a
	// intermediary class that forwards methods to this class and I figured it wasn't worth it.
	static void parse(const char * filename, World & world);

	/* ==================================== Document info ==================================== */
	void set_viewport(double x, double y, double width, double height);
	void set_viewbox_size(double width, double size);
	const LengthFactory & length_factory();
	/* ======================================================================================= */



	/* ================================== Transform handling ================================= */
	void transform_matrix(const boost::array<double, 6> & t);
	void on_enter_element(const svgpp::tag::element::any &);
	void on_exit_element();
	/* ======================================================================================= */



	/* =================================== Path detection ==================================== */
	void set(const svgpp::tag::attribute::id &, const boost::iterator_range<const char *> & value);
	void path_move_to(double x, double y, const svgpp::tag::coordinate::absolute &);
	void path_exit();
	/* ======================================================================================= */



	/* ================================== Edge detection ===================================== */
	void path_line_to(double x, double y, const svgpp::tag::coordinate::absolute &);
	void path_cubic_bezier_to(double x1, double y1,
				  double x2, double y2,
				  double x, double y,
				  const svgpp::tag::coordinate::absolute &);
	void path_quadratic_bezier_to(double x1, double y1,
				      double x, double y,
				      const svgpp::tag::coordinate::absolute &);
	void path_elliptical_arc_to(double rx, double ry, double x_axis_rotation,
				    bool large_arc_flag, bool sweep_flag,
				    double x, double y,
				    const svgpp::tag::coordinate::absolute &);
	/* ======================================================================================= */



	/* ======================== Unused functions (required by svgpp) ========================= */
	void disable_rendering() {}
	void path_close_subpath() {}
	/* ======================================================================================= */
private:
	// Reference to World parent
	World & world;


	/* ==================================== Document info ==================================== */
	// Viewport
	double viewport_width;
	double viewport_height;

	// Viewbox
	double viewbox_width;
	double viewbox_height;

	// Length policy
	std::unique_ptr<LengthFactory> length_factory_;
	/* ======================================================================================= */



	/* ================================== Transform handling ================================= */
	std::unique_ptr<SvgTransformHandler> transform_handler_;
	/* ======================================================================================= */


	
	/* =================================== Path detection ==================================== */
	std::unique_ptr<Obstacle> obstacle_;
	std::vector<Vec> trajectory_intermediate_points_;
	std::string id_;
	/* ======================================================================================= */



	/* ================================== Edge detection ===================================== */
	// Edges can either be constructed as part of a trajectory (e.g. HermiteEdge) or as part of an obstacle (e.g. LinearEdge)
	int edge_type_;
	enum
	{
		OBSTACLE_EDGE,
		TRAJECTORY_EDGE
	};
	/* ======================================================================================= */



	/* ================================= Trajectory handling ================================= */
	// Whenever a trajectory is finished building, it gets placed into a vector.
	//
	// After all the paths are assigned, we iterate through them and attempt to assign each to their
	// respective obstacle (or, if it's the robot_trajectory, to the robot_trajectory_ pointer).
	//
	// We save this for last because the trajectory might be associated with a path that hasn't been constructed yet.
	//
	// This post-parsing association is done by SvgParser::associateTrajectories()
	std::vector<
		std::pair<
			std::string,
			std::vector<Vec>
		>
	> trajectory_init_param_lists_;

	void associateTrajectories();
	std::unique_ptr<Trajectory> constructTrajectory(const std::vector<Vec> & intermediate_points);
	/* ======================================================================================= */
};

#endif
