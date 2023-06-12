// Parisa Nawar pxn210032
#ifndef HASH_H
#define HASH_H

#include "LinkedList.h"

class Hash {
    private:
        const int lambda = 2;
        int hashSize;
        int curSize;
        double lamFactr;
        int linkNum;
        Linklist* listArr;
        
    public:
        Hash();
        Hash(int s);
        void hashInsert(int s);
        void rehash();
        void printHash();
};
#endif

Hash::Hash() {
    hashSize = 10; 
    listArr = new Linklist[hashSize];
    
}

void Hash::hashInsert(int s) {
    lamFactr = (1.0 * curSize) / hashSize;
    
    if(lamFactr >= lambda) {
        rehash();
    }
    
    int k = s % hashSize;
    listArr[k].addNode(s);
    
    curSize++;
}

void Hash::rehash() {
    int nSize = hashSize * 2;
    Linklist* newArr;
    
    newArr = new Linklist[nSize];
    
    for(int i = 0; i < nSize; i++) {
        int k = listArr[i].getData() % nSize;
        newArr[k].addNode(listArr[i].getData());
    }
    
    listArr = newArr;
    hashSize = nSize;
}

void Hash::printHash() {
    for(int i = 0; i < hashSize; i++) {
        std::cout << listArr[i].listInt() << std::endl;
    }
}