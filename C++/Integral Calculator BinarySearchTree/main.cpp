/**
 * Parisa Nawar 
 * pxn210032
 */
#include <iostream>
#include <string>
#include <fstream>
#include <algorithm>
#include <iomanip>

#include "BinTree.h"
#include "Node.h"
#include "Term.h"

using namespace std;

int main()
{
    string fileName, line;
    
    cin >> fileName;
    
    ifstream file(fileName); // the file is put into the stream for evaluation
    
    while(getline(file, line)) {
        string term, eval, totalEq;
        bool evalReq = false;
        int up = 0, low = 0;
        double integTotal;
        
        BinTree<Term> equation; // binary tree is created
        
        /**
         * This for loop checks if there are bounds to be calculated
         * for the integral
         */
        for(size_t i = 0; i < line.size(); i++) {
            if(line.at(i) == '|') {
                if(isdigit(line.at(i + 1))) {
                    evalReq = true;
                    
                    term = line.substr(0, line.find('|'));
                    up = stoi(term);
                    line.erase(0, line.find('|'));
                    
                    term = line.substr(line.find('|') + 1, line.find(' ') - (line.find('|') + 1));
                    low = stoi(term);
                    line.erase(line.find('|'), line.find(' ') - line.find('|'));
                }
                else {
                    evalReq = false;
                    
                    line.erase(i, 1);
                }
            }
        }
        
        /**
         * This for loop deletes the dx portion
         */
        for(size_t i = 0; i < line.size(); i++) {
            if(line.at(i) == 'd' && line.at(i + 1) == 'x') {
                line.erase(i, 2);
            }
        }
        
        /**
         * This for loop deletes the spaces in the integral string
         */
        for(size_t i = 0; i < line.size(); i++) {
            if(line.at(i) == ' ') {
                line.erase(i, 1);
            }
        }
        
        /**
         * This for loop loops through the string and finds
         * the minus and plus signs and parses each polynomial
         */
        for(size_t i = 1; i < line.size(); i++) {
            if(line.at(i) == '+' || (line.at(i) == '-' && line.at(i - 1) != '^')) {
                term = line.substr(0, i - 0);
                line.erase(0, i - 0);

                Term sto(term);
                sto.integrate();
               
                if(evalReq == true) {
                    integTotal += sto.evaluate(up, low);
                }
                
                equation.insertBin(sto);
                
                i = 0;
            }
        } 

        Term end(line);
        end.integrate();
        
        /**
         * If the original string had values in front of the integral pipe,
         * then the term object's evaluate is called to calculate the value and return
         * it to the total integral value
         */
        if(evalReq == true) {
            integTotal += end.evaluate(up, low);
        }
        
        equation.insertBin(end);
        
        /**
         * Here the integrated equation is printed
         */
        totalEq = equation.printTreeReverse();
        
        /**
         * The for loop checks if there's both a plus and minus next to each other
         * and erases the plus if so
         */
        for(size_t i = 0; i < totalEq.size(); i++) {
            if(totalEq.at(i) == '+' && (totalEq.at(i + 1) == '-' || totalEq.at(i + 2) == '-')) {
                totalEq.erase(i, 1);
            }
        }
      
        /**
         * if the original integral had values then the following if else
         * statement decides how to exactly print out the definite or indefinite integral
         */
         if(evalReq == true) {
            totalEq = totalEq + ", " + to_string(up) + " | " + to_string(low) + " = ";
            cout << totalEq << fixed << setprecision(3) << integTotal << endl;
        }
        else {
            totalEq = totalEq + " + C";
            cout << totalEq << endl;
        } 
    }
    
    file.close(); 
}
