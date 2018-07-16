#ifndef MATH_VEC_H
#define MATH_VEC_H

#include <iostream>

class Vec {
	private:
	public:
		// Constructors
		Vec(const double & x_val, const double & y_val);
		Vec(const Vec &);

		static Vec Polar(const double & r, const double & theta);

		double x;
		double y;

		// Angle
		double radians() const;
		double degrees() const;

		// Magnitude
		double mag() const;

		// Dot product
		double dot(const Vec & v) const;

		// Arithmetic
		Vec operator*(const double & scale) const;
		Vec operator/(const double & scale) const;
		Vec operator+(const Vec & v) const;
		Vec operator-(const Vec & v) const;
		Vec operator-() const; // Negation

		// Comparison
		bool operator==(const Vec & v) const;
		bool operator!=(const Vec & v) const;
		bool operator<(const Vec & v) const; // For ability to compile Vecs into a set
};

// Printing a vector
std::ostream & operator<<(std::ostream & o, Vec v);

// Reverse order scaling (cannot be member functions)
Vec operator*(const double & scale, const Vec & v);
Vec operator/(const double & scale, const Vec & v);

// Easier to read dot product
double dot(const Vec & v1, const Vec & v2);

// Null vector returned whenever a valid vector could not be found
extern const Vec i_hat;
extern const Vec j_hat;
extern const Vec null_vector;

#endif
