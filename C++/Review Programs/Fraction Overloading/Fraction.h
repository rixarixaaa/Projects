// Parisa Nawar pxn210032

#ifndef FRACTION_H
#define FRACTION_H

#include <string>
#include <iostream>

class Fraction {
    
    protected:
        int num;
        int den;

    public:
        Fraction();
        Fraction(int);
        Fraction(int, int);
        
        int getNumerator() const {return num;} // gets numerator
        int getDenominator() const {return den;} // gets denominator
        
        void setNumerator(int n) {num = n;} // sets numerator to what user inputs
        void setDenominator(int d) {den = d;} // sets denominator to what user inputs
        
        int getDivide(int n, int d); // finds the greatest common denominator
        void Simplify(Fraction& frac); // simplifies the numerator and denominator
        

        Fraction operator+(const Fraction& frac); // adds two fraction objects
        Fraction operator-(const Fraction& frac); // subtracts two fraction objects
        Fraction operator*(const Fraction& frac); // multiplies two fraction objects
        Fraction operator/(const Fraction& frac); // divides two fraction objects
        
        bool operator<(const Fraction& frac); // compares if first fraction object is less than second 
        bool operator>(const Fraction& frac); // compares if first fraction object is greater than second
        bool operator==(const Fraction& frac); // compares if two fraction objects are equal
        
        friend std::ostream& operator<<(std::ostream& out, const Fraction& frac); // overloads output
        friend std::istream& operator>>(std::istream& in, Fraction& frac); // overloads input
};

#endif