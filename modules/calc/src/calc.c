////////////////----------------------------------------////////////////
////////////////        EstDis                          ////////////////
////////////////----------------------------------------////////////////

	/*
	 * EstDis	This is a solver of statistics problems.
	 * Copyright (C) 2016 Alejandro Colomar Andrés
	 *
	 * This program is free software: you can redistribute it and/or
	 * modify it under the terms of the GNU General Public License
	 * as published by the Free Software Foundation, either version
	 * 3 of the License, or (at your option) any later version.

	 * This program is distributed in the hope that it will be
	 * useful, but WITHOUT ANY WARRANTY; without even the implied
	 * warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR
	 * PURPOSE.  See the GNU General Public License for more
	 * details.
	 *
	 * You should have received a copy of the GNU General Public
	 * License along with this program.
	 * If not, see <http://www.gnu.org/licenses/>.
	 */

////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////

# ifndef		CALC_H
	# define	CALC_H

	#include <math.h>

	#include "alx_math.h"



// distributions:
	// Binomial dist.	X -> B(n, p)
double	binomial_P	(double n, double p, double x)
{
	return	(alx_bin_coef(n, x) * pow(p, x) * pow(1-p, n-x));
}

double	binomial_E	(double n, double p)
{
	return	(n * p);
}

double	binomial_Var	(double n, double p)
{
	return	(n * p * (1 - p));
}


	// Poisson dist.	X -> P(l)
double	poisson_P	(double l, double x)
{
	return	(exp(-l) * pow(l, x) / alx_fact(x));
}

double	poisson_E	(double l)
{
	return	(l);
}

double	poisson_Var	(double l)
{
	return	(l);
}


	// Geometric dist.	X -> G(p)
double	geometric_P	(double p, double x)
{
	return	(p * pow(1-p, x-1));
}

double	geometric_E	(double p)
{
	return	(1 / p);
}

double	geometric_Var	(double p)
{
	return	((1 - p) / (p * p));
}


	// Uniform dist.	X -> U(a, b)
double	uniform_P	(double a, double b, double x1, double x2)
{
	return	((x2 - x1) / (b - a));
}

double	uniform_E	(double a, double b)
{
	return	((a + b) / 2);
}

double	uniform_Var	(double a, double b)
{
	return	((b - a) * (b - a) / 12);
}


	// Exponential dist.	X -> exp(b)
double	exponential_P	(double b, double x1, double x2)
{
	return	(exp(-b * x1) - exp(-b * x2));
}

double	exponential_E	(double b)
{
	return	(1 / b);
}

double	exponential_Var	(double b)
{
	return	(1 / (b * b));
}


	// Normal (Gauss) dist.	X -> N(u, o2);	Z -> N(0, 1)
double	normal_o	(double o2)
{
	return	(sqrt(o2));
}

double	normal_A	(double o)
{
	return	(1 / o);
}

double	normal_B	(double u, double o)
{
	return	(-u / o);
}

double	normal_Z	(double a, double b, double x)
{
	return	(a * x + b);
}

double	normal_X	(double a, double b, double z)
{
	return	((z - b) / a);
}


// descriptive statistics:
double	descrip_Eni	(double ni)
{
	return	(ni);
}

double	descrip_Exi	(double ni, double xi)
{
	return	(ni * xi);
}

double	descrip_Exi2	(double ni, double xi)
{
	return	(ni * xi * xi);
}

double	descrip_Exiyi	(double xi, double yi)
{
	return	(xi * yi);
}


double	descrip_u	(double Exi, double Eni)
{
	return	(Exi / Eni);
}

double	descrip_o2	(double Exi2, double Eni, double u)
{
	return	(Exi2 / Eni - u * u);
}

double	descrip_o	(double o2)
{
	return	(sqrt(o2));
}

double	descrip_s2	(double o2, double Eni)
{
	return	(o2 * Eni / (Eni - 1));
}

double	descrip_s	(double s2)
{
	return	(sqrt(s2));
}

double	descrip_CV	(double o, double u)
{
	return	(o / u);
}


double	descrip_oxy	(double n, double Exiyi, double ux, double uy)
{
	return	(Exiyi / n - ux * uy);
}

double	descrip_a	(double ox2, double oxy)
{
	return	(oxy / ox2);
}

double	descrip_b	(double ux, double uy, double a)
{
	return	(uy - a * ux);
}

double	descrip_r	(double ox, double oy, double oxy)
{
	return	(oxy / (ox * oy));
}


double	descrip_Eyiy2	(double xi, double yi, double a, double b)
{
	return	(pow(yi-a*xi-b, 2));
}


double	descrip_Aa	(double n, double Exi, double Exi2, double Eyiy2)
{
	return	(sqrt(Eyiy2 / ((n - 2) * (Exi2 - Exi * Exi / n))));
}

double	descrip_Ab	(double n, double Exi2, double Aa)
{
	return	(Aa * sqrt(Exi2 / n));
}

double	descrip_Vr	(double n, double Eyiy2)
{
	return	(Eyiy2 / n);
}

double	descrip_R2	(double oy2, double Vr)
{
	return	(1 - Vr / oy2);
}


# endif			/* calc.h */