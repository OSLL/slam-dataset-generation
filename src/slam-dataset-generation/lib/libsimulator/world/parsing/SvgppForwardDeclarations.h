#ifndef WORLD_PARSING_SVGPPFORWARDDECLARATIONS_H
#define WORLD_PARSING_SVGPPFORWARDDECLARATIONS_H

namespace svgpp
{
	namespace tag
	{
		namespace length_units
		{
			struct em;
			struct ex;
			struct px;
			struct in;
			struct cm;
			struct mm;
			struct pt;
			struct pc;
			struct percent;
			struct none;
		}

		namespace length_dimension
		{
			struct absolute;
		}

		namespace length_dimension
		{
			struct width;
			struct height;
			struct not_width_nor_height;
		}

		namespace coordinate
		{
			struct absolute;
		}

		namespace element
		{
			struct any;
			struct path;
		}

		namespace attribute
		{
			struct id;
		}
	}
}

#endif
