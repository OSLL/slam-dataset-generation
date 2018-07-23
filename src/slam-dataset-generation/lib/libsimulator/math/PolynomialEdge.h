#ifndef MATH_POLYNOMIALEDGE_H
#define MATH_POLYNOMIALEDGE_H

#include "math/UnitParametricEdge.h"
#include "math/Polynomial.h"

template <int degree>
class PolynomialEdge : public UnitParametricEdge
{
public:
	template <typename ... Args>
	PolynomialEdge(Args ... args);

	virtual ~PolynomialEdge() = default;

	Vec operator()(double t) const;
	Vec derivative(double t) const;

	virtual void print(std::ostream & o, int tabs = 0) const;
	void printVectorPolynomial(std::ostream & o = std::cout) const;

protected:

	Polynomial<degree> x_;

	Polynomial<degree> y_;
};


/* ========================= Constructor ========================= */
template <int degree>
template <typename ... Args>
PolynomialEdge<degree>::PolynomialEdge(Args ... args)
	: x_(Polynomial<degree>(args.x ...))
	, y_(Polynomial<degree>(args.y ...))
{ }
/* =============================================================== */



/* ========================= Constructor ========================= */
template <int degree>
Vec PolynomialEdge<degree>::operator()(double t) const
{
	return {x_(t), y_(t)};
}

template <int degree>
Vec PolynomialEdge<degree>::derivative(double t) const
{
	return {x_.derivative(t), y_.derivative(t)};
}
/* =============================================================== */



/* ========================= Constructor ========================= */
template <int degree>
void PolynomialEdge<degree>::print(std::ostream & o, int tabs) const
{
	// Print correct number of tabs
	for (int i = 0; i < tabs; i++)
		o << '\t';
	
	o << "PolynomialEdge<" << degree << ">: ";

	printVectorPolynomial(o);
}

template <int degree>
void PolynomialEdge<degree>::printVectorPolynomial(std::ostream & o) const
{
	const auto & x_coefficients = x_.getCoefficients();
	const auto & y_coefficients = y_.getCoefficients();

	for (int i = degree; i >= 0; i--)
	{
		o << Vec {x_coefficients[i], y_coefficients[i]};

		if (i != 0)
			o << "t" << (i != 1 ? std::string("^") + std::to_string(i): "") <<  " + ";
	}

}

template <int degree>
std::ostream & operator<<(std::ostream & o, const PolynomialEdge<degree> & f)
{
	f.print(o);
	return o;
}
/* =============================================================== */

#endif
