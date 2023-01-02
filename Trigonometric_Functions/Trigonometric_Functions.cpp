#include "Trigonometric_Functions.h"

#include <exception>

const double c_Pi = 3.141592653589793238;
const double c_Pi_div_2 = c_Pi / 2.0;
const double c_Pi_mul_3_2 = c_Pi * 1.5;
const double c_Pi_mul_2 = c_Pi * 2.0;

unsigned s_num_terms = 10;
double s_eps = 0.001;  // by default

namespace math_lib {

double cos(double)
{
	throw int(0);
	return 0;
}
double tan(double)
{
	throw int(0);
	return 0;
}
double ctan(double)
{
	throw int(0);
	return 0;
}

// error is defined by Lagrange's remainder term
//
//  sin(x) == x - x^3/3! + x^5/5! + ... + 
//
//	let a_k(x) == (-1)^(k+1) * x^(2*k-1) / (2*k-1)!
//
//  sin(x) == (Sum of: a_k(x) for k = {1..n}) + o(x^k) 
//
//	sin(x) == Sum of:  for n = {1..inf}
//  sin(x) == Sum of: (-1)^(n+1)
//
// because of:  x belongs to [0..Pi/2)
// 
// then:  abs( (-1)^n * x^(2*n-1) / (n-1)! )  <=  (Pi/2)^(2*n-1) / (n+1)!  <=  eps
//
void set_error(double eps)
{
	if (eps == 0.0)
		throw std::exception("Error: incorrect eps for math_lib");

	if (eps < 0.0)
		eps *= -1.0;

	// compute by iterations for not using std::log
	double err = 0.0;
	unsigned u_fact = 1;
	err = c_Pi_div_2;
	while (err > eps) {
		err *= c_Pi_div_2 / ++u_fact;
		err *= c_Pi_div_2 / ++u_fact;
	};

	s_num_terms = u_fact;
	s_eps = eps;
}

double get_error()
{
	return s_eps;
}

void set_num_terms(unsigned u)
{
	s_num_terms = u;
}

unsigned get_num_terms()
{
	return s_num_terms;
}

// function is implemented via expressing onto Maclaurin's series (Taylor's series at zero)
// compute for x, belonging to [0..Pi/2)
double sin_calc(double x)
{
	double res = 0;
	const unsigned n = get_num_terms();

	int coeff = 1;
	const double x_2 = x * x;
	double x_n = x;
	unsigned long n_fact = 1;

	for (unsigned u = 1; u <= n;)
	{
		res += coeff * x_n / n_fact;

		coeff *= -1;
		x_n *= x_2;
		n_fact *= ++u;
		n_fact *= ++u;
	}

	return res;
}


double sin_pos(double x)  // x >= 0.0, x belongs to [0..inf)
{
	// get frac
	if (x >= c_Pi_mul_2)
	{
		x /= c_Pi_mul_2;
		x -= static_cast<int>(x);
		x *= c_Pi_mul_2;
	}

	// here x is frac of itselt by mod 2*Pi
	// x belongs to [0..2*Pi)
	if (x <= c_Pi_div_2)         // [0..Pi/2)
		return sin_calc(x);
	else if (x <= c_Pi)          // [Pi/2..Pi)
		return sin_calc(c_Pi - x);
	else if (x <= c_Pi_mul_3_2)  // [Pi..3*Pi/2)
		return -sin_calc(x - c_Pi);
	else // x <= c_Pi_mul_2      // [3*Pi/2..2*Pi)
		return -sin_calc(c_Pi_mul_2 - x);
}

double sin(double x)
{
	if (x < 0.0)
		return -sin_pos(-x);  // sin(-x) == -sin(x)
	else
		return sin_pos(x);
}

double abs(double x)
{
	return (x >= 0) ? x : -x;
}

} // namespace math_lib 