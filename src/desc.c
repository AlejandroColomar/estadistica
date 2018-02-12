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

	#include <inttypes.h>
	#include <stdio.h>

	#include "alx_getnum.h"

	#include "calc.h"

void	desc_1var	(void)
{
	int64_t		N;
	int64_t		i;
	long double	xi;
	long double	ni;
	long double	Eni = 0;
	long double	Exi = 0;
	long double	Exi2 = 0;
	long double	u;
	long double	o2;
	long double	o;
	long double	s2;
	long double	s;
	long double	CV;

	printf("\n_______________________________________________________________________________________________________________\n");
	printf("u\t= E(ni*xi)/n\t--Media.\n");
	printf("o2\t= E(xi^2)/n-u^2\t--Varianza.\n");
	printf("s2\t= o2*n/(n-1)\t--Cuasivarianza.\n");
	printf("o\t= sqrt(o2)\t--Desviacion tipica.\n");
	printf("s\t= sqrt(s2)\t--Cuasidesviacion tipica.\n");
	printf("CV\t= o/u\t\t--Coeficiente de variacion.\n\n");

	N =	alx_getint_m(1, 2, "N:\t", NULL);

	for (i = 1; i <= N; i++) {
		printf("x_%"PRIi64":\t", i);
		xi =	alx_getdbl(NULL, NULL);
		printf("n_%"PRIi64":\t", i);
		ni =	alx_getdbl_m(0, 1, NULL, NULL);

		Exi +=	descrip_Exi(ni, xi);
		Exi2 +=	descrip_Exi2(ni, xi);
		Eni +=	descrip_Eni(ni);
	}

	u =	descrip_u(Exi, Eni);
	o2 =	descrip_o2(Exi2, Eni, u);
	o =	descrip_o(o2);
	s2 =	descrip_s2(o2, Eni);
	s =	descrip_s(s2);
	CV =	descrip_CV(o, u);

	printf("\nu\t= %Lf", u);
	printf("\no2\t= %Lf", o2);
	printf("\no\t= %Lf", o);
	printf("\ns2\t= %Lf", s2);
	printf("\ns\t= %Lf", s);
	printf("\nCV\t= %Lf\n", CV);
getchar();
getchar();
}

void	desc_2var	(void){
	int64_t		n;
	int64_t		i;
	long double	Exi = 0;
	long double	Exi2 = 0;
	long double	ux;
	long double	ox2;
	long double	ox;
	long double	a;
	long double	Aa;
	long double	b;
	long double	Ab;
	long double	Eyi = 0;
	long double	Eyi2 = 0;
	long double	uy;
	long double	oy2;
	long double	oy;
	long double	c;
	long double	Ac;
	long double	d;
	long double	Ad;
	long double	Exiyi = 0;
	long double	oxy;
	long double	r;
	long double	yiy2;
	long double	xix2;
	long double	Eyiy2 = 0;
	long double	Exix2 = 0;
	long double	Vr;
	long double	R2;

	printf("\n_______________________________________________________________________________________________________________\n");
	printf("u\t= E(xi)/n\t\t--Media.\n");
	printf("o2\t= E(xi^2)/n-u^2\t\t--Varianza.\n");
	printf("o\t= sqrt(o2)\t\t--Desviacion tipica.\n");
	printf("oxy\t= E(xi*yi)/n-ux*uy\t--Covarianza.\n\n");

	printf("a\t= oxy/ox2\t\t--Pendiente.\n");
	printf("b\t= uy-a*ux\t\t--Sesgo.\n");
	printf("r\t= oxy/(ox*oy)\t\t--Coeficiente de correlacion lineal.\n\n");

	printf("n\t=\t\t\t--Numero de puntos.\n\n");

	n =	alx_getint_m(1, 2, "n:\t", NULL);

	long double	x[n + 1];
	long double	y[n + 1];

	for (i = 1; i <= n; i++) {
		printf("x_%"PRIi64":\t", i);
		x[i] =		alx_getdbl(NULL, NULL);
		Exi +=		descrip_Exi(1, x[i]);
		Exi2 +=		descrip_Exi2(1, x[i]);

		printf("y_%"PRIi64":\t", i);
		y[i] =		alx_getdbl(NULL, NULL);
		Eyi +=		descrip_Exi(1, y[i]);
		Eyi2 +=		descrip_Exi2(1, y[i]);

		Exiyi +=	descrip_Exiyi(x[i], y[i]);
	}

	ux =	descrip_u(Exi, n);
	ox2 =	descrip_o2(Exi2, n, ux);
	ox =	descrip_o(ox2);

	uy =	descrip_u(Eyi, n);
	oy2 =	descrip_o2(Eyi2, n, uy);
	oy =	descrip_o(oy2);

	oxy =	descrip_oxy(Exiyi, n, ux, uy);
	a =	descrip_a(oxy, ox2);
	b =	descrip_b(ux, uy, a);
	c =	descrip_a(oxy, oy2);
	d =	descrip_b(uy, ux, c);
	r =	descrip_r(oxy, ox, oy);

	for (i = 1; i <= n; i++) {
		Eyiy2 +=	descrip_Eyiy2(x[i], y[i], a, b);
		Exix2 +=	descrip_Eyiy2(y[i], x[i], c, d);;
	}

	Aa =	descrip_Aa(n, Exi, Exi2, Eyiy2);
	Ab =	descrip_Ab(n, Exi2, Aa);
	Ac =	descrip_Aa(n, Eyi, Eyi2, Exix2);
	Ad =	descrip_Ab(n, Eyi2, Ac);

	Vr =	descrip_Vr(n, Eyiy2);
	R2 =	descrip_R2(oy2, Vr);

	printf("\nux\t= %Lf", ux);
	printf("\nox2\t= %Lf", ox2);
	printf("\nox\t= %Lf\n", ox);
	printf("\nuy\t= %Lf", uy);
	printf("\noy2\t= %Lf", oy2);
	printf("\noy\t= %Lf\n", oy);
	printf("\noxy\t= %Lf", oxy);
	printf("\na\t= %Lf", a);
	printf("\nAa\t= %Lf", Aa);
	printf("\nb\t= %Lf", b);
	printf("\nAb\t= %Lf", Ab);
	printf("\nc\t= %Lf", c);
	printf("\nAc\t= %Lf", Ac);
	printf("\nd\t= %Lf", d);
	printf("\nAd\t= %Lf", Ad);
	printf("\nr\t= %Lf", r);
	printf("\nVr\t= %Lf", Vr);
	printf("\nR2\t= %Lf\n", R2);
getchar();
getchar();
}