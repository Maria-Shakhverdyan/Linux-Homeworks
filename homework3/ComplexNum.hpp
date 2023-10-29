#ifndef COMPLEXNUM_HPP
#define COMPLEXNUM_HPP

#include <iostream>

class ComplexNumber {
public:
    ComplexNumber(double real, double imag);

    ComplexNumber operator+(const ComplexNumber& other) const;
    ComplexNumber operator-(const ComplexNumber& other) const;
    ComplexNumber operator*(double scalar) const;

    bool operator<(const ComplexNumber& other) const;

    friend std::ostream& operator<<(std::ostream& os, const ComplexNumber& num);

private:
    double real;
    double imag;
};

#endif
