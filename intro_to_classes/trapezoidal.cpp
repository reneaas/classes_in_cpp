#include "trapezoidal.hpp"
#include <iostream>
#include <cmath>

using namespace std;

void Trapezoidal::Initialize(double a, double b, int N){
  m_a = a;
  m_b = b;
  m_N = N;
  m_I = 0.;
  m_stepsize = (b-a)*(1./N);
}

void Trapezoidal::Integrate(double f(double x)){
  double x = 0;
  m_I += 0.5*(f(m_a) + f(m_b));

  for (int i = 0; i < m_N; i++){
    x = m_a + i*m_stepsize;
    m_I += f(x);
  }

  m_I *= m_stepsize;
}

void Trapezoidal::Print(){
  cout << "Integral = " << m_I << endl;
}
