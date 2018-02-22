
/******************************************************************************
 * This program is free software; you can redistribute it and/or modify	      *
 * it under the terms of the GNU General Public License as published by	      *
 * the Free Software Foundation; either version 2 of the License, or          *
 * (at your option) any later version.					      *
 *									      *
 * This program is distributed in the hope that it will be useful,	      *
 * but WITHOUT ANY WARRANTY; without even the implied warranty of	      *
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the	      *
 * GNU General Public License for more details.				      *
 *									      *
 * You should have received a copy of the GNU General Public License	      *
 * along with this program; if not, see the file COPYING, or write	      *
 * to the Free Software Foundation, Inc.				      *
 ******************************************************************************/

# ifndef		ALX_MATH_H
	# define	ALX_MATH_H

//	#include <curses.h>
	#include <math.h>
//	#include <stdbool.h>
//	#include <stdarg.h>
	#include <stdint.h>

	/*
	 * Factorial
	 */
double	alx_fact	(int64_t n);

	/*
	 * Binomial coefficient (a b):				--!!!  a > b  !!!--
	 * - Bugs: If !(a > b), returns 1.
	 */
double	alx_bin_coef	(int64_t a, int64_t b);

# endif			/* alx_math.h */
