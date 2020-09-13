#include "tridiagonalmatrixsolver.hpp"

void TridiagonalMatrixSolver::initialize(int N, vec f(vec x))
{
  m_N = N;
  double h = 1./(m_N+1); //Local variable, only needed in this function.
  m_q = vec(m_N);
  m_v = vec(m_N);
  m_x = linspace(h, 1-h, m_N); //Only interior points of the mesh.
  m_q = h*h*f(m_x);
}

void TridiagonalMatrixSolver::write_to_file(string filename)
{
  m_ofile.open(filename);
  for (int i = 0; i < m_N; i++){
    m_ofile << m_x(i) << " " << m_v(i) << endl;
  }
  m_ofile.close();
}
