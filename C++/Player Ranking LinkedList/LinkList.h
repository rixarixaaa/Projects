/**
 * Parisa Nawar
 * pxn210032
 */
 #ifndef LINKLIST_H
 #define LINKLIST_H
 
 #include "Node.h"
 #include "Player.h"
 
 #include <string>
 
 class Linklist {
    private:
        Node* head;
        
    public:    
        Linklist();
        void addNode(Player d);
        void sortList();
        std::string toString();
        void printLeaderBA();
        void printLeaderOBP();
        void printLeaderHit();
        void printLeaderWalk();
        void printLeaderSO();
        void printLeaderHBP();
        
        
        
 };
 
 #endif //LINKLIST_H