#include "tridiagonalmatrixsolver.hpp"
#include <cmath>
#include <string>
#include <time.h>

using namespace std;

double f(double x);

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

double f(double x){
  return 100.*exp(-10*x);
}
