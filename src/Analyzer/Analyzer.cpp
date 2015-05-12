#include "Analyzer.h"


vector<real>* Analyzer::deltaN_data, * Analyzer::tn0_data;
real Analyzer::Et, Analyzer::temp, Analyzer::NA;
EquationManager* Analyzer::equations;
const int Analyzer::one;


Analyzer::Analyzer(map<string, double>& constantsMap, vector< vector<double> >& lifetimeData) {
	equations = new EquationManager(constantsMap);

	//Init pointers
	deltaN_data = NULL;
	tn0_data = NULL;
	fvec = NULL;
	fjac = NULL;
	wa4 = NULL;
	//tau and k guess init
	x = new real[2];
	x[0] = 10.0e-06; // tn0
	x[1] = 1; // k

	NA = 1e16;

	EtIt = 100;
	// Number of deltaN,temperature data pairs taken
	int dataPairs = lifetimeData.size();

	//Hard coded temps that we got from the data
	// These are in celsius
	double temperatures[15] = {190, 180, 170, 160, 145, 135, 125, 115, 105, 95,
								80, 70, 60, 50, 35};

	// iterate over each temperature
	for (int i = 0; i < dataPairs/2; i++) {
		temp = 273 + temperatures[i]; //temp must be in kelvin

		min = equations->Ev(temp);
		max = equations->Ec(temp);
		inc = (max-min) / EtIt;

		Et = min;

		//Data at this temp
		deltaN_data = &lifetimeData[2*i];
		tn0_data = &lifetimeData[2*i + 1];

		//iterate over each Et through the band gap
		for (int j = 0; j <= EtIt; j++) {

			runFit();

			tn0 = x[0];
			k = x[1];
			
			// Find chi^2 value for the fit
			// sum of (observed - expected)^2 / expected
			chi2 = 0;
			for (int z = 0; z < m; z++) {
				double expected = tSRH(x, deltaN_data->at(z), Et);
				double numerator = (tn0_data->at(z) - expected);
				chi2 += numerator * numerator / expected;
			}
			
			// Put these into arrays for later use
			
			tempVec.push_back(temp);
			EtVec.push_back(Et);
			tn0Vec.push_back(tn0);
			kVec.push_back(k);
			chi2Vec.push_back(chi2);
			

			// Increment Et
			Et += inc;

		}

		cout << "FINISHED A TEMPERATURE!" << endl;
	}

	if (equations != NULL) {
		delete equations;
	}

	printDataToFile();

}

void Analyzer::runFit()
{
	
	m = tn0_data->size(); // number of functions (tau_SRH data)
	n = 2; // number of variables (parameters)

	fvec = new real[m];
	fjac = new real[m * n];
	wa4 = new real[m];

	/*      the following starting values provide a rough fit. */

	x[0] = 1.; // tau_n0
	x[1] = 1.; // k

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
	factor = 100.; // initial step bound, ""
	nprint = 0; // controlled printing, ""

	
	__minpack_func__(lmdif)(&fcn, &m, &n, x, fvec, &ftol, &xtol, &gtol, &maxfev, &epsfcn,
		diag, &mode, &factor, &nprint, &info, &nfev, fjac, &ldfjac,
		ipvt, qtf, wa1, wa2, wa3, wa4);
	

	// Print Debugging Information
	//cout << info << endl;

	
	if (fvec != NULL) {
		delete [] fvec;
		fvec = NULL;
	}
	
	if (fjac != NULL) {
		delete [] fjac;
		fjac = NULL;
	}

	if (wa4 != NULL) {
		delete [] wa4;
		wa4 = NULL;
	}

}

void Analyzer::fcn(const int *m, const int *n, const real *x, real *fvec, int *iflag)
{

	/*      subroutine fcn for lmdif (User Guide p. 124 */
	assert(*n == 2);
	if (*iflag == 0)
	{
		/*      insert print statements here when nprint is positive. */
		return;
	}
	for (int i = 0; i < *m; i++) {
		// Array of functions to be minimized: (observed - expected)^2/sigma^2
		fvec[i] = tSRH(x, deltaN_data->at(i), Et) - tn0_data->at(i);
	}
	return;
}

/*
real Analyzer::tSRH(const real *x, real deltaN, real Et) {
	real firstExpression = (equations->p0(temp, NA) + equations->p1(temp, Et) + deltaN);
	real secondExpression = (equations->n0(temp, NA) + equations->n1(temp, Et) + deltaN);
	real denominator = equations->p0(temp, NA) + equations->n0(temp, NA) + deltaN;

	// tn0 broken down to N_t*sigmaN fit
	return pow(x[0]*equations->vthe(temp),-1.0) * (firstExpression + (x[1] * secondExpression)) / denominator;
}
*/

real Analyzer::tSRH(const real *x, real deltaN, real Et) {
	real firstExpression = (equations->p0(temp, NA) + equations->p1(temp, Et) + deltaN);
	real secondExpression = (equations->n0(temp, NA) + equations->n1(temp, Et) + deltaN);
	real denominator = equations->p0(temp, NA) + equations->n0(temp, NA) + deltaN;

	return x[0] * (firstExpression + (x[1] * secondExpression)) / denominator;
}


void Analyzer::printDataToFile() {
	// Ask for file name
	string filename;
	cout << "\nEnter a filename to export data (if file already exists, data is overwritten): ";
	cin >> filename;

	// Open stream and print a header on the first line
	ofstream output(filename);
	if (!output) {
		cerr << "\nError creating export file.\n";
		exit(1);
	}
	output << "Temperature, Et, tn0, k, chi2" << endl;

	// Print out the data vectors created earlier
	for (int i = 0; i < tempVec.size(); i++) {
		output << tempVec[i] << ", " << EtVec[i] << ", " << tn0Vec[i] << ", " << kVec[i] << ", " << chi2Vec[i] << endl;
	}

	output.close();
}