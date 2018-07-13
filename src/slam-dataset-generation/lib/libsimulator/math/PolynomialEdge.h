#ifndef MATH_POLYNOMIALEDGE_H
#define MATH_POLYNOMIALEDGE_H

#include "math/UnitParametricEdge.h"
#include "math/Polynomial.h"

template <int degree>
class PolynomialEdge : public UnitParametricEdge
{
public:
	PolynomialEdge() = default;

	PolynomialEdge(Polynomial<degree> x, Polynomial<degree> y)
		: x_(std::move(x))
		, y_(std::move(y))
	{ }

	PolynomialEdge(Vec A, Vec B, Vec C, Vec D)
		: x_(Polynomial<3>(D.x, C.x, B.x, A.x))
		, y_(Polynomial<3>(D.y, C.y, B.y, A.y))
	{ }

	virtual ~PolynomialEdge() = default;

	Vec operator()(double t) const
	{
		return {x_(t), y_(t)};
	}

	Vec derivative(double t, int n = 1) const
	{
		return {x_.derivative(t, n), y_.derivative(t, n)};
	}

	void setX(Polynomial<degree> x)
	{
		x_ = std::move(x);
	}

	void setY(Polynomial<degree> y)
	{
		y_ = std::move(y);
	}
private:
	Polynomial<degree> x_;
	Polynomial<degree> y_;
};

#endif
