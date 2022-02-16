#ifndef NINTEGRATE_HPP
#define NINTEGRATE_HPP

/**
 * Define the function to perform the integration
 *
 * - func is a function pointer to be integrated
 * - low is the lower bound
 * - high is the upper bound 
 * - eps is the desired precision
 */
double nintegrate(double (*func)(double),
		  double low, double high,
		  double eps);

#endif
