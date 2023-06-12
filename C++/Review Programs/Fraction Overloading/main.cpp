// Parisa Nawar pxn210032

#include <iostream>
#include "Fraction.h"

using namespace std;

int main()
{
    /**
     * Creation of two fraction objects
     */
    Fraction f1 = Fraction(4);
    Fraction f2 = Fraction(2, 8);
    
    /**
     * Testing input and output overloaded operators with the math operators
     */
    cin >> f1;
    
    cout << f1 + f2 << endl;
    cout << f1 - f2 << endl;
    cout << f1 * f2 << endl;
    cout << f1 / f2 << endl;
    
    /**
     * Testing comparison operators
     */
    if (f1 < f2) {
        cout << "f2 is greater";
    }
    
    if(f1 > f2) {
        cout << "f1 is greater";
    }
    
    
    if(f1 == f2) {
        cout << "Both are equal";
    } 
    
}
