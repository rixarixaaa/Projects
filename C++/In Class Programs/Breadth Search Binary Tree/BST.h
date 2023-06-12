//Parisa Nawar pxn210032
#ifndef BST_H
#define BST_H
#include "Node.h"
#include <queue>
#include <deque>

class BST
{
private:
    Node* root = nullptr;

public:
    BST(int x) {root = new Node(x);}
    ~BST() {};
    void add(Node*);
    bool search(int x);
    void insert(Node*);
    Node* deleteNode(int);
    int findHeight();
    int findHeightHelper(Node* iterator);
    void breadthFirst();
    
};
#endif // BST_H
