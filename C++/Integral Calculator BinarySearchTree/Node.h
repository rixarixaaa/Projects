/**
 * Parisa Nawar 
 * pxn210032
 */
#ifndef NODE_H
#define NODE_H

#include <string>
#include <iostream>
#include <sstream>
#include <iomanip>

template <class T> 
class Node {
    private:
        T data;
        Node* left;
        Node* right;
        
    public:
        
        Node();
        Node(T data);
        Node(Node* n);
        
        T getData() {return data;}
        void setData(T d) {data = d;}
        
        Node* getRight() {return right;}
        void setRight(Node* r) {right = r;}
        
        Node* getLeft() {return left;}
        void setLeft(Node* l) {left = l;}
        
        std::string toString();
};

/**
 * Default node constructor
 */
template <typename T>
Node<T>::Node() {
    left = nullptr;
    right = nullptr;
}

/**
 * Overloaded node constructor with
 * node parameter
 */
template <typename T>
Node<T>::Node(T data) {
    this->data = data;
    this->left = nullptr;
    this->right = nullptr;
}

/**
 * Overloaded node constructor
 * with node parameter
 */
template <typename T>
Node<T>::Node(Node* n) {
    this->data = n->data;
    this->left = n->left;
    this->right = n->right;
}

/**
 * Node toString returns the templated
 * data's own toString
 */
template <typename T>
std::string Node<T>::toString() {
    return data.toString();
}

#endif //NODE_H