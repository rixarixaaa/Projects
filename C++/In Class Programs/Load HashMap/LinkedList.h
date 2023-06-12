// Parisa Nawar pxn210032
 #ifndef LINKLIST_H
 #define LINKLIST_H
 
 #include "Node.h"
 
 #include <string>
 
 class Linklist {
    private:
        Node* head;
        Node* curNode = head;
        
    public:    
        Linklist();
        void addNode(int d);
        int getData();
        std::string listInt();
 };
 
#endif

Linklist::Linklist() {
    head = NULL;
 }
 
void Linklist::addNode(int d) {
    Node* newNode = new Node(d);
    Node* curNode;
    
    if(head == NULL) {
        head = newNode;
        return;
    }
    else {
        curNode = head;
    
        while (curNode != NULL) {
            if(*curNode == *newNode) { 
                *curNode += *newNode;
                return;
            } 
            curNode = curNode->next; 
        } 
        
        curNode = head;
        
        while(curNode->next != NULL) {
            curNode = curNode->next;
        }

        curNode->next = newNode;
    }
 }
 
 std::string Linklist::listInt() {
     std::string toStr = "";
      
      while(curNode != NULL) {
          toStr += curNode->toString();
          toStr += " ";
          curNode = curNode->next;
      }
      
      return toStr;
 }
 
 int Linklist::getData() {
     return curNode->data;
     curNode = curNode->next;
 }
