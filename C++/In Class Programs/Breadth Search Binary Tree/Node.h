//Parisa Nawar pxn210032
#ifndef NODE_H
#define NODE_H

class Node
{
private:
    int num;
    Node *right, *left;


public:
    Node(){num=0;left=nullptr;right=nullptr;}
    Node(int x){num=x;left=nullptr;right=nullptr;}
    Node(Node* c){this->num=c->num; left=nullptr; right=nullptr;}

    int getNum(){return num;}
    Node* getLeft(){return left;}
    Node* getRight(){return right;}

    void setNum(int x){num=x;}
    void setLeft(Node* n){left=n;}
    void setRight(Node* n){right=n;}

};
#endif // NODE_H