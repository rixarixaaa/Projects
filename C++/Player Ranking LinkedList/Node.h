/**
 * Parisa Nawar
 * pxn210032
 */
 #ifndef NODE_H
 #define NODE_H
 
 #include "Player.h"
 
 #include <string>
 
 
 class Node {
     
    public:
        Player data;
        Node* next;
        Node();
        Node(Player);
        
        void operator+=(const Node& nod);
        
        bool operator<(const Node& nod);
        bool operator==(const Node& nod);
        
        std::string toString();  
        
        
        
 };
 
 #endif //NODE_H