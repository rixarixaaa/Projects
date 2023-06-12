//Parisa Nawar pxn210032

#include <iostream>
#include <vector>

#include "VectorTemplate.h"

using namespace std;

int main()
{
    
    vector<int>intVec{5, 3, 4, 6, 2};
    vector<double> doubVec{5.5, 1.2, 4.5, 5.6, 9.0};
    vector<string> strVec{"cat", "dog", "apple", "bee"};

    VectorTemplate<int>tempInt(intVec);
    VectorTemplate<double>tempDoub(doubVec);
    VectorTemplate<string>tempStr(strVec);
    
    tempInt.InsertionSort();
    tempInt.BinarySearch(6);
    
    tempDoub.InsertionSort();
    tempDoub.BinarySearch(4.3);
    
    tempStr.InsertionSort();
    tempStr.BinarySearch("car");
    
    
}