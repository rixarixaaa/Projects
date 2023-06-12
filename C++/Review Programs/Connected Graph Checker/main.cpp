/**
 * Parisa Nawar
 * pxn210032
 */
#include "Graph.h"

#include <iostream>
#include <string>
#include <vector>
#include <fstream>

using namespace std;



int main()
{
    string fileName;
    
    cin >> fileName;
    ifstream file(fileName);
    
    Graph dec;
    dec.createGraph(file);
    dec.isConnected();
    
    file.close();
    
    
}
