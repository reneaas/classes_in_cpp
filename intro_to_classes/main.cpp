#include "trapezoidal.hpp"
#include <iostream>
#include <cmath>

using namespace std;

double f(double x);

int main(int argc, char const *argv[]) {
  //Parameters
  double a = 0;
  double b = 1;
  int N = 1000;

  //Solve integral
  Trapezoidal my_solver;
  my_solver.Initialize(a, b, N);
  my_solver.Integrate(f);
  my_solver.Print();

  return 0;
}

double f(double x){
  return exp(-x);
}
