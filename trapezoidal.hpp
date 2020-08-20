#ifndef TRAPEZOIDAL_HPP
#define TRAPEZOIDAL_HPP

class Trapezoidal {
private:
  double m_a, m_b, m_I, m_stepsize;
  int m_N;

public:

  void Initialize(double a, double b, int N);
  void Integrate(double f(double x));
  void Print();
};

#endif
