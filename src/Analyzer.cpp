#include "Analyzer.h"

Analyzer::Analyzer(map<string, double> constantsMap, map<double,vector<double> > dataMap) {
	equations = new EquationManager(constantsMap);
	NA = 10e16;

	runFit(dataMap);
}

void Analyzer::runFit(map<double,vector<double> > dataMap)
{
	int i, j;
	m = 15; // number of functions (tau_SRH data)
	n = 2; // number of variables (parameters)

	fvec = new real[m];
	fjac = new real[m];
	wa4 = new real[m];

	/*      the following starting values provide a rough fit. */

	x[1 - 1] = 1.; // tau_n0
	x[2 - 1] = 1.; // k

	/* ldfjac is a positive integer not less than m which specifies */
	/* the leading dimension of the array fjac */
	/* fjac is the characteristic algorithm so-to-speak for the */
	/* Levenber-Marquardt algorithm which involves the Jacobian */

	ldfjac = m;

	/*      set ftol and xtol to the square root of the machine */
	/*      and gtol to zero. unless high precision solutions are */
	/*      required, these are the recommended settings. */

	ftol = sqrt(__minpack_func__(dpmpar)(&one));
	xtol = sqrt(__minpack_func__(dpmpar)(&one));
	gtol = 0.;

	/* termination occurs when the number of calls to fcn is at least */
	/* maxfev by the end of an iteration */
	maxfev = 800;
	epsfcn = 0.; // precision, refer to User Guide p. 124 (minpack)
	mode = 1; // scaling, refer to User Guide p. 124 (minpack)
	factor = 1.e2; // initial step bound, ""
	nprint = 0; // controlled printing, ""
	
	__minpack_func__(lmdif)(&fcn, &m, &n, x, fvec, &ftol, &xtol, &gtol, &maxfev, &epsfcn,
		diag, &mode, &factor, &nprint, &info, &nfev, fjac, &ldfjac,
		ipvt, qtf, wa1, wa2, wa3, wa4);

	fnorm = __minpack_func__(enorm)(&m, fvec);

	printf("      final l2 norm of the residuals%15.7g\n\n", (double)fnorm);
	printf("      number of function evaluations%10i\n\n", nfev);
	printf("      exit parameter                %10i\n\n", info);
	printf("      final approximate solution\n");
	for (j = 1; j <= n; j++) printf("%s%15.7g", j % 3 == 1 ? "\n     " : "", (double)x[j - 1]);
	printf("\n");
	ftol = __minpack_func__(dpmpar)(&one);
	covfac = fnorm*fnorm / (m - n);
	__minpack_func__(covar)(&n, fjac, &ldfjac, ipvt, &ftol, wa1);
	printf("      covariance\n");
	for (i = 1; i <= n; i++) {
		for (j = 1; j <= n; j++)
			printf("%s%15.7g", j % 3 == 1 ? "\n     " : "", (double)fjac[(i - 1)*ldfjac + j - 1] * covfac);
	}
	printf("\n");
}

void Analyzer::fcn(const int *m, const int *n, const real *x, real *fvec, int *iflag)
{

	/*      subroutine fcn for lmdif (User Guide p. 124 */

	int i;
	real tmp1, tmp2, tmp3;
	// tau_SRH data
	real y[15] = { 1.4e-1, 1.8e-1, 2.2e-1, 2.5e-1, 2.9e-1, 3.2e-1, 3.5e-1,
		3.9e-1, 3.7e-1, 5.8e-1, 7.3e-1, 9.6e-1, 1.34, 2.1, 4.39 };
	assert(*m == 15 && *n == 2);

	if (*iflag == 0)
	{
		/*      insert print statements here when nprint is positive. */
		return;
	}
	for (i = 1; i <= 15; i++)
	{
		tmp1 = i;
		tmp2 = 16 - i;
		tmp3 = tmp1;
		if (i > 8) tmp3 = tmp2;
		// Array of functions to be minimized: (observed - expected)/sigma^2
		fvec[i - 1] = y[i - 1] - (x[1 - 1] + tmp1 / (x[2 - 1] * tmp2 + x[3 - 1] * tmp3));
	}
	return;
}