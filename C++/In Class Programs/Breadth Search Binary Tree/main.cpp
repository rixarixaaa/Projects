//Parisa Nawar pxn210032
#include <iostream>

#include "BST.h"
#include "Node.h"

using namespace std;

int main()
{
    BST b(13);
    b.add(new Node(26));
    b.add(new Node(17));
    b.add(new Node(39));
    b.add(new Node(77));
    b.add(new Node(78));
    b.add(new Node(6));
    b.add(new Node(3));
    b.add(new Node(4));
    b.add(new Node(8));
    b.add(new Node(74));
    std::cout << b.findHeight() << std::endl << std::endl;
    b.breadthFirst();
}