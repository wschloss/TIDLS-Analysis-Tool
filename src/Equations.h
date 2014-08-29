/*

First draft of all dependencies needed to simulate data.
Once constants are defined, all functions should have the
necessary information to provide values.

*/

#include <cmath>

using namespace std;



/*

Equations "four" levels down

*/

double Egap(double temp) {
	/*
	define constants from map:
	Egap0 (initial)
	alpha
	beta
	*/
	double Egap0 = 0;
	double alpha = 0;
	double beta = 0;

	return ( Egap0 - (alpha*pow(temp,2.0))/(temp + beta) );
}

// 	POSSIBLE MISTAKE HERE IN m0 POWER, CHECK 1.27A PG 23
double me(double temp) {
	/*
	define constants from map:
	m0
	"see"
	Egap0
	ml
	*/
	double m0 = 0;
	double see = 0;
	double Egap0 = 0;
	double ml = 0;

	double result = 0;

	result = m0 * pow(6.0,2.0/3.0) * pow(pow(see * (Egap0)/(Egap(temp)),2.0) * ml,1.0/3.0);

	return result;
}

double mh(double temp) {
	/*
	define constants from map:
	m0
	a through i coefficients
	*/
	double m0 = 0;
	double a, b, c, d, e, f, g, h, i;

	double numerator = a + b*temp + c*pow(temp,2.0) + d*pow(temp,3.0) + e*pow(temp,4.0);
	double denominator = 1.0 + f*temp + g*pow(temp,2.0) + h*pow(temp,3.0) + i*pow(temp,4.0);

	return (m0*pow(numerator/denominator,2.0/3.0));
}



/*

Equations "three" levels down

*/


double Nv(double temp) {
	/*
	define constants from map:
	NN
	m0
	*/
	double NN = 0;
	double m0 = 0;

	return NN * pow(mh(temp)/m0,3.0/2.0) * pow(temp/300.0,3.0/2.0);
}

double Nc(double temp) {
	/*
	define constants from map:
	NN
	m0
	*/
	double NN = 0;
	double m0 = 0;

	return NN * pow(me(temp)/m0,3.0/2.0) * pow(temp/300.0,3.0/2.0);
}

double Ev(double temp) {
	/*
	define constants from map:
	Ev0
	Egap0
	*/
	double Ev0 = 0;
	double Egap0 = 0;

	return ( Ev0 + (Egap0 - Egap(temp))/2.0 );
}

double Ec(double temp) {
	/*
	define constants from map
	Ec0
	Egap0
	*/
	double Ec0 = 0;
	double Egap0 = 0;

	return ( Ec0 - (Egap0 - Egap(temp))/2.0 );
}

/********** WHAT IS EABORON? ***********/
double C(double temp, double NA){
	/*
	define constants from map:
	EABoron?
	kB
	*/
	double EABoron = 0;
	double kb = 0;

	double result = ( (4.0*NA)/(Nv(temp)) * exp((EABoron - Ev(temp))/(kb*temp)) );

	return result;

}

double ni2(double temp) {
	/*
	define constants from map:
	kb
	*/
	double kb = 0;

	double exponential = exp(-(Ec(temp) - Ev(temp))/(kb*temp));

	return (Nc(temp) * Nv(temp)) * exponential;
}

double fA(double temp, double NA) {
	/*
	no constants to defined from map
	*/
	double numerator = sqrt(1.0 + 2.0*C(temp,NA)) - 1.0;

	return numerator/C(temp,NA);
}

double vthe(double temp) {
	/*
	define constants from map:
	vthe0
	*/
	double vthe0 = 0;

	return vthe0 * pow(temp,1.0/2.0);
}

double vthh(double temp) {
	/*
	define constants from map:
	vthh0
	*/
	double vthh0 = 0;

	return vthh0 * pow(temp,1.0/2.0);
}

/*

Equations "two" levels down

*/

double tn0(double temp, double Nt, double sigmaN) {
	/*
	no constants defined from map
	*/

	return pow(Nt*sigmaN*vthe(temp),-1.0) * pow(temp/300.0,-1.0/2.0);
}

double tp0(double temp, double Nt, double sigmaP) {
	/*
	no constants defined from map
	*/

	return pow(Nt*sigmaP*vthh(temp),-1.0) * pow(temp/300.0,-1.0/2.0);
}

/*
NOTE THAT THE FOLLOWING p AND n CONCENTRATIONS
DO NOT TAKE FREEZE OUT OR INTRINSIC CONDUCTION
PIECEWISE EXPRESSIONS INTO ACCOUNT.
*/	
double p0(double temp, double NA) {
	/*
	no constants defined from map
	*/
	return fA(temp,NA) * NA;
}

double n0(double temp, double NA) {
	/*
	no constants defined from map
	*/
	return ni2(temp)/p0(temp,NA);
}

double p1(double temp, double Et) {
	/*
	define from map:
	kb
	*/
	double kb = 0;
	return Nv(temp) * exp(-(Et - Ev(temp))/(kb*temp));
}

double n1(double temp, double Et) {
	/*
	define from map:
	kb
	*/
	double kb = 0;
	return Nc(temp) * exp(-(Ec(temp) - Et)/(kb*temp));
}

/*

The lifetime expression used for simulating data

"One" level deep

*/

double tSRH(double temp, double deltaN, double NA, double Nt, double Et, double sigmaN, double sigmaP) {
	/*
	no constants from map

	NOTE:

	We need NA, Nt, Et, sigmaN, sigmaP values to reduce the needed variable to just
	temp and deltaN to provide the desired graphs of simulated data.
	*/

	double firstExpression = tn0(temp,Nt,sigmaN) * (p0(temp,NA) + p1(temp,Et) + deltaN);
	double secondExpression = tp0(temp,Nt,sigmaP) * (n0(temp,NA) + n1(temp,Et) + deltaN);
	double denominator = p0(temp,NA) + n0(temp,NA) + deltaN;

	return (firstExpression + secondExpression)/denominator;
}
 



