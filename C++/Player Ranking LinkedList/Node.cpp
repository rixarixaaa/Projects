/**
 * Parisa Nawar
 * pxn210032
 */
 #include "Node.h"
 #include <cstring>
 
    Player data;
    Node* next;
        
    Node::Node() {
        next = NULL;
    }
    
    /**
     * Overloaded Node constructor
     * takes a Player object data and
     * inserts it to the node
     */
    Node::Node(Player data) {
        this->data = data;
        this->next = NULL;
    }
    
    /**
     * Overloaded plus equal operator
     * helps add to an existing node data with 
     * another node 
     */
    void Node::operator+=(const Node& nod) {
        this->data = this->data + nod.data;
    }
    
    /**
     * Overloaded less than operator
     * compares two nodes and returns
     * whether it is less than or not
     * by boolean
     */
    bool Node::operator<(const Node& nod) {
        return data < nod.data;
    }
    
    /**
     * Overloaded equal evaluating operator
     * compares two nodes and returns
     * whether they are equal
     * by boolean
     */
    bool Node::operator==(const Node& nod) {
        return data == nod.data;
    }
    
    /**
     * toString function of the Node class 
     * returns the toString of the Player
     * class
     */
    std::string Node::toString() {
        return data.toString();
    } 
 