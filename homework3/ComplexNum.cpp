#include "ComplexNum.hpp"
#include <cmath>

ComplexNumber::ComplexNumber(double real, double imag) : real(real), imag(imag) {}

ComplexNumber ComplexNumber::operator+(const ComplexNumber& other) const {
    return ComplexNumber(real + other.real, imag + other.imag);
}

ComplexNumber ComplexNumber::operator-(const ComplexNumber& other) const {
    return ComplexNumber(real - other.real, imag - other.imag);
}

ComplexNumber ComplexNumber::operator*(double scalar) const {
    return ComplexNumber(real * scalar, imag * scalar);
}

bool ComplexNumber::operator<(const ComplexNumber& other) const {
    return (real * real + imag * imag) < (other.real * other.real + other.imag * other.imag);
}

std::ostream& operator<<(std::ostream& os, const ComplexNumber& num) {
    os << num.real << (num.imag >= 0 ? " + " : " - ") << abs(num.imag) << "i";
    return os;
}
