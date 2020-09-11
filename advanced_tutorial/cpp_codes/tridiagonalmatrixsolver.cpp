#include "tridiagonalmatrixsolver.hpp"

void TridiagonalMatrixSolver::initialize(int N, double f(double x))
{
  m_N = N;
  m_stepsize = 1./(m_N+1);
  m_q = vec(m_N);
  m_v = vec(m_N);
  m_x = linspace(m_stepsize, 1-m_stepsize, m_N);
  double hh = m_stepsize*m_stepsize;

  for (int i = 0; i < m_N; i++){
    m_q(i) = hh*f(m_x(i));
  }
}

void TridiagonalMatrixSolver::write_to_file(string filename)
{
  m_ofile.open(filename);
  for (int i = 0; i < m_N; i++){
    m_ofile << m_x(i) << " " << m_v(i) << endl;
  }
  m_ofile.close();
}
