#include "catch.hpp"

#include "nintegrate.hpp"

#include <cmath>
const double PI = 2*atan2(1,0);

constexpr double eps = 1e-14;

// Some test functions to integrate
// constant function
double fconst(double x){
  return 1.0 + 0.0*x;
}

// linear function
double flinear(double x){
  return x;
}

// Unit Gaussian function
double fgaussian(double x){

  return exp(-0.5*x*x)/sqrt(2*PI);
}

TEST_CASE("Test constant integals", "[nintegrate]") {

  REQUIRE(nintegrate(fconst, 0.0, 1.0, eps) == Approx(1.0).margin(eps));
  REQUIRE(nintegrate(fconst, -1.0, 1.0, eps) == Approx(2.0).margin(eps));
}

TEST_CASE("Test linear integals", "[nintegrate]") {

  REQUIRE(nintegrate(flinear, 0.0, 1.0, eps) == Approx(0.5).margin(eps));
  REQUIRE(nintegrate(flinear, -1.0, 1.0, eps) == Approx(0.0).margin(eps));
}

TEST_CASE("Test sin integals", "[nintegrate]") {

  REQUIRE(nintegrate(sin, 0.0, 2*PI, eps) == Approx(0.0).margin(eps));
  REQUIRE(nintegrate(sin, -PI, PI, eps) == Approx(0.0).margin(eps));
  REQUIRE(nintegrate(sin, 0.0, PI, eps) == Approx(2.0).margin(eps));
  REQUIRE(nintegrate(sin, -PI/2, 0, eps) == Approx(-1.0).margin(eps));
  REQUIRE(nintegrate(sin, 0, PI/2, eps) == Approx(1.0).margin(eps));
}

TEST_CASE("Test exp integals", "[nintegrate]") {

  double a,b;
  
  a = 0.0;
  b = 1.0;
  REQUIRE(nintegrate(exp, a, b, eps) == Approx(exp(b)-exp(a)).margin(eps));

  a = -5.1;
  b = 7.3;
  REQUIRE(nintegrate(exp, a, b, eps) == Approx(exp(b)-exp(a)).margin(eps));

  a = 5.6;
  b = 5.7;
  REQUIRE(nintegrate(exp, a, b, eps) == Approx(exp(b)-exp(a)).margin(eps));

  a = -10.0;
  b = -2.1;
  REQUIRE(nintegrate(exp, a, b, eps) == Approx(exp(b)-exp(a)).margin(eps));
}

TEST_CASE("Test Gaussion integals", "[nintegrate]") {

  REQUIRE(nintegrate(fgaussian, 0, 100, eps) == Approx(0.5).margin(eps));
  REQUIRE(nintegrate(fgaussian, -100, 100, eps) == Approx(1.0).margin(eps));

}

TEST_CASE("Test max iterations", "[nintegrate]") {

  double result = nintegrate(sin, 0.0, 2*PI, 1e-16);
  INFO(result)
    
  // this should fail so invert test
  REQUIRE(nintegrate(sin, 0.0, 2*PI, 1e-20) != Approx(0.0).margin(1e-20));

  // this should pass
  REQUIRE(nintegrate(sin, 0.0, 2*PI, 1e-20) == Approx(0.0).margin(1e-5));
}
