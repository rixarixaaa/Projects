/**
 * Parisa Nawar
 * pxn210032
 */
#include <iostream>
#include <string>
#include <fstream>

#include "LinkList.h"
#include "Node.h"
#include "Player.h"

using namespace std;

int main()
{
    string fileName, line, name, scoreSeq;
    size_t index;
    Linklist playerList;
    
    cin >> fileName;
    
    ifstream file(fileName);
    
    if(file) { // Reads the file
        while(getline(file, line)) {
            if(line != "") {
                index = line.find(' ');
                
                name = line.substr(0, index);
                
                scoreSeq = line.substr(index + 1); 
                
                Player p(name, scoreSeq); // Player object is created with the name and the score to be calculated and stored
                
                playerList.addNode(p); // Player object is added as a node inside the linkedlist
            }
        }
    }
    
    file.close();
    
    playerList.sortList(); // calls Sorting the list alphabetically
    
    cout << playerList.toString() << endl; // prints out each person and their statistics in one line 
    
    /**
     * playerList is printed out leaders through each printLeader function call
     */
    cout << "LEAGUE LEADERS" << endl;
    playerList.printLeaderBA();
    playerList.printLeaderOBP();
    playerList.printLeaderHit();
    playerList.printLeaderWalk();
    playerList.printLeaderSO();
    playerList.printLeaderHBP();
    
    
    
} 