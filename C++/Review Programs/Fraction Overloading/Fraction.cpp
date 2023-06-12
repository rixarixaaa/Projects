// Parisa Nawar pxn210032

#include "Fraction.h"

#include <cstring>

int num;
int den;

Fraction::Fraction() {
    num = 1;
    den = 1;
}

Fraction::Fraction(int n) {
    num = n;
    den = 1;
}

Fraction::Fraction(int n, int d) {
    num = n;
    den = d;
}

int Fraction::getDivide(int n, int d) {
    if(d == 0) {
        return n;
    }
    
    return getDivide(d, n % d);
} 

void Fraction::Simplify(Fraction& frac) {
    int divide;
    
    divide = getDivide(frac.num, frac.den);
    
    frac.num = frac.num / divide;
    
    frac.den = frac.den / divide;
    
}

Fraction Fraction::operator+(const Fraction& frac) {
    Fraction fracTotal;
    
    fracTotal.num = (num * frac.den) + (frac.num * den);
    fracTotal.den = (den * frac.den);
    
    Simplify(fracTotal);
    
    return fracTotal;
}
        
Fraction Fraction::operator-(const Fraction& frac) {
    Fraction fracTotal;
    
    fracTotal.num = (num * frac.den) - (frac.num * den);
    fracTotal.den = (den * frac.den);
    
    Simplify(fracTotal);
    
    return fracTotal;
}

Fraction Fraction::operator*(const Fraction& frac) {
    Fraction fracTotal; 
    
    fracTotal.num = num * frac.num;
    fracTotal.den = den * frac.den;
    
    Simplify(fracTotal);
    
    return fracTotal;
}

Fraction Fraction::operator/(const Fraction& frac) {
    Fraction fracTotal;
    
    fracTotal.num = num * frac.den;
    fracTotal.den = den * frac.num;
    
    Simplify(fracTotal);
    
    return fracTotal;
}
 
bool Fraction::operator<(const Fraction& frac) {
    return (1.0 * num / den) < (1.0 * frac.num / frac.den); 
}
    
bool Fraction::operator>(const Fraction& frac) {
    return (1.0 * num / den) > (1.0 * frac.num / frac.den);
}

bool Fraction::operator==(const Fraction& frac) {
    return (1.0 * num / den)  == (1.0 * frac.num / frac.den); 
} 

std::ostream& operator<<(std::ostream& out, const Fraction& frac) { 
    out << frac.num << " / " << frac.den;
    return out;
}

std::istream& operator>>(std::istream& in, Fraction& frac) {
    int nu;
    int de;
    
    std::cout << "Enter numerator: ";
    
    in >> nu;
    
    frac.setNumerator(nu);
    
    std::cout << "Enter denominator: ";
    
    in >> de;
    
    frac.setDenominator(de);
    
    return in;
} 

