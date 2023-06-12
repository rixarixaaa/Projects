// Parisa Nawar pxn210032
 #ifndef NODE_H
 #define NODE_H
 
 #include <string>
 
class Node {
     
    public:
        int data;
        Node* next;
        Node();
        Node(int);
        
        void operator+=(const Node& nod);
        
        bool operator<(const Node& nod);
        bool operator==(const Node& nod);
        
        int toString();  
        
 };
 #endif
 
    Node::Node() {
        next = NULL;
    }
    

    Node::Node(int data) {
        this->data = data;
        this->next = NULL;
    }
    
    void Node::operator+=(const Node& nod) {
        this->data = this->data + nod.data;
    }
    
    bool Node::operator<(const Node& nod) {
        return data < nod.data;
    }
    
    bool Node::operator==(const Node& nod) {
        return data == nod.data;
    }

    int Node::toString() {
        return data;
    } 
 
