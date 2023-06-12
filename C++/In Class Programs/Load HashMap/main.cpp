// Parisa Nawar pxn210032
#include <iostream>

#include "Hash.h"

using namespace std;

int main()
{
    int size, val, i = 0;
    Hash trialHash;
    
    cin >> size;
    
    while(i < size) {
        cin >> val;
        trialHash.hashInsert(val);
        i++;
    }
    
    trialHash.printHash();
}