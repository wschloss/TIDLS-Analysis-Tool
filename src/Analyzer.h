/*

This class is responsible for loading data from txt consisting
of either pregenerated simulated data or actual data.  This
class also performs the fitting analysis and exports results
to txt.

Author:

*/

#pragma once

#include "EquationManager.h"
#include <map>
#include <string>
#include <vector>
#include <iostream>
#include <stdio.h>
#include <fstream>
#include <math.h>
#include <assert.h>
extern "C"
{
#include <minpack.h>
};
#define real __minpack_real__

using namespace std;

class Analyzer {
public:
	Analyzer(map<string, double> constantsMap, map<double,vector<double> > dataMap);
	void runFit(map<double,vector<double> > dataMap);
	static void fcn(const int *m, const int *n, const real *x, real *fvec, int *iflag);

private:
	EquationManager* equations;
	// Variables necessary to define a defect:
	double NA;
	// Variables necessary for the lmdif (Levenberg–Marquardt algorithm):
	int m, n, maxfev, mode, nprint, info, nfev, ldfjac, iflag;
	int ipvt[2];
	real ftol, xtol, gtol, epsfcn, factor, fnorm;
	real x[2], diag[2], qtf[2], wa1[2], wa2[2], wa3[2], *fvec, *fjac, *wa4;
	int one=1;
	real covfac;

};