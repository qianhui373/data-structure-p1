#include "nintegrate.hpp"
#include "catch.hpp"
#include <cstdlib>
#include <cmath>
#define NINTEGRATE_HPP





double nintegrate(double (*func)(double),
		  double low, double high,
		  double eps){
    const int max_steps = 25;
  // TODO: Implement your function here
  /////////////////////////////////////////////////////////
    double R1[max_steps];
    double R2[max_steps];
    
    double h = high - low;

    R1[0] = (func(low) + func(high)) * h * 0.5;

    for (int i = 1; i <= (max_steps - 1); i++) {
        h = h / 2;


        // compute the trapezoid approximation using the new
        // step size, place in second array
        double temp = 0.0;
        double steps = pow(2, (static_cast<double>(i)- 1));
        //double steps = 2 ^ (i - 1);
        for (int j = 1; j <= steps; j++) {
            temp = temp + func(low + (2* static_cast<double>(j) - 1) * h);
        }

        R2[0] = h * temp + 0.5 * R1[0];

        for (int j = 1; j <= i; j++) {
            double n = pow(4.0, static_cast<double>(j));
            
            //int n = 4 ^ j;
            R2[j] = (n * R2[j - 1] - R1[j - 1]) / (n-1);
        }

        if (i > 1 && (fabs(R1[i - 1] - R2[i]) < eps)) {
            return R2[i - 1];
        }

        for (int j = 0; j < max_steps; j++) {
            R1[j] = R2[j];
        }
    }

    return R1[max_steps - 1];//0.0;
}
