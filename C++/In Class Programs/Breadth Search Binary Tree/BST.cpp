//Parisa Nawar pxn210032
#include "BST.h"
#include <iostream>

bool BST::search(int x)
{
  Node* ptr = root;
  while (ptr)
  {
    if (ptr->getNum() == x)
        return true;
    else if (x < ptr->getNum())
        ptr = ptr->getLeft();
    else
        ptr = ptr->getRight();
  }
  return false;

}



void BST::add(Node* n)
{
    if (!root)
        root = n;
    else
    {
        Node *ptr = root;
        while(true)
        {
            if (n->getNum() < ptr->getNum())
            {
                if (ptr->getLeft())
                    ptr = ptr->getLeft();
                else
                {
                    ptr->setLeft(n);
                    break;
                }
            }
            else
            {
                if (ptr->getRight())
                    ptr = ptr->getRight();
                else
                {
                    ptr->setRight(n);
                    break;
                }
            }
        }
    }
}


Node* BST::deleteNode(int x)
{

    Node* parent = nullptr, *cur = root;

    while (cur)
    {
        if (cur->getNum() == x)
        {
            //if 0 children
            if (!cur->getLeft() && !cur->getRight())
            {
                Node* hold = new Node(cur);
                //if inside the tree
                if (parent)
                {
                    //check which child of the parent
                    if(parent->getLeft() == cur)
                        parent->setLeft(nullptr);
                    else
                        parent->setRight(nullptr);
                }
                else
                    root = nullptr;

                delete cur;
                return hold;
            }
            // check for 2 children
            else if(cur->getLeft() && cur->getRight())
            {
                Node* hold = cur;
		Node* temp = new Node(hold);
                parent = cur;
                cur = cur->getLeft();
                // move to the rightmost child of left subtree
                while (cur->getRight())
                {
                    parent = cur;
                    cur = cur->getRight();
                }
                //copying the data
                hold->setNum(cur->getNum());

                //link cur's parent to cur's child
                if (parent == hold)
                    parent->setLeft(cur->getLeft());
                else
                    parent->setRight(cur->getLeft());

                delete cur;
                return temp;
            }
            //has 1 child
            else
            {
                if (parent)
                {
                    //check if cur is left child
                    if (parent->getLeft() == cur)
                        //assign parent left to cur's child
                        parent->setLeft(cur->getLeft() ? cur->getLeft() : cur->getRight());
                    else
                        //assign parent right to cur's child
                        parent->setRight(cur->getLeft() ? cur->getLeft() : cur->getRight());
                }
                else
                    root = cur->getLeft() ? cur->getLeft() : cur->getRight();

                Node* hold = new Node(cur);
                delete cur;
                return hold;
            }


        }
        else
        {
            parent = cur;
            if (x < cur->getNum())
                cur = cur->getLeft();
            else
                cur = cur->getRight();
        }
    }
    return nullptr;
}


int BST::findHeightHelper(Node* iterator) {
    if(iterator == nullptr) {
        return 0;
    }
    int leftTreeHeight = findHeightHelper(iterator->getLeft());
    int rightTreeHeight = findHeightHelper(iterator->getRight());
    if(leftTreeHeight > rightTreeHeight) { // increment the variable for the direction with the largest height
        return leftTreeHeight+1;
    }
    else {
        return rightTreeHeight+1;
    }
    return 0;
}

int BST::findHeight() {
    return findHeightHelper(root);
}




void BST::breadthFirst() {
    if(root == NULL) {
        return;
    }
    
    std::queue<Node*> q;
    
    Node* curNode;
    
    q.push(root);
    q.push(NULL);
    
    while(q.size() > 1) {
        curNode = q.front();
        q.pop();
    
    
        if(curNode == NULL) {
            q.push(NULL);
            std::cout << "\n";
        }
        else {
            if(curNode->getLeft()) {
                q.push(curNode->getLeft());
            }
            
            if(curNode->getRight()) {
                q.push(curNode->getRight());
            }
        
            std::cout << curNode->getNum() << " ";
        }
    }
}