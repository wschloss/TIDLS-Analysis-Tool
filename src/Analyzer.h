/*

This class performs the fitting analysis and exports results
to txt.

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
#include "../Minpack/cminpack-1.3.4/minpack.h"
};
#define real __minpack_real__

using namespace std;

class Analyzer {
public:
	Analyzer(map<string, double>& constantsMap, vector< vector<double> >& lifetimeData);
	void runFit();
	static void fcn(const int *m, const int *n, const real *x, real *fvec, int *iflag);
	static real tSRH(const real *x, real deltaN, real Et);
	void printDataToFile();

private:
	// Variables necessary to define a defect
	//static 3
	static EquationManager* equations;
	static vector<real>* data, *deltaN;
	static real NA, temp, Et;
	// Energy gap at current temp
	double gap;
	// Increase in Et per iteration
	double inc;
	// Outputs
	double tn0, k, chi2;
	// Vectors with final data output
	vector<double> tempVec, EtVec, tn0Vec, kVec, chi2Vec;
	// Energy iterations
	int EtIt;
	// Variables necessary for the lmdif (Levenberg–Marquardt algorithm):
	int m, n, maxfev, mode, nprint, info, nfev, ldfjac, iflag;
	int ipvt[2];
	real ftol, xtol, gtol, epsfcn, factor, fnorm;
	real *x, diag[2], qtf[2], wa1[2], wa2[2], wa3[2], *fvec, *fjac, *wa4;
	//This is definitely what makes this code professional
	static const int one = 1;
	real covfac;

};