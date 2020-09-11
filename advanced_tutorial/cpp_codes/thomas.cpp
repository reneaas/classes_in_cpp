#include "tridiagonalmatrixsolver.hpp"

void ThomasSolver::init(int N, double f(double x))
{
  initialize(N, f);  //ThomasSolver inherited this from TridiagonalMatrixSolver, so we can freely use it here.
  m_a = vec(m_N).fill(-1.);
  m_b = vec(m_N).fill(2.);
  m_c = vec(m_N).fill(-1);
  m_v = vec(m_N).fill(0.);
}

void ThomasSolver::solve()
{
  forward_substitution();
  backward_substitution();
}

void ThomasSolver::forward_substitution()
{
  for (int i = 1; i < m_N; i++){
    m_b(i) = m_b(i) - m_a(i-1)*m_c(i-1)/m_b(i-1);
    m_q(i) = m_q(i) - m_a(i-1)*m_q(i-1)/m_b(i-1);
  }
}

void ThomasSolver::backward_substitution()
{
  m_v(m_N-1) = m_q(m_N-1)/m_b(m_N-1);
  for (int i = m_N-2; i >= 0; i--){
    m_v(i) = (m_q(i) - m_c(i)*m_v(i+1))/m_b(i);
  }
}
