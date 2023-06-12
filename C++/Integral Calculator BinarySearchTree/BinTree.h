/**
 * Parisa Nawar 
 * pxn210032
 */
#ifndef BINTREE_H
#define BINTREE_H

#include "Node.h"

#include <string>
#include <iostream>

template <class T>
class BinTree {
    private:
        Node<T>* root;
        
    public:
        BinTree() {root = nullptr;}
        ~BinTree();
        void desHelper(Node<T>* n);
        
        Node<T>* getRoot() {return root;}
        void setRoot(Node<T>* set) {root = set;}
        
        void insertBin(T in);
        void insertBinHelper(T i, Node<T>* r);
        
        bool searchBin(T se); 
        bool searchBinHelper(T s, Node<T>* n);
        
        void removeBin(T re); 
        Node<T>* removeBinHelper(T r, Node<T>* n);
        
        std::string printTreeReverse();
        std::string printHelper(Node<T>* r);
};

/**
 * Templated BinaryTree destructor destroys the whole tree once 
 * it is out of scope
 */
template <typename T>
BinTree<T>::~BinTree() {
    desHelper(root);
} 

/**
 * BinaryTree destructor helper method recursively traverses
 * through the tree to delete each node
 */
template <typename T>
void BinTree<T>::desHelper(Node<T>* n) {
    if(n) {
        desHelper(n->getLeft());
        desHelper(n->getRight());
        delete n;
    }
}

/**
 * Insert function of the binary tree
 * takes a templated data and inserts it into a Node
 * which is inserted into the tree
 */
template <typename T>
void BinTree<T>::insertBin(T in) {
    insertBinHelper(in, root);
}

/**
 * Insert helper method recursively checks
 * for an empty leaf and inserts the latest node 
 * there based on exponent order
 */
template <typename T>
void BinTree<T>::insertBinHelper(T i, Node<T>* r) {
    Node<T>* newNode = new Node<T>(i);
    
    if(root == nullptr) {
        root = newNode;
        return;
    }
    
    if(i < r->getData()) {
        if(r->getLeft()) {
           insertBinHelper(i, r->getLeft()); 
        }
        else {
            r->setLeft(newNode);
        } 
    }
    else if(i > r->getData()) {
        if(r->getRight()) {
            insertBinHelper(i, r->getRight());
        }
        else {
            r->setRight(newNode);
        }
    }
    else {
        r->setData(r->getData() + i);
        return;
    } 
}

/**
 * Search function of the binary tree
 * uses a templated data to search for the node 
 * that contains the data
 */
template <typename T>
bool BinTree<T>::searchBin(T se) {
    return searchBinHelper(se, root);
}

/**
 * Search helper method of the binary tree recursively traverses through
 * the tree to find whether that node exists with the data passed
 * and returns true or false
 */
template <typename T>
bool searchBinHelper(T s, Node<T>* n) {
    if(n == nullptr) {
        return false;
    }
    else if(s == n->getData()) {
        return true;
    }
    else if(s < n->getData()) {
        return searchBinHelper(s, n->getLeft());
    }
    else if(s > n->getData()) {
        return searchBinHelper(s, n->getRight());
    }
}

/**
 * Remove function of the binary tree removes a node with
 * the given templated data 
 */
template <typename T>
void BinTree<T>::removeBin(T re) {
    removeBinHelper(re, root);
} 

/**
 * Remove helper method recursively searches for the Node
 * that contains the templated data in the argument and returns
 * the node that should be deleted
 */
template <typename T>
Node<T>* BinTree<T>::removeBinHelper(T re, Node<T>* n) {
    if(n == nullptr) {
        return n;
    }
    
    if(re < n->getData()) {
        removeBinHelper(re, n->getLeft());
    }
    else if(re > n->getData()) {
        removeBinHelper(re, n->getRight());
    }
    else {
        if(n->getLeft() == nullptr && n->getRight() == nullptr) {
            return nullptr;
        }
        else if (n->getLeft() == nullptr) {
            Node<T>* tempNode = n->getLeft();
            
            free(n);
            
            return tempNode;
        }
        else if(n->getRight() == nullptr) {
            Node<T>* tempNode = n->getLeft();
            
            free(n);
            
            return tempNode;
        }
        
        Node<T>* curNode = n->getRight();
        Node<T>* tempNode;
        Node<T>* repNode;
    
        while(curNode && curNode->left != nullptr) {
            curNode = curNode->getLeft();
        }
    
        tempNode = curNode;
    
        n = tempNode;
        
        removeBinHelper(tempNode->getData(), n->getRight());
    }
    
    return n;
} 

/**
 * Print tree reverse method prints the binary tree
 * from greatest to smallest value in order
 */
template <typename T>
std::string BinTree<T>::printTreeReverse() {
    return printHelper(root);
}
 
 /**
  * Print tree helper method prints the binary tree
  * from the right side to print the greatest values
  * first then left side to print the smaller values
  * and returns the string with the nodes
  */
template <typename T>   
std::string BinTree<T>::printHelper(Node<T>* r) {
    std::string equation = ""; 
  
    if(r != nullptr) {
        if(r->getRight()) {
            equation = equation + " + " + printHelper(r->getRight());
        }
        
        equation.insert(0, r->toString());
        
        if(r->getLeft()) {
            equation = equation + " + " + printHelper(r->getLeft());
        }
    }
    
    
    return equation;
} 




#endif //BINTREE_H