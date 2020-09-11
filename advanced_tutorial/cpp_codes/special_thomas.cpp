#include "tridiagonalmatrixsolver.hpp"


void SpecialThomasSolver::init(int N, double f(double x)){
  initialize(N, f); //SpecialThomasSolver inherited this from TridiagonalMatrixSolver, so we can use it here.
}

void SpecialThomasSolver::solve()
{
  forward_substitution();
  backward_substitution();
}

void SpecialThomasSolver::forward_substitution()
{
  for (int i = 1; i < m_N; i++){
    m_q(i) = m_q(i) + 1.*i/(i+1)*m_q(i-1);
  }
}

void SpecialThomasSolver::backward_substitution()
{

  m_v(m_N-1) = ((double) m_N/(m_N+1))*m_q(m_N-1);
  for (int i = m_N-2; i >= 0; i--){
    m_v(i) = ((double) (i+1)/(i+2))*(m_q(i)+m_v(i+1));
  }
}
