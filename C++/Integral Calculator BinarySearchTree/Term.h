/**
 * Parisa Nawar 
 * pxn210032
 */
#ifndef TERM_H
#define TERM_H

#include <string>

class Term {
    private:
        std::string str;
        int coefficient;
        int exponent;
        int num = 0;
        int den = 0;
        bool firstTerm;
        
    
    public:
        Term();
        Term(std::string);
        
        int getCo() {return coefficient;}
        void setCo(int co) {coefficient = co;}
        
        int getEx() {return exponent;}
        void setEx(int ex) {exponent = ex;}
        
        int getGCD(int nu, int de);
        void simplify(int& n, int& d);
        
        void integrate();
        double evaluate(int u, int d);
        
        Term operator+(const Term& ter);
        
        bool operator<(const Term& ter); 
        bool operator>(const Term& ter);
        bool operator==(const Term& ter);
        bool operator!=(const Term& ter);
        
        
        std::string toString();
};

#endif //TERM_H