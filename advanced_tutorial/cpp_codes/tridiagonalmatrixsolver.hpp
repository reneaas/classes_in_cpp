#ifndef TridiagonalMatrixSolver_HPP
#define TridiagonalMatrixSolver_HPP
#include <fstream>
#include <armadillo>

using namespace std;
using namespace arma;

/*
-------------------------------------------------------------------
TridiagonalMatrixSolver:
A solver for a tridiagonal toeplitz matrix A
solves the equation Av = q.
-------------------------------------------------------------------
m_q: RHS of the matrix equation
m_x: vector of mesh points on the interval (0,1).
m_v: Solution vector of the matrix equation.
-------------------------------------------------------------------
*/
class TridiagonalMatrixSolver {
//Declare variables as "protected" so that derived classes can inherit the member variables.
protected:
  int m_N;
  vec m_q, m_x, m_v;
  ofstream m_ofile;

public:
  void initialize(int N, vec f(vec x));
  void write_to_file(string filename);
};


/*
---------------------------------------------------------------------
ThomasSolver: A derived class from TridiagonalMatrixSolver.
Solves the matrix equation Av = q using the general Thomas algorithm.
---------------------------------------------------------------------
m_a: Lower off-diagonal elements of A.
m_b: Diagonal elements of A.
m_c: Upper off-diagonal elements of A.
---------------------------------------------------------------------
*/
class ThomasSolver : public TridiagonalMatrixSolver {
private:
  vec m_a, m_b, m_c;
  void forward_substitution();
  void backward_substitution();
public:
  void init(int N, vec f(vec x));
  void solve();
};

/*
---------------------------------------------------------------------
SpecialThomasSolver: A derived class from TridiagonalMatrixSolver.
Solves the matrix equation Av = q using the a specialized Thomas algorithm.
where elements of the matrix A is precalculated.
---------------------------------------------------------------------
*/
class SpecialThomasSolver : public TridiagonalMatrixSolver {
private:
  void forward_substitution();
  void backward_substitution();
public:
  void init(int N, vec f(vec x));
  void solve();
};

#endif
