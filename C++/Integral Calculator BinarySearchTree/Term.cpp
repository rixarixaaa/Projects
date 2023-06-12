/**
 * Parisa Nawar 
 * pxn210032
 */
 #include "Term.h"
 
 #include <cstring>
 #include <cmath>
 #include <iostream>
 
 std::string str;
 int coefficient;
 int exponent;
 int num = 0;
 int den = 0;
 bool firstTerm;
 
 Term::Term() {
    str = "";
    coefficient = 0;
    exponent = 0;
    num = 0;
    den = 0;
 }

/**
 * Overloaded term constructor takes the string polynomial
 * argument and parses the numbers before x as the coefficient
 * and after the ^ as the exponent, otherwise assigns a default
 * value to them
 */
Term::Term(std::string t) {
    size_t place;
    
    if(t.find('x') != std::string::npos) {
        if(t.at(0) == '+') {
            place = t.find('x');
            
            if(!isdigit(t.at(place - 1))) {
                coefficient = 1;
            }
            else {
                coefficient = std::stoi(t.substr(1, place - 1));
            }
            
            if(t.find('^') != std::string::npos) {
                place = t.find('^');
                exponent = std::stoi(t.substr(place + 1));
            }
            else {
                exponent = 1;
            }
        }
        else if(t.at(0) == '-') {
            place = t.find('x');
            
            if(!isdigit(t.at(place - 1))) {
                coefficient = -1;
            }
            else {
                coefficient = std::stoi(t.substr(0, place));
            }
            
            if(t.find('^') != std::string::npos) {
                place = t.find('^');
                exponent = std::stoi(t.substr(place + 1));
            }
            else {
                exponent = 1;
            }
        }
        else {
            firstTerm = true;
            place = t.find('x');
            
            if(!isdigit(t.at(0))) {
                coefficient = 1;
            }
            else {
                coefficient = std::stoi(t.substr(0, place));
            }
            
            if(t.find('^') != std::string::npos) {
                place = t.find('^');
                exponent = std::stoi(t.substr(place + 1));
            }
            else {
                exponent = 1;
            }
            
        }
    }
    else {
        if(t.at(0) == '+') {
            coefficient = std::stoi(t.substr(1));
            exponent = 0;
        }
        else if(t.at(0) == '-') {
            coefficient = std::stoi(t.substr(0));
            exponent = 0;
        }
        else {
            firstTerm = true;
            
            coefficient = std::stoi(t.substr(0));
            exponent = 0;
        }
    } 
}

/**
 * getGCD gets the greatest common
 * denominator for the simplify function
 */
int Term::getGCD(int nu, int de) {
    if(de == 0) {
        return nu;
    }
    
    return getGCD(de, nu % de);
}

/**
 * simplify function simplifies the 
 * numerator and denominator passed by
 * reference
 */
void Term::simplify(int& n, int& d) {
    int com;
    
    com = getGCD(n, d);
    
    n = n / com;
    d = d / com;
    
}

/**
 * integrate function integrates
 * the polynomial by incrementing the
 * exponent by 1 and adjusting the coefficient accordingly
 */
void Term::integrate() {
    exponent = exponent + 1;
    
    if(coefficient % exponent == 0) {
        num = coefficient / exponent;
        den = 1;
    }
    else {
        num = coefficient;
        den = exponent;
        
        if((num / den) < 0) {
            num = abs(num);
            den = abs(den);
            
            simplify(num, den);
            
            num = num * -1;
        }
        else {
            num = abs(num);
            den = abs(den);
            
            simplify(num, den);
        }
        
    }
}

/**
 * evaluate function calculates the value
 * of the integral by using the two numbers 
 * passed through the parameters to calculate the total 
 * using the polynomial
 */
double Term::evaluate(int u, int d) {
    double upperTotal;
    double lowerTotal;
    
    if(den == 1) {
       upperTotal = (num) * pow(u, exponent);
       lowerTotal = (num) * pow(d, exponent);
   }
   else {
       upperTotal = (static_cast<double>(num) / static_cast<double>(den)) * pow(u, exponent);
       lowerTotal = (static_cast<double>(num) / static_cast<double>(den)) * pow(d, exponent);
   } 
   
   return (upperTotal - lowerTotal);
} 

/**
 * Overloaded term operator adds two terms
 * together
 */
Term Term::operator+(const Term& ter) {
    Term termTotal;
    
    termTotal.exponent = exponent;
    termTotal.num = (num * ter.den) + (ter.num * den);
    termTotal.den = (den * ter.den);
    
    simplify(termTotal.num, termTotal.den);
    
    return termTotal;
}

/**
 * Overloaded less than operator compares the exponents
 * of two operators and returns whether the first Term
 * is less than the second or not
 */
bool Term::operator<(const Term& ter) {
    return (exponent < ter.exponent);
}

/**
 * Overloaded greater than operator compares the exponents
 * of two operators and returns whether the first Term
 * is greater than the second or not
 */
bool Term::operator>(const Term& ter) {
    return (exponent > ter.exponent);
}

/**
 * Overloaded evaluator operator evaluates whether two terms are the same
 * with the same coefficients
 */
bool Term::operator==(const Term& ter) {
    return (exponent == ter.exponent);
}

/**
 * Overloaded not equal to operator
 * checks if a term is not the same by comparing the coefficients 
 * of two terms
 */
bool Term::operator!=(const Term& ter) {
    return (exponent != ter.exponent);
}

/**
 * toString Term operator returns a string with the polynomial Term
 * object
 */
std::string Term::toString() {
    std::string term = "";
    
    if(exponent == 1) {
        if(den == 1) {
            if(num == 1) {
                term = "x";
            }
            else if(num == -1) {
                term = "-x";
            }
            else {
                if(num > 0) {
                    term = term + std::to_string(num) + "x";
                }
                else if(num < 0) {
                    num = abs(num);
                    term = term + "-" + std::to_string(num) + "x";
                }
            }
        }
        else {
            if(num > 0) {
                term = term + "(" + std::to_string(num) + "/" + std::to_string(den) + ")" + "x";
            }
            else if(num < 0) {
                num = abs(num);
                term = term + "-(" + std::to_string(num) + "/" + std::to_string(den) + ")" + "x";
            }
        }
    }
    else {
        if(den == 1) {
            if(num == 1) {
                term = "x^" + std::to_string(exponent);
            }
            else if(num == -1) {
                term = "-x^" + std::to_string(exponent);
            }
            else {
                if(num > 0) {
                    term = term + std::to_string(num) + "x^" + std::to_string(exponent);
                }
                else if(num < 0) {
                    num = abs(num);
                    term = term + "-" + std::to_string(num) + "x^" + std::to_string(exponent);
                }
            }
        }
        else {
            if(num > 0) {
                term = term + "(" + std::to_string(num) + "/" + std::to_string(den) + ")" + "x^" + std::to_string(exponent);
            }
            else if(num < 0) {
                num = abs(num);
                term = term + "-(" + std::to_string(num) + "/" + std::to_string(den) + ")" + "x^" + std::to_string(exponent);
            }
        }
    }
    return term;
}