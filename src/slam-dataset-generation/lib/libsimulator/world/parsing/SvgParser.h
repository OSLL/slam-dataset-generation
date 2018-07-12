#ifndef WORLD_PARSING_SVGPARSER_H
#define WORLD_PARSING_SVGPARSER_H

#include "world/World.h"
#include "world/parsing/LengthFactory.h"
#include "world/parsing/SvgTransformHandler.h"
#include "world/parsing/SvgppForwardDeclarations.h"
#include <vector>

#include <boost/range/iterator_range.hpp>

class SvgParser
{
public:
	SvgParser(World & parent_obj);

	static void parse(const char * filename, World & world);

	/* ################## Document info ################## */
	void set_viewport(double x, double y, double width, double height);
	void set_viewbox_size(double width, double size);
	const LengthFactory & length_factory() {return length_factory_;};
	/* ################################################### */



	/* ################ Transform handling ############### */
	void transform_matrix(const SvgTransformHandler::Transform & t);
	void on_enter_element(const svgpp::tag::element::any &);
	/* ################################################### */


	
	/* ################# Edge detection ################## */
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
	/* ################################################### */


	
	/* ################# Path detection ################## */
	void set(const svgpp::tag::attribute::id &, const boost::iterator_range<const char *> & value);
	void path_move_to(double x, double y, const svgpp::tag::coordinate::absolute &);
	void on_exit_element();
	/* ################################################### */



	/* ################ Unused functions ################# */
	void disable_rendering()  { }
	void path_exit()	  { }
	void path_close_subpath() { }
	/* ################################################### */

	friend class LengthFactory;
private:
	// Reference to World parent
	World & world;

	// Length policy
	LengthFactory length_factory_;

	// Transform handling
	SvgTransformHandler transform_handler_;

	/* ################## Document info ################## */
	double canvas_width;
	double canvas_height;

	// Viewport
	Vec viewport_location;
	double viewport_width;
	double viewport_height;

	// Viewbox
	double viewbox_width;
	double viewbox_height;
	/* ################################################### */



	/* ################# Edge detection ################## */
	bool parsing_path;
	/* ################################################### */


	
	/* ################# Path detection ################## */
	EdgePath * current_path;
	/* ################################################### */
};

#endif
