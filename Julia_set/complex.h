#ifndef COMPLEX_H
#define COMPLEX_H

#include <algorithm>
#include <cmath>
#include <utility>


class Complex {
 public:
  Complex(double real = 0.0, double imaginary = 0.0);
  Complex(std::pair<double, double> other);
  Complex(const Complex &other) = default;
  ~Complex() = default;

  void Swap(Complex &other);

  double Abs();
  double SqrAbs();

  Complex operator -();
  Complex operator ~();
  Complex operator +(Complex other);
  Complex operator -(Complex other);
  Complex operator *(Complex other);
  Complex operator /(Complex other);

  Complex operator +(double other);
  Complex operator -(double other);
  Complex operator *(double other);
  Complex operator /(double other);

  Complex& operator =(Complex other);

 private:
  double real_;
  double imaginary_;
};


#endif // COMPLEX_H
