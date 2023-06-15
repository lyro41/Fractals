#include "complex.h"

Complex::Complex(double real, double imaginary) : real_(real), imaginary_(imaginary) {
  return;
}

Complex::Complex(std::pair<double, double> other) : real_(other.first), imaginary_(other.second) {
  return;
}

void Complex::Swap(Complex &other) {
  std::swap(this->real_, other.real_);
  std::swap(this->imaginary_, other.imaginary_);
  return;
}

double Complex::Abs() {
  return std::sqrt(real_ * real_ + imaginary_ * imaginary_);
}

double Complex::SqrAbs() {
  return real_ * real_ + imaginary_ * imaginary_;
}

Complex Complex::operator -() {
  Complex result;
  result.real_ = -this->real_;
  result.imaginary_ = -this->imaginary_;
  return result;
}

Complex Complex::operator ~() {
  Complex result;
  result.real_ = this->real_;
  result.imaginary_ = -this->imaginary_;
  return result;
}

Complex Complex::operator +(Complex other) {
  Complex result;
  result.real_ = other.real_ + this->real_;
  result.imaginary_ = other.imaginary_ + this->imaginary_;
  return result;
}

Complex Complex::operator -(Complex other) {
  return *this + -other;
}

Complex Complex::operator *(Complex other) {
  Complex result;
  result.real_ = this->real_ * other.real_ - this->imaginary_ * other.imaginary_;
  result.imaginary_ = this->imaginary_ * other.real_ + this->real_ * other.imaginary_;
  return result;
}

Complex Complex::operator /(Complex other) {
  Complex result;
  result.real_ = (this->real_ * other.real_ + this->imaginary_ + other.imaginary_) /
                 (other.real_ * other.real_ + other.imaginary_ * other.imaginary_);
  result.imaginary_ = (other.real_ * this->imaginary_ - this->real_ * other.imaginary_) /
                      (other.real_ * other.real_ + other.imaginary_ + other.imaginary_);
  return result;
}

Complex Complex::operator +(double other) {
  Complex result;
  result.real_ = this->real_ + other;
  result.imaginary_ = this->imaginary_;
  return result;
}

Complex Complex::operator -(double other) {
  Complex result;
  result.real_ = this->real_ - other;
  result.imaginary_ = this->imaginary_;
  return result;
}

Complex Complex::operator *(double other) {
  Complex result;
  result.real_ = this->real_ * other;
  result.imaginary_ = this->imaginary_ * other;
  return result;
}

Complex Complex::operator /(double other) {
  Complex result;
  result.real_ = this->real_ / other;
  result.imaginary_ = this->imaginary_ / other;
  return result;
}

Complex& Complex::operator=(Complex other) {
  this->Swap(other);
  return *this;
}
