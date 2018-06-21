#ifndef PARSINGCONTEXT_H
#define PARSINGCONTEXT_H

#include "world/world.h"
#include "world/edgepath.h"
#include <svgpp/svgpp.hpp>

class ParsingContext {
	private:
		// Reference to World parent
		World & parent;
		
		// EdgePath being currently constructed
		EdgePath * current_path;

		// A small bit of state to tell when ids are associated with paths vs non-paths
		bool parsing_path;

		boost::array<double, 6> transformation_matrix;
		Vec transform(const Vec & v);
	public:
		ParsingContext(World & parent_obj);

		// Parse member function
		void parse(char * buffer);

		// Process id
		void set(svgpp::tag::attribute::id, const boost::iterator_range<const char *> & value);

		// Delineate the start and end of paths
		void path_move_to(double x, double y, svgpp::tag::coordinate::absolute);
		void on_exit_element();

		// Update transformation matrix
		void transform_matrix(const boost::array<double, 6> & matrix);

		// Add edges
		void path_line_to(double x, double y, svgpp::tag::coordinate::absolute);
		void path_cubic_bezier_to(double x1, double y1,
					  double x2, double y2,
					  double x, double y,
					  svgpp::tag::coordinate::absolute);
		void path_quadratic_bezier_to(double x1, double y1,
					      double x, double y,
					      svgpp::tag::coordinate::absolute);
		void path_elliptical_arc_to(double rx, double ry, double x_axis_rotation,
					    bool large_arc_flag, bool sweep_flag,
					    double x, double y,
					    svgpp::tag::coordinate::absolute);

		// Required for svgpp, but not used
		void on_enter_element(svgpp::tag::element::any);
		void path_exit();
		void path_close_subpath();
};

#endif
