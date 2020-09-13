#include "tridiagonalmatrixsolver.hpp"
#include <cmath>
#include <string>
#include <time.h>
#include <armadillo>

using namespace arma;

vec f(vec x);

int main(int argc, char const *argv[]) {

  clock_t start, end;
  double timeused;
  int N = atoi(argv[1]);
  string algorithm = string(argv[2]);
  string filename = algorithm + "_N_" + to_string(N) + ".txt";

  if (algorithm == "general"){
    ThomasSolver my_solver;
    my_solver.init(N, f);
    start = clock();
    my_solver.solve();
    end = clock();
    timeused = (double) (end-start)/CLOCKS_PER_SEC;
    my_solver.write_to_file(filename);
  }

  if (algorithm == "special"){
    SpecialThomasSolver my_solver;
    my_solver.init(N, f);
    start = clock();
    my_solver.solve();
    end = clock();
    timeused = (double) (end-start)/CLOCKS_PER_SEC;
    my_solver.write_to_file(filename);
  }

  return 0;
}

vec f(vec x){
  return 100.*exp(-10*x);
}
